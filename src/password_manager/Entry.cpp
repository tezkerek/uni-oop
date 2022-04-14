#include "Entry.hpp"
#include <memory>
#include <ostream>
#include <string>
#include <utility>

namespace passman {

Attribute::Attribute(std::string str) noexcept : value(std::move(str)) {}

Attribute &Attribute::operator=(const std::string &str) noexcept {
    value = str;
    return *this;
}

std::string Attribute::getValue() const noexcept { return value; }

Entry::Entry(std::string name, std::string uuid) noexcept
    : name(std::move(name)), uuid(std::move(uuid)) {}

Entry::Entry(std::string name) noexcept : Entry(std::move(name), "") {}

Entry::Entry(const Entry &rhs) noexcept = default;

Entry::~Entry() noexcept = default;

std::unique_ptr<Entry> Entry::clone() const noexcept {
    return std::make_unique<Entry>(*this);
}

const char *Entry::TYPE_GENERIC = "GENERIC_ENTRY";
const char *Entry::TYPE_NOTE = "NOTE";
const char *Entry::TYPE_ACCOUNT = "ACCOUNT";

std::string Entry::getEntryType() const noexcept { return TYPE_GENERIC; }

Attribute Entry::getAttribute(const std::string &attr) const {
    return attributes.at(attr);
}

void Entry::setAttribute(const std::string &attr, std::string value) {
    attributes.insert_or_assign(attr, value);
}

std::string Entry::getName() const noexcept { return name; }

void Entry::print(std::ostream &os) const {
    os << "Entry \"" << getName() << "\" { ";
    for (const auto &[attrName, attr] : attributes) {
        os << attrName << ": " << attr.getValue() << ", ";
    }
    os << '}';
}

std::ostream &operator<<(std::ostream &os, const Entry &entry) {
    entry.print(os);
    return os;
}

} // namespace passman
