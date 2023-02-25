#ifndef TYPE_HH
#define TYPE_HH

#include "Types.hh"

namespace Language {
namespace AST {
/// Enum of types of variables, arguments, etc.
enum class DataType : u8 {
  Void,
  Int8,
  Int16,
  Int32,
  Int64,
  UInt8,
  UInt16,
  UInt32,
  UInt64,
};
} // namespace AST
} // namespace Language

#endif