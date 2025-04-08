#pragma once
#include "logger.hh"

namespace Parrot {
  // log
  template<LogLevel Level, class... Args>
  void Logger::log(strview scope, strview fmt, const Args&... args) {
    if (uint(Level) >= uint(getLevel(scope))) {
      logHead(scope, Level);
      logBody(fmt, args...);
    }
  }
  // :: trace
  template<class... Args>
  void Logger::logTrace(strview scope, strview fmt, const Args&... args) {
    log<LogLevel::TRACE>(scope, fmt, args...);
  }
  // :: debug
  template<class... Args>
  void Logger::logDebug(strview scope, strview fmt, const Args&... args) {
    log<LogLevel::DEBUG>(scope, fmt, args...);
  }
  // :: info
  template<class... Args>
  void Logger::logInfo(strview scope, strview fmt, const Args&... args) {
    log<LogLevel::INFO>(scope, fmt, args...);
  }
  // :: warning
  template<class... Args>
  void Logger::logWarning(strview scope, strview fmt, const Args&... args) {
    log<LogLevel::WARNING>(scope, fmt, args...);
  }
  // :: error
  template<class... Args>
  void Logger::logError(strview scope, strview fmt, const Args&... args) {
    log<LogLevel::ERROR>(scope, fmt, args...);
  }

  // logBody
  template<class First, class... Rest>
  void Logger::logBody(strview fmt, const First& first, const Rest&... rest) {
    for (auto it = fmt.begin(); it != fmt.end(); ++it) {
      if (std::next(it) != fmt.end()) {
        if (*it == '{' && *std::next(it) == '}') {
          cout << first;
          return logBody(strview(std::next(it, 2), fmt.end()), rest...);
        }
      }
      cout << *it;
    }
  }
}