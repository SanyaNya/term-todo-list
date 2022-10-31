#pragma once

#include <unordered_map>
#include "Task.hpp"

namespace todolist
{

class TodoList
{
    std::unordered_map<std::string, Task> tasks;

public:
    void add(Task&& task);
    void done(const std::string& name);
    void update(const std::string& name, Task&& task);
    size_t del(const std::string& name);

    auto begin() noexcept;
    auto begin() const noexcept;
    auto cbegin() const noexcept;

    auto end() noexcept;
    auto end() const noexcept;
    auto cend() const noexcept;
};

} //namespace todolist
