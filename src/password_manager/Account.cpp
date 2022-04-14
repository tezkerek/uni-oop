#include <ostream>
#include <string>

#include "Account.hpp"

namespace passman {

Account::Account(const std::string &accountName, const std::string &username,
                 const std::string &password, const std::string &url) noexcept
    : Entry(accountName) {
    setUsername(username);
    setPassword(password);
    setURL(url);
}

std::unique_ptr<Entry> Account::clone() const noexcept {
    return std::make_unique<Account>(*this);
}

std::string Account::getEntryType() const noexcept { return TYPE_ACCOUNT; }

const char *Account::ATTR_USERNAME = "ACCOUNT_USERNAME";
const char *Account::ATTR_PASSWORD = "ACCOUNT_PASSWORD";
const char *Account::ATTR_URL = "ACCOUNT_URL";

std::string Account::getUsername() const noexcept {
    return getAttribute(ATTR_USERNAME).getValue();
}

void Account::setUsername(const std::string &accountName) noexcept {
    setAttribute(ATTR_USERNAME, accountName);
}

std::string Account::getPassword() const noexcept {
    return getAttribute(ATTR_PASSWORD).getValue();
}

void Account::setPassword(const std::string &password) noexcept {
    setAttribute(ATTR_PASSWORD, password);
}

std::string Account::getURL() const noexcept {
    return getAttribute(ATTR_URL).getValue();
}

void Account::setURL(const std::string &url) noexcept {
    setAttribute(ATTR_URL, url);
}

void Account::print(std::ostream &os) const {
    os << "Account \"" << getName() << "\" { " << getUsername() << " at "
       << getURL() << " }";
}

} // namespace passman
