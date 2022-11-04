#include "cli.hpp"
#include "Command.hpp"

int main(int argc, const char* const argv[])
{
    todolist::CLI<todolist::Command> cli(++argv, --argc);
    try
    {
        cli.parse_and_exec();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
