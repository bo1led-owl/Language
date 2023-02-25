#ifndef EXCEPTION_HH
#define EXCEPTION_HH

#include <exception>
#include <string>
#include <string_view>

namespace Language {
namespace Parse {
class ParseException : public std::exception {
  std::string_view Message;

 public:
  ParseException(const std::string &message) : Message(message) {}

  std::string_view what() { return std::string_view{Message}; }
};
} // namespace Parse
} // namespace Language

#endif