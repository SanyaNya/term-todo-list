#pragma once

#include <type_traits>
#include <iterator>

namespace todolist::utils
{

template<typename F>
class func_iterator
{
    F func;
    size_t count;

public:
    using iterator_category = std::input_iterator_tag;
    using value_type = std::invoke_result_t<decltype(func)>;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = int;

    func_iterator(F f, size_t count_) noexcept : func(f), count(count_) {}

    bool operator!=(func_iterator it) const noexcept
    {
        return count != it.count;
    }

    value_type operator*() const noexcept(noexcept(func()))
    {
        return func();
    }

    func_iterator& operator++() noexcept
    {
        ++count;

        return *this; 
    }
};

template<typename F>
func_iterator(F, size_t) -> func_iterator<F>;

} //namespace todolist::utils
