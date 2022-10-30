#include "cli.hpp"
#include "Parser/Arg/VarArray.hpp"

using namespace todolist;
using namespace todolist::Tokenizer::Tokens;

struct AddCommand
{
    static constexpr std::string_view name = "add";
    std::tuple<Dspace, String, Dequal, Dquotes, Parser::VarArray<String>, Dquotes> args;

    void execute()
    {
        std::cout << "Command add: " 
                  << std::get<1>(args).value << "=\"";
        for(auto&& e : std::get<4>(args).array)
            std::cout << e.value << " ";
        std::cout << "\"\n";
    }
};

struct DoneCommand
{
    static constexpr std::string_view name = "done";
    std::tuple<> args;

    void execute() {}
};

using Command =
    std::variant<
        AddCommand,
        DoneCommand>;

using TokenIterator = 
    Tokenizer::Iterator<
        utils::ArgvIterator>;

int main(int argc, const char* const argv[])
{
    CLI<Command> cli(++argv, --argc);
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
