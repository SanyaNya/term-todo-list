#include "cli.hpp"
#include "Parser/Arg/VarArray.hpp"
#include "Parser/Arg/LongString.hpp"
#include "Parser/Arg/Date.hpp"
#include "Parser/Arg/Optional.hpp"
#include "Parser/Arg/Tuple.hpp"
#include "Parser/Arg/Predicate.hpp"
#include "utils/file_resource.hpp"
#include "TodoList.hpp"
#include <functional>

namespace todolist
{

using namespace Tokenizer::Tokens;

inline std::string to_string(std::string_view sv)
{
    return std::string{sv.begin(), sv.end()};
}

struct Path { static constexpr auto path = "todolist.data"; };
inline utils::file_resource<TodoList, Path> todo;

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
        todo.get().add(
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
            todo.get().done(to_string(std::get<1>(args).value));
        }
        catch(const std::out_of_range& e)
        {
            std::cout 
                << "Task \"" << std::get<1>(args).value << "\" not found\n";
        }
    }
};

template<typename T, typename R = decltype(T::value)>
static R read_arg(const char* invocation)
{
    std::string buf;

    std::cout << invocation;
    std::getline(std::cin, buf);

    const char* const bufcstr = buf.c_str();
    
    Tokenizer::Iterator begin(
            utils::ArgvIterator(&bufcstr, 1));
    Tokenizer::Iterator end(
            utils::ArgvIterator(&bufcstr, 1, utils::null_sentinel{}));

    std::optional<T> opt = Parser::parse_arg<T>(begin, end);

    if(opt)
        return R{opt.value().value};
    else 
        throw Parser::unexpected_token<Parser::LongString>();
}

struct UpdateCmd
{
    static constexpr std::string_view name = "update";
    std::tuple<Dspace, String> args;

    void execute()
    {
        try
        {
            Task& task = todo.get().at(std::string(std::get<1>(args).value));
            
            task.description = 
                read_arg<Parser::LongString>("Description: ");

            task.date = 
                read_arg<Parser::Date>("Date: ");

            task.category = 
                read_arg<
                    Tokenizer::Tokens::String, std::string>("Category: ");

            std::cout << "Task \"" << task.name << "\" updated\n";
        }
        catch(const std::out_of_range& e)
        {
            std::cout 
                << "Task \"" << std::get<1>(args).value << "\" not found\n";
        }
        
    }
};

struct DeleteCmd
{
    static constexpr std::string_view name = "delete";
    std::tuple<Dspace, String> args;

    void execute()
    {
        if(todo.get().del(to_string(std::get<1>(args).value)))
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
                            Parser::Predicate<Task>, 
                            Parser::Tuple<Dspace, Kand, Dspace>>>>> args;

    static void print(const Task& task)
    {
        std::cout 
            << "Name: "        << task.name        << "\n"
            << "Description: " << task.description << "\n"
            << "Date: "        
            << std::put_time(std::localtime(&task.date), "%Y-%m-%d %H:%M") 
            << "\n"
            << "Category: "    << task.category    << "\n"
            << "Status: "      << task.status      << "\n\n";
    }

    void execute()
    {
        if(!std::get<2>(args).value)
        {
            for(const auto&[name, task] : todo.get())
                print(task);
        }
        else
        {
            const auto& arr = 
                std::get<3>(std::get<2>(args).value.value().value).array;

            auto array_predicate = [&arr](const Task& t)
            {
                for(const auto& p : arr)
                    if(!p.value(t)) return false;

                return true;
            };

            for(const auto&[name, task] : todo.get())
                if(array_predicate(task))
                    print(task);
        }
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
