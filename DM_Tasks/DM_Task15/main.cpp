#include <fstream>
#include <stack>
#include <regex>
#include <cctype>
#include <map>

inline bool space(char c) {
    return std::isspace(static_cast<unsigned char>(c));
}

inline bool not_space(char c) {
    return !std::isspace(static_cast<unsigned char>(c));
}

std::vector<std::string> split(const std::string& s) {
    typedef std::string::const_iterator iter;
    std::vector<std::string> ret;
    iter i = s.begin();

    while (i != s.end()) {
        i = std::find_if(i, s.end(), not_space);
        iter j = std::find_if(i, s.end(), space);
        if (i != s.end()) {
            ret.emplace_back(i, j);
            i = j;
        }
    }
    return ret;
}

bool bool_value(int num_var, int iteration, int num_variables) {
    return (iteration / (1 << (num_variables - num_var))) % 2 == 1;;
}

bool bool_operation(bool var1, bool var2, const std::string& operation) {
    if (operation == "\\/") {
        return var1 || var2;
    }
    else if (operation == "/\\") {
        return var1 && var2;
    }
    else if (operation == "->") {
        return !var1 || var2;
    }
    else if (operation == "<=>") {
        return var1 == var2;
    }
    else if (operation == "^") {
        return var1 != var2;
    }
    else if (operation == "|") {
        return !(var1 && var2);
    }
    else {
        return !(var1 || var2);
    }
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    std::string str;
    std::getline(input, str);

    std::vector<std::string> words = split(str);

    int num_variables = 0;
    bool* check_variables = new bool[24]();

    for (const std::string& word : words) {
        if (word[0] == 'x') {
            int num_var = std::stoi(word.substr(1, word.size() - 1));
            check_variables[num_var - 1] = true;

            if (num_variables < num_var) {
                num_variables = num_var;
            }
        }
    }

    std::map<int, std::vector<bool>> bool_vectors;

    int num_iteration = 1 << num_variables;

    std::stack<std::string> operation_stack;
    auto* var_stack = new std::stack<bool>[num_iteration];

    for (const std::string &word : words) {
        if (word == "(") {
            continue;
        } else if (word[0] == 'x') {
            for (int i = 0; i < num_iteration; i++) {
                var_stack[i].push(bool_value(std::stoi(word.substr(1, word.size() - 1)), i, num_variables));
            }
        } else if (word == "1" || word == "0") {
            for (int i = 0; i < num_iteration; i++) {
                var_stack[i].push(std::stoi(word));
            }
        } else if (word == ")") {
            std::string operation = operation_stack.top();
            operation_stack.pop();

            if (operation == "~") {
                for (int i = 0; i < num_iteration; i++) {
                    bool value = var_stack[i].top();
                    var_stack[i].pop();
                    var_stack[i].push(!value);
                }
            } else {
                for (int i = 0; i < num_iteration; i++) {
                    bool var2 = var_stack[i].top();
                    var_stack[i].pop();
                    bool var1 = var_stack[i].top();
                    var_stack[i].pop();

                    var_stack[i].push(bool_operation(var1, var2, operation));
                }
            }
        } else {
            operation_stack.push(word);
        }
    }

    for (int i = 0; i < num_iteration; i++) {
        output << var_stack[i].top();
        var_stack[i].pop();
    }

    input.close();
    output.close();

    return 0;
}