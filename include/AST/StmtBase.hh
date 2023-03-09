#ifndef STMTBASE_HH
#define STMTBASE_HH

#include <string>

#include "Print/Print.hh"
#include "Types.hh"

namespace Language {
namespace AST {
/// Base AST statement class
class Stmt {
 protected:
  std::string Type;

 public:
  Stmt() : Type("void") {}
  Stmt(const std::string &type) : Type(type) {}
  virtual ~Stmt() = default;

  /// Print Stmt as an AST element
  virtual void Print(const i32 offset = 0) { Print::MakeOffset(offset); };
  inline const std::string &GetType() const { return Type; }
};
} // namespace AST
} // namespace Language

#endif
