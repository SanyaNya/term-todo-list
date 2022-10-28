TEST("ArgvIterator",
    SUBTEST("Empty args", []()
    {
        const char* argv[]{};
        int argc = 0;

        using namespace todolist::utils;

        ArgvIterator it(argv, argc);
        ArgvIterator end(argv, argc, null_sentinel{});

        assert(it == end);
    }),
    SUBTEST("One arg", []()
    {
        const char* argv[]{ "word=123" };
        int argc = 1;

        using namespace todolist::utils;

        ArgvIterator it(argv, argc);
        ArgvIterator end(argv, argc, null_sentinel{});

        assert(it.token() == "word=123");
        assert(std::equal(it, end, argv[0]));
    }),
    SUBTEST("Many args", []()
    {
        const char* argv[]
            { "a", "abcd", "321.12", "qwerty=\"123 321\"" };

        int argc = sizeof(argv)/sizeof(*argv);

        std::string s;
        for(const char* arg : argv)
        {
            s += arg;
            s += ' ';
        }
        s.pop_back();

        using namespace todolist::utils;

        ArgvIterator it(argv, argc);
        ArgvIterator end(argv, argc, null_sentinel{});

        assert(std::equal(it, end, s.begin()));

        for(const char* arg : argv)
        {
            assert(it.token() == arg);
            it.to_next_token();
        }
    })
)
