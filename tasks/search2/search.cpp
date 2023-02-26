#include "search.h"
#include <cmath>
#include <set>
#include <string>

const int DIFFERENCE_IN_CHARS = 32;

std::vector<std::string_view> SearchEngine::SplittedIntoStrings(std::string_view s) const {
    std::vector<std::string_view> splitted_str;
    if (s[0] == '\n') {
        size_t divider = 0;
        while (s.find('\n', divider + 1) != std::string::npos) {
            if (!s.substr(divider + 1, s.find('\n', divider + 1) - divider - 1).empty()) {
                splitted_str.emplace_back(s.substr(divider + 1, s.find('\n', divider + 1) - divider - 1));
            }
            divider = s.find('\n', divider + 1);
        }
        if (!s.substr(divider + 1, s.size() - divider - 1).empty()) {
            splitted_str.emplace_back(s.substr(divider + 1, s.size() - divider - 1));
        }
        return splitted_str;
    }
    splitted_str.emplace_back(s.substr(0, s.find('\n')));
    size_t divider = s.find('\n');
    if (divider != std::string::npos) {
        while (s.find('\n', divider + 1) != std::string::npos) {
            if (!s.substr(divider + 1, s.find('\n', divider + 1) - divider - 1).empty()) {
                splitted_str.emplace_back(s.substr(divider + 1, s.find('\n', divider + 1) - divider - 1));
            }
            divider = s.find('\n', divider + 1);
        }
        if (!s.substr(divider + 1, s.find('\n', divider + 1) - divider - 1).empty()) {
            splitted_str.emplace_back(s.substr(divider + 1, s.size() - divider - 1));
        }
    }
    return splitted_str;
}

std::vector<std::string_view> SearchEngine::SplittedIntoWords(std::string_view s) const {
    std::vector<std::string_view> splitted_str;
    if (!isalpha(s[0])) {
        size_t divider1 = 0;
        size_t divider2 = 1;
        while (divider2 < s.size() && isalpha(s[divider2])) {
            ++divider2;
        }
        while (divider2 < s.size()) {
            if (!s.substr(divider1 + 1, divider2 - divider1 - 1).empty()) {
                splitted_str.emplace_back(s.substr(divider1 + 1, divider2 - divider1 - 1));
            }
            divider1 = divider2;
            if (divider2 < s.size()) {
                ++divider2;
            }
            while (divider2 < s.size() && isalpha(s[divider2])) {
                ++divider2;
            }
        }
        if (!s.substr(divider1 + 1, s.size() - divider1 - 1).empty()) {
            splitted_str.emplace_back(s.substr(divider1 + 1, s.size() - divider1 - 1));
        }
        return splitted_str;
    }
    size_t divider2 = 0;
    while (divider2 < s.size() && isalpha(s[divider2])) {
        ++divider2;
    }
    splitted_str.emplace_back(s.substr(0, divider2));
    size_t divider1 = divider2;
    if (divider1 < s.size()) {
        ++divider2;
        while (divider2 < s.size() && isalpha(s[divider2])) {
            ++divider2;
        }
        while (divider2 < s.size()) {
            if (!s.substr(divider1 + 1, divider2 - divider1 - 1).empty()) {
                splitted_str.emplace_back(s.substr(divider1 + 1, divider2 - divider1 - 1));
            }
            divider1 = divider2;
            ++divider2;
            while (divider2 < s.size() && isalpha(s[divider2])) {
                ++divider2;
            }
        }
        if (!s.substr(divider1 + 1, s.size() - divider1 - 1).empty()) {
            splitted_str.emplace_back(s.substr(divider1 + 1, s.size() - divider1 - 1));
        }
    }
    return splitted_str;
}

bool SearchEngine::Equality(std::string_view s1, std::string_view s2) const {
    if (s1.size() != s2.size()) {
        return false;
    }
    for (size_t i = 0; i < s1.size(); ++i) {
        if (s1[i] == s2[i]) {
            continue;
        }
        if (std::islower(s1[i]) && s2[i] == (s1[i] - DIFFERENCE_IN_CHARS)) {
            continue;
        }
        if (std::isupper(s1[i]) && s2[i] == (s1[i] + DIFFERENCE_IN_CHARS)) {
            continue;
        }
        return false;
    }
    return true;
}

double SearchEngine::Tf(std::string_view st, std::string_view s) const {
    int64_t number_of_equal_words = 0;
    for (auto wdocst : string_to_vec_.at(st)) {
        if (Equality(wdocst, s)) {
            ++number_of_equal_words;
        }
    }
    return static_cast<double>(number_of_equal_words) / static_cast<double>(number_of_words_.at(st));
}

bool SearchEngine::IsInTheString(std::vector<std::string_view> vdocst, std::string_view s) const {
    for (auto wdocst : vdocst) {
        if (Equality(wdocst, s)) {
            return true;
        }
    }
    return false;
}

double SearchEngine::Idf(std::vector<std::string_view> vdoc, std::string_view s) const {
    size_t counter_of_containing = 0;
    for (auto stdoc : vdoc) {
        std::vector<std::string_view> vecofwords = SplittedIntoWords(stdoc);
        if (IsInTheString(vecofwords, s)) {
            ++counter_of_containing;
        }
    }
    return log10(static_cast<double>(number_of_docs_) / static_cast<double>(counter_of_containing));
}

void SearchEngine::BuildIndex(std::string_view text) {
    SearchEngine::vec_of_strings_ = SplittedIntoStrings(text);
    number_of_docs_ = vec_of_strings_.size();
    for (auto st : vec_of_strings_) {
        std::vector<std::string_view> vec_of_stwords = SplittedIntoWords(st);
        string_to_vec_[st] = vec_of_stwords;
        number_of_words_[st] = vec_of_stwords.size();
    }
}

std::vector<std::string_view> SearchEngine::Search(std::string_view query, size_t results_count) const {
    std::vector<std::string_view> most_relevant_docs;
    std::vector<std::string_view> vec_of_qwords = SplittedIntoWords(query);
    std::set<std::string_view> set_of_qwords;
    std::vector<Searchstring> vec_for_searchstr;
    for (auto qw : vec_of_qwords) {
        set_of_qwords.insert(qw);
    }
    for (const auto& stpair : string_to_vec_) {
        double relevance = 0.0;
        Searchstring searchstr;
        searchstr.str = stpair.first;
        for (auto wqu : set_of_qwords) {
            relevance += Tf(stpair.first, wqu) * Idf(vec_of_strings_, wqu);
        }
        searchstr.relev = relevance;
        if (searchstr.relev > 0) {
            vec_for_searchstr.emplace_back(searchstr);
        }
    }
    sort(vec_for_searchstr.begin(), vec_for_searchstr.end(), Cmp);
    for (size_t i = 0; i < vec_for_searchstr.size() && i < results_count; ++i) {
        most_relevant_docs.emplace_back(vec_for_searchstr[i].str);
    }
    return most_relevant_docs;
}
