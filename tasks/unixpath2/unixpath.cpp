#include "unixpath.h"
#include <cmath>

std::vector<std::string_view> UnixPath::Splitted(std::string_view s) const {
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
        return splitted_str;
    }
    splitted_str.emplace_back(s.substr(0, s.find('/')));
    size_t divider = s.find('/');
    if (divider != std::string::npos) {
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

std::string UnixPath::NormalizePath(std::vector<std::string_view> path) const {
    std::string normalizedpath;
    std::vector<std::string_view> vector_of_words;
    for (auto word : path) {
        if (word == static_cast<std::string_view>("..")) {
            if (!vector_of_words.empty()) {
                vector_of_words.pop_back();
            }
            continue;
        }
        if (word != static_cast<std::string_view>(".")) {
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
    return normalizedpath;
}

UnixPath::UnixPath(std::string_view initial_dir) {
    start_path = Splitted(initial_dir);
    current_dir = start_path;
}

void UnixPath::ChangeDirectory(std::string_view path) {
    if (path == "..") {
        if (!current_dir.empty()) {
            current_dir.pop_back();
        }
    }
    if (path != "." and path != "..") {
        current_dir = Splitted(path);
    }
}

std::string UnixPath::GetAbsolutePath() const {
    return NormalizePath(current_dir);
}

std::string UnixPath::GetRelativePath() const {
    std::string normalizedpath;
    size_t i = 0;
    std::string current_str = NormalizePath(current_dir);
    std::vector current_dir_norm = Splitted(current_str);
    std::string start_str = NormalizePath(start_path);
    std::vector start_path_norm = Splitted(start_str);
    while (i < std::min(current_dir_norm.size(), start_path_norm.size()) && current_dir_norm[i] == start_path_norm[i]) {
        ++i;
    }
    if (i == start_path_norm.size()) {
        normalizedpath += '.';
    } else {
        normalizedpath += "..";
    }
    for (auto k = i; k < current_dir_norm.size(); ++k) {
        normalizedpath += "/";
        normalizedpath += static_cast<std::string>(current_dir_norm[k]);
    }
    if (normalizedpath.empty()) {
        normalizedpath += "/";
    }
    return normalizedpath;
}
