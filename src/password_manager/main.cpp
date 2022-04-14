#include "Account.hpp"
#include "Database.hpp"
#include "Entry.hpp"
#include "Note.hpp"

#include <iostream>
#include <memory>

int main() {
    passman::Database db;

    db.addGroup("Uni");
    std::cerr << "Added group \"" << db.getGroup("Uni").getName() << "\".\n";

    db.addEntry("Uni",
                passman::Account("Moodle", "student@s.unibuc.ro",
                                 "securepassword", "https://moodle.unibuc.ro"));
    db.addEntry("Uni", passman::Note("Homework", "SD\nOOP\nLFA\n"));

    passman::Account teamsAccount("Microsoft Teams", "student@s.unibuc.ro",
                                  "securepassword",
                                  "https://teams.microsoft.com");

    try {
        db.addEntry("Inexistent", teamsAccount);
    } catch (const passman::GroupDoesNotExist &e) {
        std::cerr << e.what() << '\n';
    }
    db.addEntry("Uni", teamsAccount);

    db.addGroup("Shopping");
    try {
        db.addGroup("Shopping");
    } catch (const passman::GroupAlreadyExists &e) {
        std::cerr << e.what() << '\n';
    }

    passman::Account customEntry("Double shop", "person@example.com", "password", "https://shoes.shop.com");
    customEntry.setAttribute("URL_2", "https://pants.shop.com");
    db.addEntry("Shopping", static_cast<passman::Entry>(customEntry));

    std::cerr << "\nPrinting database:\n";
    std::cout << db << '\n';

    return 0;
}
