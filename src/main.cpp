#include <Config.h>
#include <iostream>
#include <LogWatcher.h>
#include <notify/TelegramNotifier.h>
#include <spdlog/spdlog.h>

int main()
{
  std::string configFile = std::filesystem::current_path().append("config.yaml").string();
  spdlog::info("Starting HiIWouldLikeToBuy, loading config file: {}", configFile);
  Config config{configFile};
  std::vector<std::unique_ptr<INotifier>> vecNotifier;
  if (config.isTelegramActive())
  {
    vecNotifier.push_back(std::make_unique<TelegramNotifier>(config.telegramBotToken(), config.telegramChatId()));
  }

  LogWatcher watcher{
    config.logFile(),
    [&vecNotifier, &config](const LogWatcher::ChatMessage& message)
    {
      for (const auto& filterRegex : config.filterRegex())
      {
        std::regex regex{filterRegex, std::regex_constants::icase};
        if (std::regex_match(message.message, regex))
        {
          spdlog::debug("Received message: {}", message);
          for (const auto& notifier : vecNotifier)
          {
            notifier->notify(message);
          }
          break;
        }
      }
    }};
  do
  {
    std::cout << '\n' << "Press a key to continue..." << std::endl;
  } while (std::cin.get() != '\n');
  return 0;
}
