#pragma once

#include <LogWatcher.h>

class INotifier
{
public:
  virtual ~INotifier() = default;
  virtual void notify(const LogWatcher::ChatMessage& message) = 0;
};
