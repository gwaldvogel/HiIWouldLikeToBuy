include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(APP_NAME "HiIWouldLikeToBuy")
set(SOURCES
  "main.cpp"
  "Config.cpp"
  "Config.h"
  "LogWatcher.h"
  "LogWatcher.cpp"
  "notify/INotifier.h"
  "notify/TelegramNotifier.cpp"
  "notify/TelegramNotifier.h")

add_executable(${APP_NAME} ${SOURCES})

target_link_libraries(${APP_NAME}
  PRIVATE
  spdlog::spdlog_header_only
  httplib::httplib
  yaml-cpp
  OpenSSL::SSL
  OpenSSL::Crypto)

configure_file("${CMAKE_SOURCE_DIR}/config.yaml" "${CMAKE_CURRENT_BINARY_DIR}/config.yaml" COPYONLY)