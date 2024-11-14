#pragma once
#include "logger.hh"

namespace Parrot {
	// logger (only for engine code, not for client!)
	static inline Logger logger = Logger("parrot");
}
// macros
#if !defined(PARROT_NO_LOG)
// :: global
#define LOG_GLOBAL_TRACE(...) ::Parrot::logger.logTrace(strview(), __VA_ARGS__)
#define LOG_GLOBAL_DEBUG(...) ::Parrot::logger.logDebug(strview(), __VA_ARGS__)
#define LOG_GLOBAL_INFO(...) ::Parrot::logger.logInfo(strview(), __VA_ARGS__)
#define LOG_GLOBAL_WARNING(...) ::Parrot::logger.logWarning(strview(), __VA_ARGS__)
#define LOG_GLOBAL_ERROR(...) ::Parrot::logger.logError(strview(), __VA_ARGS__)
// :: asset
#define LOG_ASSET_TRACE(...) ::Parrot::logger.logTrace("asset", __VA_ARGS__)
#define LOG_ASSET_DEBUG(...) ::Parrot::logger.logDebug("asset", __VA_ARGS__)
#define LOG_ASSET_INFO(...) ::Parrot::logger.logInfo("asset", __VA_ARGS__)
#define LOG_ASSET_WARNING(...) ::Parrot::logger.logWarning("asset", __VA_ARGS__)
#define LOG_ASSET_ERROR(...) ::Parrot::logger.logError("asset", __VA_ARGS__)
// :: core
#define LOG_CORE_TRACE(...) ::Parrot::logger.logTrace("core", __VA_ARGS__)
#define LOG_CORE_DEBUG(...) ::Parrot::logger.logDebug("core", __VA_ARGS__)
#define LOG_CORE_INFO(...) ::Parrot::logger.logInfo("core", __VA_ARGS__)
#define LOG_CORE_WARNING(...) ::Parrot::logger.logWarning("core", __VA_ARGS__)
#define LOG_CORE_ERROR(...) ::Parrot::logger.logError("core", __VA_ARGS__)
// :: ecs
#define LOG_ECS_TRACE(...) ::Parrot::logger.logTrace("ecs", __VA_ARGS__)
#define LOG_ECS_DEBUG(...) ::Parrot::logger.logDebug("ecs", __VA_ARGS__)
#define LOG_ECS_INFO(...) ::Parrot::logger.logInfo("ecs", __VA_ARGS__)
#define LOG_ECS_WARNING(...) ::Parrot::logger.logWarning("ecs", __VA_ARGS__)
#define LOG_ECS_ERROR(...) ::Parrot::logger.logError("ecs", __VA_ARGS__)
// :: graphics
#define LOG_GRAPHICS_TRACE(...) ::Parrot::logger.logTrace("graphics", __VA_ARGS__)
#define LOG_GRAPHICS_DEBUG(...) ::Parrot::logger.logDebug("graphics", __VA_ARGS__)
#define LOG_GRAPHICS_INFO(...) ::Parrot::logger.logInfo("graphics", __VA_ARGS__)
#define LOG_GRAPHICS_WARNING(...) ::Parrot::logger.logWarning("graphics", __VA_ARGS__)
#define LOG_GRAPHICS_ERROR(...) ::Parrot::logger.logError("graphics", __VA_ARGS__)
// :: math
#define LOG_MATH_TRACE(...) ::Parrot::logger.logTrace("math", __VA_ARGS__)
#define LOG_MATH_DEBUG(...) ::Parrot::logger.logDebug("math", __VA_ARGS__)
#define LOG_MATH_INFO(...) ::Parrot::logger.logInfo("math", __VA_ARGS__)
#define LOG_MATH_WARNING(...) ::Parrot::logger.logWarning("math", __VA_ARGS__)
#define LOG_MATH_ERROR(...) ::Parrot::logger.logError("math", __VA_ARGS__)
// :: window
#define LOG_WINDOW_TRACE(...) ::Parrot::logger.logTrace("window", __VA_ARGS__)
#define LOG_WINDOW_DEBUG(...) ::Parrot::logger.logDebug("window", __VA_ARGS__)
#define LOG_WINDOW_INFO(...) ::Parrot::logger.logInfo("window", __VA_ARGS__)
#define LOG_WINDOW_WARNING(...) ::Parrot::logger.logWarning("window", __VA_ARGS__)
#define LOG_WINDOW_ERROR(...) ::Parrot::logger.logError("window", __VA_ARGS__)
#endif