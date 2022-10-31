#include "TodoList.hpp"

namespace todolist
{

void TodoList::add(Task&& task)
{
    tasks.emplace(task.name, std::move(task));
}

void TodoList::done(const std::string& name)
{
    tasks.at(name).status = true;
}

void TodoList::update(const std::string& name, Task&& task)
{
    tasks.at(name) = std::move(task);
}

size_t TodoList::del(const std::string& name)
{
    return tasks.erase(name);
}

auto TodoList::begin() noexcept { return tasks.begin(); }
auto TodoList::begin() const noexcept { return tasks.begin(); }
auto TodoList::cbegin() const noexcept { return tasks.cbegin(); }

auto TodoList::end() noexcept { return tasks.end(); }
auto TodoList::end() const noexcept { return tasks.end(); }
auto TodoList::cend() const noexcept { return tasks.cend(); }

} //namespace todolist
