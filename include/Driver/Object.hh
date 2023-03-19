#ifndef OBJECT_HH
#define OBJECT_HH

#include <any>

namespace Language {
namespace Driver {
struct Object {
    std::any Value;

    Object() : Value(std::any()) {}
    Object(std::any value) : Value(value) {}
};
} // namespace Driver
} // namespace Language

#endif
