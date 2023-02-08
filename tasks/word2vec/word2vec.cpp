#include "word2vec.h"

#include <vector>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    size_t max_prox = 0;
    std::vector<size_t> proximities;
    std::vector<std::string> closest_words;
    for (size_t i = 1; i < vectors.size(); ++i) {
        size_t proximity = 0;
        for (size_t j = 0; j < vectors[i].size(); ++j) {
            proximity += vectors[0][j] * vectors[i][j];
        }
        proximities.push_back(proximity);
        if (proximity > max_prox) {
            max_prox = proximity;
        }
    }
    for (size_t k = 0; k < proximities.size(); ++k) {
        if (proximities[k] == max_prox) {
            closest_words.push_back(words[k + 1]);
        }
    }
    return closest_words;
}
