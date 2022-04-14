#pragma once

#include <memory>
#include <string>

#include "Entry.hpp"

namespace passman {

class Note : public Entry {
public:
    explicit Note(std::string name) noexcept;
    explicit Note(std::string name, const std::string &content) noexcept;

    std::unique_ptr<Entry> clone() const noexcept override;

    std::string getEntryType() const noexcept override;

    void print(std::ostream &os) const override;

    std::string getContent() const noexcept;
    void setContent(const std::string &content) noexcept;

    static const char *ATTR_NOTE_CONTENT;
};

} // namespace passman
