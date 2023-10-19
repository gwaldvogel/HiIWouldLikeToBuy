#pragma once

#include <httplib.h>
#include <notify/INotifier.h>
#include <string>

class TelegramNotifier : public INotifier
{
public:
  TelegramNotifier(std::string botToken, std::string chatId);
  void notify(const LogWatcher::ChatMessage& message) override;

private:
  const std::string m_botToken;
  const std::string m_chatId;
  httplib::Client m_client = httplib::Client("https://api.telegram.org");
};
