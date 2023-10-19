#pragma once

#include <string>
#include <yaml-cpp/yaml.h>

class Config
{
public:
  explicit Config(const std::string& configFile = "config.yaml");

  bool isTelegramActive();
  std::string logFile();
  std::string telegramBotToken();
  std::string telegramChatId();
  std::vector<std::string> filterRegex();

private:
  struct Keys
  {
    static constexpr const char* TELEGRAM = "telegram";
    static constexpr const char* TELEGRAM_BOT_TOKEN = "botToken";
    static constexpr const char* TELEGRAM_CHAT_ID = "chatId";
    static constexpr const char* FILTER = "filter";
    static constexpr const char* LOG_FILE = "logFile";
  };

  YAML::Node m_config;
};
