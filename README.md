# C++ Multithreaded Task Scheduler

A multithreaded task scheduler built in C++ using a **thread pool** and a **thread-safe producer-consumer queue**.

## Overview

This project demonstrates how multiple worker threads can process tasks concurrently while safely sharing a common task queue.

The scheduler creates a fixed number of worker threads. Tasks are added to a thread-safe queue, and available workers pick up and execute those tasks.

## Features

* Thread pool with multiple worker threads
* Thread-safe task queue
* Producer-consumer design
* `std::mutex` for synchronization
* `std::condition_variable` for efficient worker waiting
* Graceful thread shutdown
* Safe task submission
* CMake-based build system
* Tested and debugged using GDB

## Technologies Used

* **C++**
* C++11/14/17 threading facilities
* STL
* CMake
* Linux / WSL
* GDB

## Project Structure

```text
Cpp-Multithreaded-Task-Scheduler/
│
├── CMakeLists.txt
├── ThreadPool.h
├── ThreadPool.cpp
├── ThreadSafeQueue.h
├── Task.h
├── Task.cpp
├── main.cpp
├── .gitignore
└── README.md
```

## How It Works

```text
                Tasks
                  │
                  ▼
        ┌──────────────────┐
        │  Thread-Safe     │
        │     Queue        │
        └────────┬─────────┘
                 │
        ┌────────┼────────┐
        ▼        ▼        ▼
     Worker 1 Worker 2 Worker 3
        │        │        │
        ▼        ▼        ▼
      Task     Task     Task
```

1. Tasks are submitted to the scheduler.
2. Tasks are stored in a thread-safe queue.
3. Worker threads wait for available tasks.
4. A worker retrieves a task from the queue.
5. The task is executed independently.
6. Workers continue processing until the scheduler is shut down.
7. The destructor safely stops and joins all worker threads.

## Building the Project

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Running

From the `build` directory:

```bash
./scheduler
```

## Key Concepts Demonstrated

### Thread Pool

Instead of creating a new thread for every task, the scheduler maintains a fixed number of worker threads that can execute multiple tasks.

### Producer-Consumer

The main thread acts as a producer by submitting tasks, while worker threads act as consumers by retrieving and executing tasks.

### Mutex

A mutex protects shared data from being accessed by multiple threads at the same time.

### Condition Variable

Workers sleep while the queue is empty and are notified when a new task becomes available. This avoids unnecessary CPU usage from continuously checking the queue.

### Graceful Shutdown

When the scheduler is destroyed, worker threads are notified, finish pending work, and are properly joined before the program exits.

## What I Learned

Through this project, I gained practical experience with:

* C++ multithreading
* Thread synchronization
* Race-condition prevention
* Producer-consumer architecture
* Thread lifecycle management
* STL containers and synchronization primitives
* CMake
* Linux command-line development
* Debugging multithreaded programs using GDB

## Future Improvements

Possible future improvements include:

* Task priorities
* Dynamic worker scaling
* Task cancellation
* Task result/future support
* Performance benchmarking
