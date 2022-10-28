TEST("TokenIterator",
    SUBTEST("Empty", []()
    {
        const char* argv[]{};
        int argc = 0;

        using namespace todolist;

        utils::ArgvIterator argv_begin(argv, argc);
        utils::ArgvIterator argv_end(argv, argc, utils::null_sentinel{});

        Tokenizer::Iterator<utils::ArgvIterator> it(argv_begin);
        Tokenizer::Iterator<utils::ArgvIterator> end(argv_end);

        assert(it == end);
    }),
    SUBTEST("Word::Keyword", []()
    {
        const char* argv[]
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

        int argc = sizeof(argv)/sizeof(*argv);

        using namespace todolist;

        utils::ArgvIterator argv_begin(argv, argc);
        utils::ArgvIterator argv_end(argv, argc, utils::null_sentinel{});
    })
)
