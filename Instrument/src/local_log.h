#pragma once
#include "../Include/Utilities/log.h"

spdlog::logger *local_logger();
void log_init(const char* path_name, int level);

#ifdef tLog
#undef tLog
#define tLog(...) tNLog(local_logger(), __VA_ARGS__)
#endif

#ifdef dLog
#undef dLog
#define dLog(...) dNLog(local_logger(), __VA_ARGS__)
#endif

#ifdef iLog
#undef iLog
#define iLog(...) iNLog(local_logger(), __VA_ARGS__)
#endif

#ifdef wLog
#undef wLog
#define wLog(...) wNLog(local_logger(), __VA_ARGS__)
#endif

#ifdef eLog
#undef eLog
#define eLog(...) eNLog(local_logger(), __VA_ARGS__)
#endif

#ifdef cLog
#undef cLog
#define cLog(...) cNLog(local_logger(), __VA_ARGS__)
#endif

