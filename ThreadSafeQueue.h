#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template <typename T>
class ThreadSafeQueue
{
private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable condition;

    bool stopped = false;

public:
    void push(T value);

    std::optional<T> pop();

    void shutdown();

    bool empty() const;
};


template <typename T>
void ThreadSafeQueue<T>::push(T value)
{
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (stopped)
        {
            return;
        }

        queue.push(std::move(value));
    }

    condition.notify_one();
}


template <typename T>
std::optional<T> ThreadSafeQueue<T>::pop()
{
    std::unique_lock<std::mutex> lock(mutex);

    condition.wait(lock, [this]()
    {
        return !queue.empty() || stopped;
    });

    if (queue.empty() && stopped)
    {
        return std::nullopt;
    }

    T value = std::move(queue.front());

    queue.pop();

    return value;
}


template <typename T>
void ThreadSafeQueue<T>::shutdown()
{
    {
        std::lock_guard<std::mutex> lock(mutex);

        stopped = true;
    }

    condition.notify_all();
}


template <typename T>
bool ThreadSafeQueue<T>::empty() const
{
    std::lock_guard<std::mutex> lock(mutex);

    return queue.empty();
}