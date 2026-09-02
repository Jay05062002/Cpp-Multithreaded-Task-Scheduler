cmake_minimum_required(VERSION 3.16)

project(TaskScheduler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(scheduler
    main.cpp
    Task.cpp
    ThreadPool.cpp
)

target_link_libraries(scheduler
    pthread
)