#pragma once

#include <memory>
#include <regex>
#include <string>

#include "Entry.hpp"
#include "serialization.hpp"
#include "utils.hpp"

namespace passman {

using ::operator<<;

template <Serializable ContentType = std::string> class Note : public Entry {
protected:
    Serializer<ContentType> contentSerializer;

public:
    explicit Note(std::string name) noexcept : Note(std::move(name), "") {}
    explicit Note(std::string name, const ContentType &content) noexcept
        : Entry(std::move(name)) {
        setContent(content);
    }

    std::unique_ptr<Entry> clone() const noexcept override {
        return std::make_unique<Note>(*this);
    }

    std::string getEntryType() const noexcept override { return TYPE_NOTE; }

    void print(std::ostream &os) const override {
        os << "Note \"" << getName() << "\" { " << getContent() << " }";
    }

    ContentType getContent() const noexcept {
        auto serialized = getAttribute(ATTR_NOTE_CONTENT).getValue();
        if constexpr (std::convertible_to<ContentType, std::string>) {
            return serialized;
        } else {
            return contentSerializer.deserialize(serialized);
        }
    }

    void setContent(const ContentType &content) noexcept {
        std::string serialized;
        if constexpr (std::convertible_to<ContentType, std::string>) {
            serialized = content;
        } else {
            serialized = contentSerializer.serialize(content);
        }

        setAttribute(ATTR_NOTE_CONTENT, serialized);
    }

    static const char *ATTR_NOTE_CONTENT;
};

template <Serializable ContentType>
const char *Note<ContentType>::ATTR_NOTE_CONTENT = "NOTE_CONTENT";

} // namespace passman
