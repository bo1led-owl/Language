#include "Driver/Driver.hh"
#include "Types.hh"

#include <iostream>

i32 main(i32 argc, char **argv) {
    if (argc > 1) {
        Language::Driver::Driver driver{argv[1]};
        driver.Run();
    } else {
        std::cerr << "No input file was provided\n";
    }

    return 0;
}
