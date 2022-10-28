#include <iostream>
#include <functional>
#include <array>
#include <vector>
#include <cassert>
#include "utils/ArgvIterator.hpp"

#define TEST(NAME, ...) std::pair{ std::string(NAME), std::vector{ __VA_ARGS__ } },
#define SUBTEST(NAME, ...) std::pair<std::string, std::function<void()>>{NAME, __VA_ARGS__}

std::array tests
{
#include "test_ArgvIterator.hpp"
};

int main()
{
    unsigned test_counter = 0;
    for(const auto&[tests_name, subtests] : tests)
    {
        std::cout << "Testing \"" << tests_name << "\"\n";
        std::cout << "-------------------------------------------------------------------\n";
        unsigned subtest_counter = 0;
        for(const auto&[subtest_name, subtest] : subtests)
        {
            std::cout << "[" << subtest_counter++ << "/" << subtests.size() << "] Running \"" << subtest_name << "\" " << std::flush;
            subtest();
            std::cout << " OK\n";

            test_counter++;
        }
        std::cout << "\nAll subtests passed [" << subtest_counter << "/" << subtest_counter << "]\n";
        std::cout << "-------------------------------------------------------------------\n\n";
    }

    std::cout << "All tests passed [" << test_counter << "/" << test_counter << "]\n";
}
