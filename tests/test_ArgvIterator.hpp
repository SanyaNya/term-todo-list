TEST("ArgvIterator",
    SUBTEST("Empty args", []()
    {
        const char* argv[]{};
        int argc = 0;

        using namespace todolist::utils;

        ArgvIterator it(argv, argc);
        ArgvIterator end(argv, argc, null_sentinel{});

        assert(*it == null_sentinel{});
    })))
