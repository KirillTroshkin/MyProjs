#include "search.h"
#include <cmath>
#include <string>
#include <set>

const int DIFFERENCE_IN_CHARS = 32;

struct Searchstring {
    std::string_view str;
    double relev = 0.0;
};

std::vector<std::string_view> SplittedIntoStrings(std::string_view s) {
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

std::vector<std::string_view> SplittedIntoWords(std::string_view s) {
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

bool Equality(std::string_view s1, std::string_view s2) {
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

double Tf(std::vector<std::string_view> vdocst, std::string_view s) {
    int64_t number_of_equal_words = 0;
    for (auto wdocst : vdocst) {
        if (Equality(wdocst, s)) {
            ++number_of_equal_words;
        }
    }
    return static_cast<double>(number_of_equal_words) / static_cast<double>(vdocst.size());
}

bool IsInTheString(std::vector<std::string_view> vdocst, std::string_view s) {
    for (auto wdocst : vdocst) {
        if (Equality(wdocst, s)) {
            return true;
        }
    }
    return false;
}

double Idf(std::vector<std::string_view> vdoc, std::string_view s) {
    size_t counter_of_containing = 0;
    for (auto stdoc : vdoc) {
        std::vector<std::string_view> vecofwords = SplittedIntoWords(stdoc);
        if (IsInTheString(vecofwords, s)) {
            ++counter_of_containing;
        }
    }
    return log10(static_cast<double>(vdoc.size()) / static_cast<double>(counter_of_containing));
}

bool Cmp(const Searchstring& sr1, const Searchstring& sr2) {
    return sr1.relev > sr2.relev;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<std::string_view> most_relevant_docs;
    std::vector<std::string_view> vec_of_strings = SplittedIntoStrings(text);
    std::vector<std::string_view> vec_of_qwords = SplittedIntoWords(query);
    std::set<std::string_view> set_of_qwords;
    std::vector<Searchstring> vec_for_searchstr;
    for (auto qw : vec_of_qwords) {
        set_of_qwords.insert(qw);
    }
    for (auto st : vec_of_strings) {
        std::vector<std::string_view> vec_of_stwords = SplittedIntoWords(st);
        double relevance = 0.0;
        Searchstring searchstr;
        searchstr.str = st;
        for (auto wqu : set_of_qwords) {
            relevance += Tf(vec_of_stwords, wqu) * Idf(vec_of_strings, wqu);
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
