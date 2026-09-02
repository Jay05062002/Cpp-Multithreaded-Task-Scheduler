#include "Task.h"

Task::Task(
    int id,
    const std::string& name,
    std::function<void()> function
)
    : id(id),
      name(name),
      function(std::move(function))
{
}

void Task::execute()
{
    function();
}

int Task::getId() const
{
    return id;
}

std::string Task::getName() const
{
    return name;
}