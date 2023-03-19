#ifndef PRINT_HH
#define PRINT_HH

#include <iostream>

#include "Types.hh"

namespace Language {
namespace Print {
inline void MakeOffset(const i32 offset) {
    for (i32 i{}; i < offset; ++i) {
        std::cout << "  ";
    }
}
} // namespace Print
} // namespace Language

#endif
