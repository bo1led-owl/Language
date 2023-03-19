#ifndef SCOPE_HH
#define SCOPE_HH

#include <memory>
#include <string>
#include <unordered_map>

#include "AST/Decl.hh"
#include "Driver/Object.hh"

namespace Language {
namespace Driver {
class Scope {
    std::unordered_map<std::string, std::shared_ptr<Object>> Variables;
    std::unordered_map<std::string, std::unique_ptr<AST::FnDecl>> Functions;
    std::shared_ptr<Scope> Parent;
    std::shared_ptr<Scope> TopParent;

  public:
    Scope(std::shared_ptr<Scope> parent, std::shared_ptr<Scope> topParent)
        : Parent(parent), TopParent(topParent) {}
    Scope(std::unordered_map<std::string, std::shared_ptr<Object>> &variables,
          std::shared_ptr<Scope> parent, std::shared_ptr<Scope> topParent)
        : Variables(variables), Parent(parent), TopParent(topParent) {}

    void SetTopParent(std::shared_ptr<Scope> topParent) {
        TopParent = topParent;
    }

    std::shared_ptr<Object> GetValue(const std::string &name) {
        if (Variables.contains(name)) {
            return Variables[name];
        }
        // null parent check is not needed, it is checked while parsing
        return Parent->GetValue(name);
    }

    void SetValue(const std::string &name, std::shared_ptr<Object> value) {
        Variables[name] = value;
    }

    std::shared_ptr<Object> ExecFn(const std::string &name,
                                   std::vector<std::shared_ptr<Object>> args) {
        std::unordered_map<std::string, std::shared_ptr<Object>> argValues;
        const std::unique_ptr<AST::FnDecl> &decl{Functions[name]};
        for (size_t i{}; i < args.size(); ++i) {
            argValues[decl->GetArgumentByIndex(i)->Name] = args[i];
        }
        // for (size_t i{}; i < args.size(); ++i) {
        //     const auto arg{decl->GetArgumentByIndex(i)};
        //     argValues[arg->Name] = args[i]->Exec(SelfPtr);
        // }
        return Functions[name]->Exec(std::make_shared<Scope>(argValues, nullptr, TopParent));
    }

    const std::unique_ptr<AST::FnDecl> &GetFnDecl(const std::string &name) {
        return Functions[name];
    }

    std::shared_ptr<Object> ExecFn(const std::string &name) {
        return Functions[name]->Exec(TopParent);
    }

    void AddVariable(const std::string &name, std::shared_ptr<Object> value) {
        Variables[name] = value;
    }

    void AddFunction(std::unique_ptr<AST::FnDecl> decl) {
        Functions[decl->GetName()] = std::move(decl);
    }
};
} // namespace Driver
} // namespace Language

#endif
