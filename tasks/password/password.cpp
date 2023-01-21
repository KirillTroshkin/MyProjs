#include "password.h"

#include <cctype>

const size_t MIN_POSSIBLE_LENGTH = 8;
const size_t MAX_POSSIBLE_LENGTH = 14;

bool ValidatePassword(const std::string& password) {
    if (password.size() < MIN_POSSIBLE_LENGTH || password.size() > MAX_POSSIBLE_LENGTH) {
        return false;
    }
    int having_uppercase = 0;
    int having_lowercase = 0;
    int having_digit = 0;
    int having_others = 0;
    for (size_t i = 0; i < password.size(); ++i) {
        if (password[i] < '!' || password[i] > '~') {
            return false;
        } else if (isupper(password[i])) {
            having_uppercase = 1;
        } else if (islower(password[i])) {
            having_lowercase = 1;
        } else if (isdigit(password[i])) {
            having_digit = 1;
        } else {
            having_others = 1;
        }
    }
    if (having_uppercase + having_lowercase + having_digit + having_others < 3) {
        return false;
    }
    return true;
}
