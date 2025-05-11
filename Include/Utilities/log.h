#pragma once

#include "../Third/spdlog/spdlog.h"

#include <QtCore/qglobal.h>

#if defined(UTILITIES_LIBRARY)
#  define UTILITIESHARED_EXPORT Q_DECL_EXPORT
#else
#  define UTILITIESHARED_EXPORT Q_DECL_IMPORT
#endif


namespace Log {

	UTILITIESHARED_EXPORT bool setup(const char* file_path_name, int level, const char* log_name = "default"
		, uint32_t max_size = 1 << 23 , uint32_t max_files = 5);
	UTILITIESHARED_EXPORT void set_level(int);
	UTILITIESHARED_EXPORT spdlog::logger* get_logger();
	UTILITIESHARED_EXPORT spdlog::logger* get_logger(const char* log_name);
}


#define tLog(...) SPDLOG_LOGGER_TRACE(Log::get_logger(), __VA_ARGS__)
#define dLog(...) SPDLOG_LOGGER_DEBUG(Log::get_logger(), __VA_ARGS__)
#define iLog(...) SPDLOG_LOGGER_INFO(Log::get_logger(),__VA_ARGS__)
#define wLog(...) SPDLOG_LOGGER_WARN(Log::get_logger(),__VA_ARGS__)
#define eLog(...) SPDLOG_LOGGER_ERROR(Log::get_logger(),__VA_ARGS__)
#define cLog(...) SPDLOG_LOGGER_CRITICAL(Log::get_logger(),__VA_ARGS__)

#define tNLog(l, ...) SPDLOG_LOGGER_TRACE(l, __VA_ARGS__)
#define dNLog(l, ...) SPDLOG_LOGGER_DEBUG(l, __VA_ARGS__)
#define iNLog(l, ...) SPDLOG_LOGGER_INFO(l,__VA_ARGS__)
#define wNLog(l, ...) SPDLOG_LOGGER_WARN(l,__VA_ARGS__)
#define eNLog(l, ...) SPDLOG_LOGGER_ERROR(l,__VA_ARGS__)
#define cNLog(l, ...) SPDLOG_LOGGER_CRITICAL(l,__VA_ARGS__)

