#include "Utilities/async_task.h"
#include <thread>
#include <vector>
#include <cassert>

#include "asio/io_context.hpp"
#include "asio/executor_work_guard.hpp"
#include "asio/steady_timer.hpp"

namespace {
    using namespace AsyncTask;

    class AsyncTaskImpl final
        : public std::enable_shared_from_this<AsyncTaskImpl>
    {
        using Threads = std::vector<std::thread>;

      public:
        AsyncTaskImpl()
            : _work_guard(asio::make_work_guard(_context)) {}
        ~AsyncTaskImpl() { /*stop();*/ }	//call stop here is invalid, because reference cycle exist
											//then must call stop explicit

        AsyncTaskImpl(const AsyncTaskImpl &) = delete;
        AsyncTaskImpl &operator=(const AsyncTaskImpl &) = delete;
        AsyncTaskImpl(AsyncTaskImpl &&) = delete;
        AsyncTaskImpl &operator=(AsyncTaskImpl &&) = delete;

        void start(uint32_t max_thread)
        {
            assert(_threads.empty());
            if (_context.stopped())
                _context.restart();

            for (uint32_t i = 0; i < max_thread; ++i)
                _threads.push_back(std::thread(std::bind(&AsyncTaskImpl::run, shared_from_this())));
        }

        void stop()
        {
            _context.stop();
            for (auto &&t : _threads)
            {
                if (t.joinable())
                    t.join();
            }

            _threads.clear();
        }

        template <class F>
        void post(F &&f)
        {
            _context.post(std::move(f));
        }

        asio::io_context& get_context() { return _context; }

      private:
        void run() { _context.run(); }

        Threads _threads;
        asio::io_context _context;
        asio::executor_work_guard<asio::io_context::executor_type> _work_guard;
    };

    std::shared_ptr<AsyncTaskImpl> l_thread_pool=nullptr;
} // namespace

namespace AsyncTask{
    void start(uint32_t max_thread)
    {
        if(!max_thread)
            max_thread = std::thread::hardware_concurrency();
		if (!l_thread_pool)
			l_thread_pool = std::make_shared<AsyncTaskImpl>();
        
        l_thread_pool->start(max_thread);
    }

    void stop()
    {
        assert(l_thread_pool);
        l_thread_pool->stop();
		//l_thread_pool = nullptr; //need set? if so out context reference invalid will be a bug when post
    }

    void post(F&& f)
    {
        assert(l_thread_pool);
        l_thread_pool->post(std::move(f));
    }

    asio::io_context* get_context()
    {
        assert(l_thread_pool);
		if (!l_thread_pool)
			return nullptr;
        return &l_thread_pool->get_context();
    }

	UTILITIESHARED_EXPORT bool op_aborted(const std::error_code& ec)
	{
		return ec.value() == asio::error::operation_aborted;
	}

	AsyncTimer::AsyncTimer()
		:_timer(std::make_unique<Timer>(*AsyncTask::get_context()))
	{
	}

	AsyncTimer::~AsyncTimer()
	{
	}

	void AsyncTimer::async_wait(EF&& f)
	{
		_timer->async_wait(std::move(f));
	}

	void AsyncTimer::expired_after(std::chrono::microseconds ms)
	{
		_timer->expires_after(ms);
	}

	void AsyncTimer::expired_at(Clock::time_point tp)
	{
		_timer->expires_at(tp);
	}

	void AsyncTimer::cancel(std::error_code& ec)
	{
		_timer->cancel(ec);
	}

    void AsyncTimer::cancel()
    {
        std::error_code ec;
        cancel(ec);
    }
}
