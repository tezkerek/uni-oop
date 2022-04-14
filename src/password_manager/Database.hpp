#pragma once

#include <memory>
#include <ostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "Entry.hpp"
#include "Group.hpp"

namespace passman {

class Database {
protected:
    std::vector<Group> groups;
    std::unordered_map<std::string, std::size_t> nameToGroupIndexMap;

public:
    [[nodiscard]] const Group &getGroup(const std::string &name) const;
    void addGroup(const std::string &name);

    template <class EntryT>
    void addEntry(const std::string &groupName, const EntryT &entry);
    friend std::ostream &operator<<(std::ostream &os, const Database &db);
};

std::ostream &operator<<(std::ostream &os, const Database &db);

class InvalidGroup : public std::invalid_argument {
public:
    using std::invalid_argument::invalid_argument;
};

class GroupAlreadyExists : public InvalidGroup {
public:
    explicit GroupAlreadyExists(const std::string &groupName);
};

class GroupDoesNotExist : public InvalidGroup {
public:
    explicit GroupDoesNotExist(const std::string &groupName);
};

template <class EntryT>
void Database::addEntry(const std::string &groupName, const EntryT &entry) {
    try {
        groups.at(nameToGroupIndexMap.at(groupName)).addEntry<EntryT>(entry);
    } catch (const std::out_of_range &e) {
        throw GroupDoesNotExist(groupName);
    }
}

} // namespace passman
