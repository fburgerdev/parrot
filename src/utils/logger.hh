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
}
#include "logger_impl.hh"