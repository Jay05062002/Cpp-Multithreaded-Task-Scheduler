#pragma once

#include <string>
#include <functional>

class Task
{
private:
    int id;
    std::string name;
    std::function<void()> function;

public:
    Task(
        int id,
        const std::string& name,
        std::function<void()> function
    );

    void execute();

    int getId() const;
    std::string getName() const;
};