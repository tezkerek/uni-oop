#pragma once

#include <string>
#include <memory>

#include "Entry.hpp"

namespace passman {

class Account : public Entry {
public:
    Account(const std::string &accountName, const std::string &username,
            const std::string &password, const std::string &url) noexcept;

    std::unique_ptr<Entry> clone() const noexcept override;

    std::string getEntryType() const noexcept override;

    void print(std::ostream &os) const override;

    std::string getUsername() const noexcept;
    void setUsername(const std::string &accountName) noexcept;

    std::string getPassword() const noexcept;
    void setPassword(const std::string &password) noexcept;

    std::string getURL() const noexcept;
    void setURL(const std::string &url) noexcept;

    static const char *ATTR_USERNAME;
    static const char *ATTR_PASSWORD;
    static const char *ATTR_URL;
};

} // namespace passman
