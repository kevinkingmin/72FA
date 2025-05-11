#ifndef ASYNC_TASK_H
#define ASYNC_TASK_H

#include <functional>
#include <chrono>
#include <system_error>
#include <memory>

#include <QtCore/qglobal.h>

#if defined(UTILITIES_LIBRARY)
#  define UTILITIESHARED_EXPORT Q_DECL_EXPORT
#else
#  define UTILITIESHARED_EXPORT Q_DECL_IMPORT
#endif

namespace asio{
	class io_context;
	class executor;
	template<typename T>
	struct wait_traits;
	template <typename Clock, typename WaitTraits = wait_traits<Clock>, typename Executor = executor>
	class basic_waitable_timer;
}

namespace AsyncTask{
    using F = std::function<void()>;
	using EF = std::function<void(std::error_code)>;

	class UTILITIESHARED_EXPORT AsyncTimer
	{
		using Clock = std::chrono::steady_clock;
		using Timer = asio::basic_waitable_timer<Clock>;
		using Ptr = std::unique_ptr<Timer>;
	public:
		AsyncTimer();
		~AsyncTimer();
		AsyncTimer(const AsyncTimer&) = delete;
		AsyncTimer& operator=(const AsyncTimer&) = delete;
		AsyncTimer(AsyncTimer&&) = delete;
		AsyncTimer& operator=(AsyncTimer&&) = delete;

		void async_wait(EF&& f);
		void expired_after(std::chrono::microseconds);
		void expired_at(Clock::time_point);
		void cancel(std::error_code&);
                void cancel();
	private:
		Ptr _timer;
	};

	UTILITIESHARED_EXPORT void start(uint32_t max_thread = 0);
	UTILITIESHARED_EXPORT void stop();
	UTILITIESHARED_EXPORT void post(F&& f);
	UTILITIESHARED_EXPORT asio::io_context* get_context();
	UTILITIESHARED_EXPORT bool op_aborted(const std::error_code& ec);
}
#endif
