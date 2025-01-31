#pragma once
#include "logger.hh"

namespace Parrot {
  // (global) engine_logger
  inline Logger engine_logger = Logger("parrot");
}
// macros
#if !defined(PARROT_NO_LOG)
#define LOGGER ::Parrot::engine_logger
// :: global
#define LOG_GLOBAL_TRACE(fmt,...) LOGGER.logTrace(strview(), fmt, __VA_ARGS__)
#define LOG_GLOBAL_DEBUG(fmt,...) LOGGER.logDebug(strview(), fmt, __VA_ARGS__)
#define LOG_GLOBAL_INFO(fmt,...) LOGGER.logInfo(strview(), fmt, __VA_ARGS__)
#define LOG_GLOBAL_WARNING(fmt,...) LOGGER.logWarning(strview(), fmt, __VA_ARGS__)
#define LOG_GLOBAL_ERROR(fmt,...) LOGGER.logError(strview(), fmt, __VA_ARGS__)
// :: core
#define LOG_CORE_TRACE(fmt, ...) LOGGER.logTrace("core", fmt, __VA_ARGS__)
#define LOG_CORE_DEBUG(fmt, ...) LOGGER.logDebug("core", fmt, __VA_ARGS__)
#define LOG_CORE_INFO(fmt, ...) LOGGER.logInfo("core", fmt, __VA_ARGS__)
#define LOG_CORE_WARNING(fmt, ...) LOGGER.logWarning("core", fmt, __VA_ARGS__)
#define LOG_CORE_ERROR(fmt, ...) LOGGER.logError("core", fmt, __VA_ARGS__)
// :: app
#define LOG_APP_TRACE(fmt, ...) LOGGER.logTrace("app", fmt, __VA_ARGS__)
#define LOG_APP_DEBUG(fmt, ...) LOGGER.logDebug("app", fmt, __VA_ARGS__)
#define LOG_APP_INFO(fmt, ...) LOGGER.logInfo("app", fmt, __VA_ARGS__)
#define LOG_APP_WARNING(fmt, ...) LOGGER.logWarning("app", fmt, __VA_ARGS__)
#define LOG_APP_ERROR(fmt, ...) LOGGER.logError("app", fmt, __VA_ARGS__)
// :: asset
#define LOG_ASSET_TRACE(fmt, ...) LOGGER.logTrace("asset", fmt, __VA_ARGS__)
#define LOG_ASSET_DEBUG(fmt, ...) LOGGER.logDebug("asset", fmt, __VA_ARGS__)
#define LOG_ASSET_INFO(fmt, ...) LOGGER.logInfo("asset", fmt, __VA_ARGS__)
#define LOG_ASSET_WARNING(fmt, ...) LOGGER.logWarning("asset", fmt, __VA_ARGS__)
#define LOG_ASSET_ERROR(fmt, ...) LOGGER.logError("asset", fmt, __VA_ARGS__)
// :: ecs
#define LOG_ECS_TRACE(fmt, ...) LOGGER.logTrace("ecs", fmt, __VA_ARGS__)
#define LOG_ECS_DEBUG(fmt, ...) LOGGER.logDebug("ecs", fmt, __VA_ARGS__)
#define LOG_ECS_INFO(fmt, ...) LOGGER.logInfo("ecs", fmt, __VA_ARGS__)
#define LOG_ECS_WARNING(fmt, ...) LOGGER.logWarning("ecs", fmt, __VA_ARGS__)
#define LOG_ECS_ERROR(fmt, ...) LOGGER.logError("ecs", fmt, __VA_ARGS__)
// :: graphics
#define LOG_GRAPHICS_TRACE(fmt, ...) LOGGER.logTrace("graphics", fmt, __VA_ARGS__)
#define LOG_GRAPHICS_DEBUG(fmt, ...) LOGGER.logDebug("graphics", fmt, __VA_ARGS__)
#define LOG_GRAPHICS_INFO(fmt, ...) LOGGER.logInfo("graphics", fmt, __VA_ARGS__)
#define LOG_GRAPHICS_WARNING(fmt, ...) LOGGER.logWarning("graphics", fmt, __VA_ARGS__)
#define LOG_GRAPHICS_ERROR(fmt, ...) LOGGER.logError("graphics", fmt, __VA_ARGS__)
// :: math
#define LOG_MATH_TRACE(fmt, ...) LOGGER.logTrace("math", fmt, __VA_ARGS__)
#define LOG_MATH_DEBUG(fmt, ...) LOGGER.logDebug("math", fmt, __VA_ARGS__)
#define LOG_MATH_INFO(fmt, ...) LOGGER.logInfo("math", fmt, __VA_ARGS__)
#define LOG_MATH_WARNING(fmt, ...) LOGGER.logWarning("math", fmt, __VA_ARGS__)
#define LOG_MATH_ERROR(fmt, ...) LOGGER.logError("math", fmt, __VA_ARGS__)
// :: window
#define LOG_WINDOW_TRACE(fmt, ...) LOGGER.logTrace("window", fmt, __VA_ARGS__)
#define LOG_WINDOW_DEBUG(fmt, ...) LOGGER.logDebug("window", fmt, __VA_ARGS__)
#define LOG_WINDOW_INFO(fmt, ...) LOGGER.logInfo("window", fmt, __VA_ARGS__)
#define LOG_WINDOW_WARNING(fmt, ...) LOGGER.logWarning("window", fmt, __VA_ARGS__)
#define LOG_WINDOW_ERROR(fmt, ...) LOGGER.logError("window", fmt, _fmt, _VA_ARGS__)
#endif