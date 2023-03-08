#ifndef DECL_BASE_HH
#define DECL_BASE_HH

#include <string>

#include "Print/Print.hh"
#include "Types.hh"

namespace Language {
namespace AST {

/// Base AST declaration class
class Decl {
 protected:
  std::string Name;
  std::string Type;

 public:
  Decl(const std::string &name, const std::string &type) : Name(name), Type(type) {}
  virtual ~Decl() = default;

  virtual void Print(i32 offset = 0) {
    Print::MakeOffset(offset);
  }

  inline const std::string &GetName() const { return Name; }
  inline const std::string &GetType() const { return Type; }
};
} // namespace AST
} // namespace Language
#endif
