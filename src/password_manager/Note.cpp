#include <regex>
#include <string>
#include <utility>

#include "Note.hpp"

namespace passman {

Note::Note(std::string name, const std::string &content) noexcept
    : Entry(std::move(name)) {
    setContent(content);
}

Note::Note(std::string name) noexcept : Note(std::move(name), "") {}

std::unique_ptr<Entry> Note::clone() const noexcept {
    return std::make_unique<Note>(*this);
}

std::string Note::getEntryType() const noexcept { return TYPE_NOTE; }

const char *Note::ATTR_NOTE_CONTENT = "NOTE_CONTENT";

std::string Note::getContent() const noexcept {
    return getAttribute(ATTR_NOTE_CONTENT).getValue();
}

void Note::setContent(const std::string &content) noexcept {
    setAttribute(ATTR_NOTE_CONTENT, content);
}

void Note::print(std::ostream &os) const {
    auto content = std::regex_replace(getContent(), std::regex("\n"), "⤶");
    os << "Note \"" << getName() << "\" { \"" << content << "\" }";
}

} // namespace passman
