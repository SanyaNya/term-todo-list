#pragma once

#include <unordered_map>
#include "serialization/serialization.hpp"
#include "Task.hpp"

namespace todolist
{

class TodoList
{
    std::unordered_map<std::string, Task> tasks;

    TodoList(decltype(tasks)&& t) : tasks(t) {}

public:
    TodoList() = default;

    void add(Task&& task)
    {
        tasks.emplace(task.name, std::move(task));
    }

    void done(const std::string& name)
    {
        tasks.at(name).status = true;
    }

    void update(const std::string& name, Task&& task)
    {
        tasks.at(name) = std::move(task);
    }

    size_t del(const std::string& name)
    {
        return tasks.erase(name);
    }

    Task& at(const std::string& name)
    {
        return tasks.at(name);
    }

    const Task& at(const std::string& name) const
    {
        return tasks.at(name);
    }

    auto begin() noexcept { return tasks.begin(); }
    auto begin() const noexcept { return tasks.begin(); }
    auto cbegin() const noexcept { return tasks.cbegin(); }

    auto end() noexcept { return tasks.end(); }
    auto end() const noexcept { return tasks.end(); }
    auto cend() const noexcept { return tasks.cend(); }

    void serialize(std::ostream& os) const
    {
        serialization::serialize(os, tasks);
    }
    static TodoList deserialize(std::istream& is)
    {
        return TodoList{serialization::deserialize<decltype(tasks)>(is)};
    }
};

} //namespace todolist
