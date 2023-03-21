#pragma once

#include <iterator>

template <typename It1, typename It2>
class ZipIt {
public:
    ZipIt(It1 it1, It2 it2) : it1_(it1), it2_(it2) {
    }
    auto operator*() {
        return std::pair(*it1_, *it2_);
    }
    ZipIt& operator++() {
        it1_++;
        it2_++;
        return *this;
    };
    bool operator!=(ZipIt& other) {
        return std::pair(it1_, it2_) != std::pair(other.it1_, other.it2_);
    }
    It1 GetIt1() {
        return it1_;
    }
    It2 GetIt2() {
        return it2_;
    }

private:
    It1 it1_;
    It2 it2_;
};

template <typename It1, typename It2>
class Seq {
public:
    Seq(It1 beg1, It1 end1, It2 beg2, It2 end2) : beg1_(beg1), end1_(end1), beg2_(beg2), end2_(end2) {
    }
    auto begin() {
        ZipIt<It1, It2> zipit(beg1_, beg2_);
        return zipit;
    }
    auto end() {
        ZipIt<It1, It2> zipit(beg1_, beg2_);
        while (zipit.GetIt1() != end1_ && zipit.GetIt2() != end2_) {
            ++zipit;
        }
        return zipit;
    }

private:
    It1 beg1_;
    It1 end1_;
    It2 beg2_;
    It2 end2_;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    return Seq(std::begin(sequence1), std::end(sequence1), std::begin(sequence2), std::end(sequence2));
}
