#include "TelegramNotifier.h"

#include <spdlog/spdlog.h>
#include <utility>

TelegramNotifier::TelegramNotifier(std::string botToken, std::string chatId)
    : m_botToken(std::move(botToken))
    , m_chatId(std::move(chatId))
{
}

void TelegramNotifier::notify(const LogWatcher::ChatMessage& message)
{
  httplib::Params params;
  params.emplace("chat_id", m_chatId);
  params.emplace("text", fmt::format("{}", message));
  std::string url{fmt::format("/bot{}/sendMessage", m_botToken)};
  if (auto res = m_client.Post(url, params); res->status != 200)
  {
    spdlog::error("Sent telegram message, Status: {}, Body: {}", res->status, res->body);
  }
  else
  {
    spdlog::debug("Sent telegram message, Status: {}, Body: {}", res->status, res->body);
  }
}
