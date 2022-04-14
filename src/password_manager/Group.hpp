#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "Entry.hpp"

namespace passman {

class Group {
protected:
    std::string name;
    std::vector<std::unique_ptr<Entry>> entries;

public:
    explicit Group(std::string name);
    Group(const Group &rhs);

    Group &operator=(const Group &rhs);

    [[nodiscard]] std::string getName() const noexcept;
    [[nodiscard]] const decltype(entries) &getEntries() const noexcept;

    template <class EntryT> void addEntry(const EntryT &entry) noexcept;

    friend std::ostream &operator<<(std::ostream &os, const Group &group);
};

std::ostream &operator<<(std::ostream &os, const Group &group);

template <class EntryT> void Group::addEntry(const EntryT &entry) noexcept {
    entries.push_back(std::make_unique<EntryT>(entry));
}

} // namespace passman
