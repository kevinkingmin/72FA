#include "local_log.h"

static spdlog::logger* l_logger{};

spdlog::logger * local_logger()
{
	return l_logger;
}

void log_init(const char* path_name, int level)
{	
	Log::setup(path_name, level, "instrument");
	l_logger = Log::get_logger("instrument");
}
