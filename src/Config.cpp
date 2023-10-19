#include "Config.h"

Config::Config(const std::string& configFile)
    : m_config(YAML::LoadFile(configFile))
{
}

std::string Config::telegramBotToken()
{
  return m_config[Keys::TELEGRAM][Keys::TELEGRAM_BOT_TOKEN].as<std::string>();
}

std::string Config::telegramChatId()
{
  return m_config[Keys::TELEGRAM][Keys::TELEGRAM_CHAT_ID].as<std::string>();
}

std::vector<std::string> Config::filterRegex()
{
  std::vector<std::string> vec;
  for (std::size_t i = 0; i < m_config[Keys::FILTER].size(); i++)
  {
    const std::string regex{m_config[Keys::FILTER][i].as<std::string>()};
    if (std::ranges::find(vec.begin(), vec.end(), regex) == vec.end())
    {
      vec.push_back(regex);
    }
  }
  return vec;
}

std::string Config::logFile()
{
  return m_config[Keys::LOG_FILE].as<std::string>();
}

bool Config::isTelegramActive()
{
  if (m_config[Keys::TELEGRAM].IsMap())
  {
    return true;
  }
  return false;
}
