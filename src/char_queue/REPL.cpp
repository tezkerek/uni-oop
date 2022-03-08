#include "REPL.hpp"
#include <iostream>
#include <stdexcept>

namespace CharQueue {
const char *HELP_TEXT =
    R""""(Commands:
quit | exit | CTRL-D
set <var> <value>
print <var>
+ <var1> <var2>
- <var1> <var2>
)"""";

void string_to_uppercase(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

std::vector<std::string> string_split(const std::string &str,
                                      const std::string &delimiter) {
    std::vector<std::string> result;

    std::size_t start_pos = 0, end_pos;
    while ((end_pos = str.find(delimiter, start_pos)) != std::string::npos) {
        auto token = str.substr(start_pos, end_pos - start_pos);
        start_pos = end_pos + delimiter.length();

        if (!token.empty()) {
            result.push_back(token);
        }
    }
    // Also add last token
    result.push_back(str.substr(start_pos));

    return result;
}

CharQueue &REPL::get_variable(const std::string &var_name) {
    try {
        return variables.at(var_name);
    } catch (const std::out_of_range &e) {
        throw std::invalid_argument("Undefined variable " + var_name);
    }
}

std::string &REPL::get_arg(std::vector<std::string> &args, std::size_t pos) {
    if (args.size() <= pos) {
        throw std::invalid_argument(
            "Expected at least " + std::to_string(pos + 1) +
            " arguments, but received only " + std::to_string(args.size()));
    }

    return args[pos];
}

bool REPL::eval_print(const std::string &line, std::ostream &os) {
    auto args = string_split(line, " ");

    try {
        auto cmd = get_arg(args, 0);

        if (cmd == "exit" || cmd == "quit") {
            return false;
        }
        if (cmd == "help") {
            os << HELP_TEXT;
        } else if (cmd == "set") {
            auto var_name = get_arg(args, 1);
            auto value = get_arg(args, 2);
            variables[var_name] = value;
        } else if (cmd == "print") {
            auto var_name = get_arg(args, 1);
            auto value = get_variable(var_name);
            os << var_name << " = " << value << '\n';
        } else if (cmd == "+") {
            auto var1 = get_arg(args, 1);
            auto var2 = get_arg(args, 2);
            auto &cq1 = get_variable(var1);
            auto &cq2 = get_variable(var2);

            auto cq_sum = cq1 + cq2;
            os << var1 << " + " << var2 << " = " << cq_sum << '\n';
        } else if (cmd == "-") {
            auto var1 = get_arg(args, 1);
            auto var2 = get_arg(args, 2);
            auto &cq1 = get_variable(var1);
            auto &cq2 = get_variable(var2);

            auto cq_diff = cq1 - cq2;
            os << var1 << " - " << var2 << " = " << cq_diff << '\n';
        } else {
            os << "Unknown command\n";
        }
    } catch (const std::invalid_argument &e) {
        os << "ERROR: " << e.what() << '\n';
    }

    return true;
}

void REPL::repl() {
    auto &is = std::cin;
    auto &os = std::cerr;

    os << "Type 'help' for a list of commands.\n"
       << "$> ";
    std::string line;
    while (std::getline(is, line)) {
        if (!eval_print(line, os)) {
            break;
        };
        os << "$> ";
    }
}
} // namespace CharQueue
