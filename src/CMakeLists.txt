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

# Enable for easy local testing
# configure_file("${CMAKE_SOURCE_DIR}/config.yaml" "${CMAKE_CURRENT_BINARY_DIR}/config.yaml" COPYONLY)

install(TARGETS ${APP_NAME}
  RUNTIME_DEPENDENCY_SET ${APP_NAME}_RUNTIME_DEPS
  DESTINATION ${CMAKE_INSTALL_PREFIX})

LIST(APPEND PRE_EXCLUDE_REGEXES "api-ms-.*")
LIST(APPEND PRE_EXCLUDE_REGEXES "ext-ms-.*")
LIST(APPEND POST_EXCLUDE_REGEXES ".*Windows[\\/].*")

install(RUNTIME_DEPENDENCY_SET ${APP_NAME}_RUNTIME_DEPS
  PRE_EXCLUDE_REGEXES ${PRE_EXCLUDE_REGEXES}
  POST_EXCLUDE_REGEXES ${POST_EXCLUDE_REGEXES}
  DESTINATION "${CMAKE_INSTALL_PREFIX}")

install(FILES "${CMAKE_SOURCE_DIR}/config.example.yaml"
  DESTINATION "${CMAKE_INSTALL_PREFIX}")
