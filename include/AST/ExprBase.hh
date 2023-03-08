#ifndef EXPRBASE_HH
#define EXPRBASE_HH

#include "AST/StmtBase.hh"

namespace Language {
namespace AST {
/// Base AST expression class
class Expr : public Stmt {
 public:
  Expr(const std::string &type) : Stmt(type) {}
};
}
} // namespace Language

#endif
