#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace passman {

class Attribute {
protected:
    std::string value;

public:
    explicit Attribute(std::string str) noexcept;
    Attribute &operator=(const std::string &str) noexcept;
    [[nodiscard]] std::string getValue() const noexcept;
};

class Entry {
protected:
    std::string name;
    std::string uuid;
    std::unordered_map<std::string, Attribute> attributes;

public:
    Entry(std::string name, std::string uuid) noexcept;
    explicit Entry(std::string name) noexcept;
    Entry(const Entry &rhs) noexcept;
    virtual ~Entry() noexcept;

    virtual std::unique_ptr<Entry> clone() const noexcept;

    virtual std::string getEntryType() const noexcept;
    virtual Attribute getAttribute(const std::string &attr) const;
    virtual void setAttribute(const std::string &attr, std::string value);

    std::string getName() const noexcept;

    virtual void print(std::ostream &os) const;

    static const char *TYPE_GENERIC;
    static const char *TYPE_NOTE;
    static const char *TYPE_ACCOUNT;
};

std::ostream &operator<<(std::ostream &os, const Entry &entry);

} // namespace passman
