#ifndef EXCEPTION_HH
#define EXCEPTION_HH

#include <exception>
#include <string>
#include <string_view>

namespace Language {
namespace Parse {
/// Parsing exception class
class ParseException : public std::exception {
  std::string Message;

 public:
  ParseException(const std::string& message) : Message(message) {}

  const char *what() const noexcept override { return Message.c_str(); }
};
} // namespace Parse
} // namespace Language

#endif
