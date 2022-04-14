#include "Group.hpp"

#include <memory>
#include <ostream>
#include <string>

namespace passman {

Group::Group(std::string name) : name(std::move(name)) {}

Group::Group(const Group &rhs) {
    name = rhs.name;
    for (const auto &entry : rhs.entries) {
        entries.push_back(entry->clone());
    }
}

std::string Group::getName() const noexcept { return name; }

const decltype(Group::entries) &Group::getEntries() const noexcept {
    return entries;
}

std::ostream &operator<<(std::ostream &os, const Group &group) {
    os << "Group \"" << group.getName() << "\" {\n";
    for (const auto &entry : group.entries) {
        os << *entry << ",\n";
    }
    os << "}";

    return os;
}

} // namespace passman
