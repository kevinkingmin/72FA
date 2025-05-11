#include "Utilities/log.h"

#include <vector>
#include <memory>
#include "spdlog/common.h"
#include "spdlog/sinks/rotating_file_sink.h"
#ifdef _MSC_VER
#include "spdlog/sinks/msvc_sink.h"
#endif

namespace Log {
	using namespace  spdlog;
	bool setup(const char* file_path_name, int level, const char* log_name, uint32_t max_size, uint32_t max_files)
	{
		std::vector<sink_ptr> sinks;
#ifdef _MSC_VER
		sinks.push_back(std::make_shared<sinks::msvc_sink_mt>());
#endif
		sinks.push_back(std::make_shared<sinks::rotating_file_sink_mt>(file_path_name, max_size, max_files));
		auto l = std::make_shared<logger>(log_name, sinks.begin(), sinks.end());
		l->set_level(static_cast<level::level_enum>(level));
		l->flush_on(level::err);

		if (strcmp(log_name, "default") == 0)
			spdlog::set_default_logger(l);
        else
            spdlog::register_logger(l);

        l->set_pattern("[%Y-%m-%d %H:%M:%S:%e] %^[%L]%$ [%t][%s|%#][%!] %v");
		using namespace std::chrono_literals;
		spdlog::flush_every(3s);
		return true;
	}

	spdlog::logger* get_logger()
	{
		return spdlog::default_logger_raw();
	}

	spdlog::logger* get_logger(const char* log_name)
	{
		assert(spdlog::get(log_name));
		return spdlog::get(log_name).get();
	}
}
