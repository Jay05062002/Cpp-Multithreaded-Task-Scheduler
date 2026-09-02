#include "ThreadPool.h"

#include <iostream>
#include <optional>


ThreadPool::ThreadPool(int numberOfWorkers)
{
    for (int i = 1; i <= numberOfWorkers; ++i)
    {
        workers.emplace_back(
            &ThreadPool::worker,
            this,
            i
        );
    }
}


ThreadPool::~ThreadPool()
{
    shutdown();
}


void ThreadPool::worker(int workerId)
{
    while (true)
    {
        std::optional<Task> task = taskQueue.pop();

        if (!task)
        {
            break;
        }

        std::cout
            << "Worker "
            << workerId
            << " received: "
            << task->getName()
            << "\n";

        task->execute();
    }

    std::cout
        << "Worker "
        << workerId
        << " shutting down\n";
}


bool ThreadPool::submit(
    int id,
    const std::string& name,
    std::function<void()> function
)
{
    {
        std::lock_guard<std::mutex> lock(stateMutex);

        if (stopped)
        {
            return false;
        }
    }

    Task task(
        id,
        name,
        std::move(function)
    );

    taskQueue.push(std::move(task));

    return true;
}


void ThreadPool::shutdown()
{
    {
        std::lock_guard<std::mutex> lock(stateMutex);

        if (stopped)
        {
            return;
        }

        stopped = true;
    }

    taskQueue.shutdown();

    for (std::thread& workerThread : workers)
    {
        if (workerThread.joinable())
        {
            workerThread.join();
        }
    }
}