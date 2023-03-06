#ifndef DECL_BASE_HH
#define DECL_BASE_HH

#include <string>

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

  inline const std::string &GetName() const { return Name; }
  inline const std::string &GetType() const { return Type; }
};
} // namespace AST
} // namespace Language
#endif
