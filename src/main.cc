#include <cstring>
#include <iostream>

#include "Driver/Driver.hh"
#include "Types.hh"

i32 main(i32 argc, char **argv) {
    if (argc > 1) {
        if (std::strcmp(argv[1], "--help") == 0) {
            std::cout << "Usage:\nlanguage filename (arg)\n\nAvailable "
                         "arguments:\n--tokens - print tokens from file\n--ast - print "
                         "Abstract Sybtax Tree\n--help - see this help\n\nWarning: do "
                         "NOT mix arguments\n";
        } else if (access(argv[1], F_OK) == -1) {
            std::cerr << "File with name " + std::string{argv[1]} +
                             " is not accessible\n";
        } else {
            Language::Driver::Driver driver{argv[1], argc, argv};
            driver.Run();
        }
    } else {
        std::cerr << "No input file was provided\n";
    }

    return 0;
}
