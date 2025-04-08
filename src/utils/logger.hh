#pragma once
#include "common.hh"

namespace Parrot {
  enum class LogLevel {
    TRACE, DEBUG, INFO, WARNING, ERROR
  };
  class Logger {
  public:
    Logger(strview name);

    template<LogLevel Level, class... Args>
    void log(strview scope, strview fmt, const Args&... args);
    template<class... Args>
    void logTrace(strview scope, strview fmt, const Args&... args);
    template<class... Args>
    void logDebug(strview scope, strview fmt, const Args&... args);
    template<class... Args>
    void logInfo(strview scope, strview fmt, const Args&... args);
    template<class... Args>
    void logWarning(strview scope, strview fmt, const Args&... args);
    template<class... Args>
    void logError(strview scope, strview fmt, const Args&... args);

    LogLevel getLevel() const;
    LogLevel getLevel(strview scope) const;
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