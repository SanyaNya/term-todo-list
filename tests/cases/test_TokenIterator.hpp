TEST("TokenIterator",
    SUBTEST("Empty", []()
    {
        std::array<const char*, 0> argv{};
        auto[it, end] = token_iter_pair(argv);
        assert(it == end);
    }),

    SUBTEST("Word::Keyword", []()
    {
        size_t i = 0;
        std::array argv = 
        {
            "name", 
            "description", 
            "date", 
            "category", 
            "status", 
            "where", 
            "and", 
            "like"
        };

        for(auto[it, end] = token_iter_pair(argv); ; ++it, ++i)
        {
            using namespace todolist::Tokenizer::Tokens;
            check_keyword(it, end, i, argv[i]);
            
            if(++it != end) check_delim<Empty, Dspace>(it, end);
            else break;
        }

        using namespace todolist;
        assert(i+1 == std::variant_size_v<Tokenizer::Tokens::Keyword>);
    }),

    SUBTEST("Word::Number", []()
    {
        const std::array argv{ "0", "-123", "x32", "64qwerty", "2.16" };
        auto[it, end] = token_iter_pair(argv);

        using namespace todolist::Tokenizer::Tokens;

        check_num(it, end, 0);
        check_delim<Empty, Dspace>(++it, end);
        
        check_delim<Punctuation, Ddash>(++it, end);
        check_num(++it, end, 123);
        check_delim<Empty, Dspace>(++it, end);

        check_string(++it, end, "x32");
        check_delim<Empty, Dspace>(++it, end);

        check_string(++it, end, "64qwerty");
        check_delim<Empty, Dspace>(++it, end);

        check_num(++it, end, 2);
        check_delim<Punctuation, Ddot>(++it, end);
        check_num(++it, end, 16);
    }),

    SUBTEST("Word::String", []()
    {
        const std::array argv{ "asd123", "qwerty=\"a b\"" };
        auto[it, end] = token_iter_pair(argv);

        using namespace todolist::Tokenizer::Tokens;

        check_string(it, end, "asd123");
        check_delim<Empty, Dspace>(++it, end);

        check_string(++it, end, "qwerty");
        check_delim<Compare, Dequal>(++it, end);
        check_delim<Punctuation, Dquotes>(++it, end);
        check_string(++it, end, "a");
        check_delim<Empty, Dspace>(++it, end);
        check_string(++it, end, "b");
        check_delim<Punctuation, Dquotes>(++it, end);
    })
)
