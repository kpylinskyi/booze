#include "core/thread_pool.hpp"

ThreadPool& ThreadPool::getInstance()
{
    static ThreadPool instance;
    return instance;
}

ThreadPool::ThreadPool(std::size_t nr_workers)
{
    _stop = false;
    for (auto i{0}; i < nr_workers; i++)
    {
        _workers.emplace_back(&ThreadPool::worker, this);
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _stop = true;
    }

    _cv.notify_all();
    for (auto& worker : _workers)
    {
        worker.join();
    }
}

void ThreadPool::worker()
{
    for (;;)
    {
        std::function<void()> cur_task;
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _cv.wait(lock, [this]() { return _stop || !_queue.empty(); });

            if (_stop && _queue.empty())
                break;
            if (_queue.empty())
                continue;

            cur_task = _queue.front();
            _queue.pop();
        }
        cur_task();
    }
}
