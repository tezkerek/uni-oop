#include <ostream>
#include <stdexcept>
#include <utility>

#include "Database.hpp"

namespace passman {

const Group &Database::getGroup(const std::string &name) const {
    try {
        return groups.at(nameToGroupIndexMap.at(name));
    } catch (const std::out_of_range &e) {
        throw GroupDoesNotExist(name);
    }
}

void Database::addGroup(const std::string &name) {
    if (nameToGroupIndexMap.contains(name)) {
        throw GroupAlreadyExists(name);
    }

    groups.emplace_back(name);
    nameToGroupIndexMap[name] = groups.size() - 1;
}

std::ostream &operator<<(std::ostream &os, const Database &db) {
    os << "Database {\n";
    for (const auto &group : db.groups) {
        os << group << ",\n";
    }
    os << "}";

    return os;
}

GroupAlreadyExists::GroupAlreadyExists(const std::string &groupName)
    : InvalidGroup("Group \"" + groupName + "\" already exists.") {}

GroupDoesNotExist::GroupDoesNotExist(const std::string &groupName)
    : InvalidGroup("Group \"" + groupName + "\" does not exist.") {}

} // namespace passman
