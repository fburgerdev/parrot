#pragma once
#include "common.hh"

namespace Parrot {
  // LogLevel
  enum class LogLevel {
    TRACE, DEBUG, INFO, WARNING, ERROR
  };
  // Logger
  class Logger {
  public:
    // (constructor)
    Logger(strview name);

    // log
    template<LogLevel Level, class... Args>
    void log(strview scope, strview fmt, const Args&... args);
    template<class... Args>
    void logTrace(strview scope, strview fmt, const Args&... args);
    // :: debug
    template<class... Args>
    void logDebug(strview scope, strview fmt, const Args&... args);
    // :: info
    template<class... Args>
    void logInfo(strview scope, strview fmt, const Args&... args);
    // :: warning
    template<class... Args>
    void logWarning(strview scope, strview fmt, const Args&... args);
    // :: error
    template<class... Args>
    void logError(strview scope, strview fmt, const Args&... args);

    // level
    // :: get
    LogLevel getLevel() const;
    LogLevel getLevel(strview scope) const;
    // :: set
    void setLevel(LogLevel level);
    void setLevel(strview scope, LogLevel level);
  private:
    void logHead(strview scope, LogLevel level);
    void logBody(strview fmt);
    template<class First, class... Rest>
    void logBody(strview fmt, const First& first, const Rest&... rest);

    string _name;
    Map<string, LogLevel> _levels;
  };

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