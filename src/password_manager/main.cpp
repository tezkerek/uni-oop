#include "Account.hpp"
#include "Database.hpp"
#include "Entry.hpp"
#include "Note.hpp"
#include "serialization.hpp"
#include "utils.hpp"

#include <iostream>
#include <memory>

template <> struct Serializer<std::vector<int>> {
    static std::string serialize(const std::vector<int> &vec) {
        if (vec.empty()) {
            return "";
        }

        std::stringstream ss;
        auto iter = vec.begin();
        ss << *iter;
        ++iter;
        while (iter != vec.end()) {
            ss << ' ' << *iter;
            ++iter;
        }
        return ss.str();
    }

    static std::vector<int> deserialize(const std::string &str) {
        std::vector<int> vec;

        std::string::size_type start_pos = 0;
        auto end_pos = str.find(' ');
        while (start_pos != std::string::npos) {
            auto num_str = str.substr(start_pos, end_pos - start_pos);
            vec.push_back(std::stoi(num_str));

            if (end_pos == std::string::npos) {
                break;
            }
            start_pos = end_pos + 1;
            end_pos = str.find(' ', start_pos);
        }

        return vec;
    }
};

int main() {
    passman::Database db;

    db.addGroup("Uni");
    std::cerr << "Added group \"" << db.getGroup("Uni").getName() << "\".\n";

    db.addEntry("Uni",
                passman::Account("Moodle", "student@s.unibuc.ro",
                                 "securepassword", "https://moodle.unibuc.ro"));
    db.addEntry("Uni", passman::Note<>("Homework", "SD\nOOP\nLFA\n"));
    db.addEntry("Uni",
                passman::Note("Grades", std::vector<int>{10, 9, 10, 8, 4}));

    passman::Account teamsAccount("Microsoft Teams", "student@s.unibuc.ro",
                                  "securepassword",
                                  "https://teams.microsoft.com");

    try {
        db.addEntry("Inexistent", teamsAccount);
    } catch (const passman::GroupDoesNotExist &e) {
        std::cerr << e.what() << '\n';
    }
    db.addEntry("Uni", teamsAccount);

    passman::Group group2("Uni2");
    group2 = db.getGroup("Uni");
    group2.addEntry(passman::Note("Extra note"));
    std::cerr << "Called operator=\nPrinting group:\n" << group2 << '\n';

    db.addGroup("Shopping");
    try {
        db.addGroup("Shopping");
    } catch (const passman::GroupAlreadyExists &e) {
        std::cerr << e.what() << '\n';
    }

    passman::Account customEntry("Double shop", "person@example.com",
                                 "password", "https://shoes.shop.com");
    customEntry.setAttribute("URL_2", "https://pants.shop.com");
    db.addEntry("Shopping", static_cast<passman::Entry>(customEntry));

    std::cerr << "\nPrinting database:\n";
    std::cout << db << '\n';

    return 0;
}
