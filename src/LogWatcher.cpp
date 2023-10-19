#include "LogWatcher.h"

#include "spdlog/spdlog.h"
#include <fstream>
#include <regex>
#include <utility>

using namespace std::chrono_literals;

LogWatcher::LogWatcher(std::string filename, std::function<void(const ChatMessage&)> callback)
    : m_filename(std::move(filename))
    , m_callback(std::move(callback))
    , m_watcherThread([this]() { watch(); })
{
}

LogWatcher::~LogWatcher()
{
  m_keepWatching = false;
  if (m_watcherThread.joinable())
  {
    m_watcherThread.join();
  }
}

void LogWatcher::handleUpdatedFile()
{
  static const std::regex regex{R"(^([0-9\/]+ [0-9:]+) [0-9a-z \[\]A-Z]+ @From (?:<.*> )*([^:]+): (.*)$)"};
  if (std::ifstream file(m_filename); file && m_lastPos != 0)
  {
    file.seekg(m_lastPos);
    spdlog::debug("Reading at position {}", m_lastPos);
    std::string line;
    while (std::getline(file, line))
    {
      std::smatch result;
      if (std::regex_match(line, result, regex))
      {
        ChatMessage message{
          result[1],
          result[2],
          result[3],
        };
        m_callback(message);
      }
    }
    m_lastPos = file.tellg();
  }
  if (m_lastPos == -1 || m_lastPos == 0)
  {
    jumpToEnd();
  }
  spdlog::debug("Next position is {}", m_lastPos);
}

void LogWatcher::watch()
{
  jumpToEnd();
  while (m_keepWatching)
  {
    std::this_thread::sleep_for(1s);
    if (auto currentWriteTime = std::filesystem::last_write_time(m_filename); currentWriteTime != m_lastWriteTime)
    {
      m_lastWriteTime = currentWriteTime;
      handleUpdatedFile();
    }
    m_firstRun = false;
  }
}

void LogWatcher::jumpToEnd()
{
  if (std::ifstream file(m_filename); file)
  {
    file.seekg(0, std::ios::end);
    m_lastPos = file.tellg();
    spdlog::debug("Jumping to position {}", m_lastPos);
  }
}
