#include "cli.hpp"
#include "Parser/Arg/VarArray.hpp"
#include "Parser/Arg/LongString.hpp"
#include "Parser/Arg/Date.hpp"
#include "Parser/Arg/Optional.hpp"
#include "Parser/Arg/Tuple.hpp"
#include "Parser/Arg/Predicate.hpp"
#include "TodoList.hpp"

namespace todolist
{

using namespace Tokenizer::Tokens;

inline std::string to_string(std::string_view sv)
{
    return std::string{sv.begin(), sv.end()};
}

inline TodoList todo;

struct AddCmd
{
    static constexpr std::string_view name = "add";
    std::tuple<
        Dspace, String, 
        Dspace, Parser::LongString, 
        Dspace, Parser::Date,
        Dspace, String> args;

    void execute()
    {
        todo.add(
            Task{
                to_string(std::get<1>(args).value), 
                to_string(std::get<3>(args).value), 
                std::get<5>(args).value, 
                to_string(std::get<7>(args).value), 
                false});

        std::cout 
            << "Task \"" << std::get<1>(args).value << "\" added\n";
    }
};

struct DoneCmd
{
    static constexpr std::string_view name = "done";
    std::tuple<Dspace, String> args;

    void execute()
    {
        try
        {
            todo.done(to_string(std::get<1>(args).value));
        }
        catch(const std::out_of_range& e)
        {
            std::cout 
                << "Task \"" << std::get<1>(args).value << "\" not found\n";
        }
    }
};

struct UpdateCmd
{
    static constexpr std::string_view name = "update";
    std::tuple<Dspace, String> args;

    void execute()
    {
        //TODO
    }
};

struct DeleteCmd
{
    static constexpr std::string_view name = "delete";
    std::tuple<Dspace, String> args;

    void execute()
    {
        if(todo.del(to_string(std::get<1>(args).value)))
            std::cout << "Task \"" << std::get<1>(args).value << "\" deleted\n";
        else
            std::cout << "There is no task \"" << std::get<1>(args).value << "\"\n";
    }
};

struct SelectCmd
{
    static constexpr std::string_view name = "select";
    std::tuple<
        Dspace, Dstar, 
        Parser::Optional<
            Parser::Tuple<
                Dspace, Kwhere, 
                Dspace, Parser::VarArray<
                            Parser::Predicate, 
                            Parser::Tuple<Dspace, Kand, Dspace>>>>> args;

    void execute()
    {
        //TODO
    }
};

using Command =
    std::variant<
        AddCmd,
        DoneCmd,
        UpdateCmd,
        DeleteCmd,
        SelectCmd>;

} //namespace todolist

int main(int argc, const char* const argv[])
{
    todolist::CLI<todolist::Command> cli(++argv, --argc);
    try
    {
        auto cmdv = cli.parse();
        cli.execute(cmdv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
