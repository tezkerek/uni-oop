#pragma once

#include "CharQueue.hpp"
#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

namespace CharQueue {
class REPL {
private:
    std::unordered_map<std::string, CharQueue> variables;

    CharQueue &get_variable(const std::string &var_name);
    static std::string &get_arg(std::vector<std::string> &args,
                                std::size_t pos);
    bool eval_print(const std::string &line, std::ostream &os);

public:
    REPL() = default;
    void repl();
};
} // namespace CharQueue
