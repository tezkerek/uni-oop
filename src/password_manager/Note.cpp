#include <regex>
#include <string>
#include <utility>

#include "Note.hpp"
#include "serialization.hpp"

namespace passman {

template <> void Note<std::string>::print(std::ostream &os) const {
    auto content = std::regex_replace(getContent(), std::regex("\n"), "⤶");
    os << "Note \"" << getName() << "\" { \"" << content << "\" }";
}

} // namespace passman
