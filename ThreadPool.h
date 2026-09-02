#pragma once

#include <vector>
#include <thread>
#include <string>
#include <functional>
#include <mutex>

#include "Task.h"
#include "ThreadSafeQueue.h"

class ThreadPool
{
private:
    ThreadSafeQueue<Task> taskQueue;
    std::vector<std::thread> workers;

    bool stopped = false;
    std::mutex stateMutex;

    void worker(int workerId);

public:
    explicit ThreadPool(int numberOfWorkers);

    ~ThreadPool();

    bool submit(
        int id,
        const std::string& name,
        std::function<void()> function
    );

    void shutdown();
};