#include "cli.hpp"
#include "Parser/Arg/VarArray.hpp"
#include "Parser/Arg/LongString.hpp"
#include "Parser/Arg/Date.hpp"

using namespace todolist;
using namespace todolist::Tokenizer::Tokens;

struct AddCommand
{
    static constexpr std::string_view name = "add";
    std::tuple<Dspace, String, Dequal, Parser::Date> args;

    void execute()
    {
        std::cout << "Command add: " 
                  << std::get<1>(args).value << "=\"";
        auto d = std::get<3>(args);
        std::tm t = *std::localtime(&d.value);
        std::cout << t.tm_year << "-" << t.tm_mon << "-" << t.tm_mday << " " << t.tm_hour << ":" << t.tm_min << "\"\n";
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
