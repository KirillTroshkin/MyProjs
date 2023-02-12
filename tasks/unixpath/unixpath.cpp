#include "unixpath.h"
#include <vector>

std::vector<std::string_view> Splitted(std::string_view s) {
    std::vector<std::string_view> splitted_str;
    if (s[0] == '/') {
        size_t divider = 0;
        while (s.find('/', divider + 1) != std::string::npos) {
            if (!s.substr(divider + 1, s.find('/', divider + 1) - divider - 1).empty()) {
                splitted_str.emplace_back(s.substr(divider + 1, s.find('/', divider + 1) - divider - 1));
            }
            divider = s.find('/', divider + 1);
        }
        if (!s.substr(divider + 1, s.find('/', divider + 1) - divider - 1).empty()) {
            splitted_str.emplace_back(s.substr(divider + 1, s.size() - divider - 1));
        }
    } else {
        splitted_str.emplace_back(s.substr(0, s.find('/')));
        size_t divider = s.find('/');
        while (s.find('/', divider + 1) != std::string::npos) {
            if (!s.substr(divider + 1, s.find('/', divider + 1) - divider - 1).empty()) {
                splitted_str.emplace_back(s.substr(divider + 1, s.find('/', divider + 1) - divider - 1));
            }
            divider = s.find('/', divider + 1);
        }
        if (!s.substr(divider + 1, s.find('/', divider + 1) - divider - 1).empty()) {
            splitted_str.emplace_back(s.substr(divider + 1, s.size() - divider - 1));
        }
    }
    return splitted_str;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string normalizedpath;
    std::vector<std::string_view> vector_of_words;
    if (path[0] != '/') {
        for (auto word : Splitted(current_working_dir)) {
            if (word == static_cast<std::string_view>("..")) {
                if (!vector_of_words.empty()) {
                    vector_of_words.pop_back();
                }
            } else if (word != static_cast<std::string_view>(".")) {
                vector_of_words.push_back(word);
            }
        }
        for (auto word : Splitted(path)) {
            if (word == static_cast<std::string_view>("..")) {
                if (!vector_of_words.empty()) {
                    vector_of_words.pop_back();
                }
            } else if (word != static_cast<std::string_view>(".")) {
                vector_of_words.push_back(word);
            }
        }
        for (auto word : vector_of_words) {
            normalizedpath += "/";
            normalizedpath += static_cast<std::string>(word);
        }
        if (normalizedpath.empty()) {
            normalizedpath += "/";
        }
    } else {
        for (auto word : Splitted(path)) {
            if (word == static_cast<std::string_view>("..")) {
                if (!vector_of_words.empty()) {
                    vector_of_words.pop_back();
                }
            } else if (word != static_cast<std::string_view>(".")) {
                vector_of_words.push_back(word);
            }
        }
        for (auto word : vector_of_words) {
            normalizedpath += "/";
            normalizedpath += static_cast<std::string>(word);
        }
        if (normalizedpath.empty()) {
            normalizedpath += "/";
        }
    }
    return normalizedpath;
}
