# Hi I Would Like To Buy
HiIWouldLikeToBuy can notify you when you receive a trade request in Path of Exile.

## Features
- Monitor your Path of Exile log file and send notifications via Telegram bot API
- Filter chat messages based on regular expressions, configurable via `config.yaml`

## Setup
1. Download HiIWouldLikeToBuy from the releases page on GitHub or optionally compile it yourself
2. Copy/rename `config.example.yaml` to `config.yaml`
3. Create a new Telegram bot using the [@BotFather](https://t.me/botfather), put the token into your `config.yaml`. You can find a tutorial here: https://core.telegram.org/bots/tutorial#obtain-your-bot-token
4. Send a message to your newly created bot and forward that message to the [@getidsbot](https://t.me/getidsbot), it will give you your chat ID, which you put into the `config.yaml`
5. If you are not using an English Path of Exile client you will also have to adapt the filter regexes in `config.yaml`
6. Change `logFile` to the location of your log file in `config.yaml`
7. You are done. Start `HiIWouldLikeToBuy.exe`. Pressing Enter will stop the tool.
8. Optionally: Verify that it works by sending yourself a trade request

### Regular Expressions
This tool uses C++ `std::regex`, which uses regular expressions in ECMAScript flavor. You can test your regular expressions on [regex101.com](https://regex101.com/) by setting the flavor to `ECMAScript (JavaScript)`