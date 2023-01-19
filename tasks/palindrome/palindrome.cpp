#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    std::string checker;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            checker += str[i];
        }
    }
    for (int i = 0; i < checker.size(); ++i) {
        if (checker[i] != checker[checker.size() - 1 - i]) {
            return false;
        }
    }
    return true;
}
