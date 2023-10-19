#pragma once

#include "fmt/format.h"
#include <filesystem>
#include <functional>
#include <regex>
#include <string_view>
#include <thread>

class LogWatcher
{
public:
  struct ChatMessage
  {
    std::string datetime;
    std::string author;
    std::string message;
  };

  LogWatcher(std::string filename, std::function<void(const ChatMessage&)> callback);
  ~LogWatcher();

private:
  void watch();
  void handleUpdatedFile();

  std::string m_filename;
  std::function<void(const ChatMessage&)> m_callback;
  std::filesystem::file_time_type m_lastWriteTime;
  int64_t m_lastPos = 0;

  std::atomic_bool m_keepWatching = true;
  bool m_firstRun = true;
  std::thread m_watcherThread;
  void saveLastPosition();
  void jumpToEnd();
};

template <> struct fmt::formatter<LogWatcher::ChatMessage>
{
  constexpr auto parse(format_parse_context& ctx) -> format_parse_context::iterator
  {
    auto it = ctx.begin();
    if (auto end = ctx.end(); it != end && *it != '}')
      throw_format_error("invalid format");
    return it;
  }
  auto format(const LogWatcher::ChatMessage& msg, format_context& ctx) const -> format_context::iterator
  {
    return fmt::format_to(ctx.out(), "[{}] {}: {}", msg.datetime, msg.author, msg.message);
  }
};