#ifndef BINARY_OPS_HH
#define BINARY_OPS_HH

#include "Types.hh"

namespace Language {
namespace AST {
enum class BinaryExprKind : u8 {
  Plus,
  Minus,
  Multiply,
  Divide,
};
}
} // namespace Language

#endif