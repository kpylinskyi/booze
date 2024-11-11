#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <boost/asio.hpp>
#include <future>
#include <thread>
#include <vector>
#include <type_traits>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadPool
{
  public:
    static ThreadPool& getInstance();

    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>;

    ThreadPool(ThreadPool&) = delete;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

  private:
    ThreadPool(std::size_t nr_threads = std::thread::hardware_concurrency());
    ~ThreadPool();

    void worker();

    std::vector<std::thread> _workers;
    std::mutex _mutex;
    std::condition_variable _cv;
    std::queue<std::function<void()>> _queue;
    bool _stop;
};

template <typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
{
    using return_type = std::invoke_result_t<F, Args...>;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> result = task->get_future();
    {
        std::unique_lock<std::mutex> lock(_mutex);
        if (_stop)
        {
            throw std::runtime_error("ThreadPool has been stopped");
        }
        _queue.emplace([task]() { (*task)(); });
    }
    _cv.notify_one();
    return result;
}

#endif