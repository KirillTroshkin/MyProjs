#include "poly.h"
#include <cmath>

Poly::Poly(std::initializer_list<std::pair<const size_t, int64_t>> poly_ins) : poly_ins_(poly_ins) {
}

Poly::Poly(const std::vector<int64_t>& poly_ins) {
    for (size_t i = 0; i < poly_ins.size(); ++i) {
        if (poly_ins.at(i) != 0) {
            poly_ins_[i] = poly_ins[i];
        }
    }
}

int64_t Poly::operator()(const int64_t x) const {
    int64_t result = 0;
    for (auto [deg, coef] : poly_ins_) {
        result +=
            static_cast<int64_t>(pow(static_cast<double>(x), static_cast<double>(deg)) * static_cast<double>(coef));
    }
    return result;
}

void Poly::EraseZeros() {
    for (auto [deg, coef] : poly_ins_) {
        if (coef == 0) {
            poly_ins_.erase(deg);
        }
    }
}

bool Poly::operator==(const Poly& other) const {
    return poly_ins_ == other.poly_ins_;
}

bool Poly::operator!=(const Poly& other) const {
    return poly_ins_ != other.poly_ins_;
}

void Poly::operator=(const Poly& other) {
    poly_ins_ = other.poly_ins_;
}

Poly Poly::operator+(const Poly& other) const {
    Poly sum = *this;
    for (auto [deg, coef] : other.poly_ins_) {
        sum.poly_ins_[deg] += coef;
    }
    sum.EraseZeros();
    return sum;
}

Poly Poly::operator-(const Poly& other) const {
    Poly diff = *this;
    for (auto [deg, coef] : other.poly_ins_) {
        diff.poly_ins_[deg] -= coef;
    }
    diff.EraseZeros();
    return diff;
}

void Poly::operator+=(const Poly& other) {
    for (auto [deg, coef] : other.poly_ins_) {
        poly_ins_[deg] += coef;
    }
    EraseZeros();
}

void Poly::operator-=(const Poly& other) {
    for (auto [deg, coef] : other.poly_ins_) {
        poly_ins_[deg] -= coef;
    }
    EraseZeros();
}

Poly Poly::operator*(const Poly& other) const {
    Poly prod;
    for (auto [deg_this, coef_this] : poly_ins_) {
        for (auto [deg_other, coef_other] : other.poly_ins_) {
            prod.poly_ins_[deg_this + deg_other] += coef_this * coef_other;
        }
    }
    prod.EraseZeros();
    return prod;
}

void Poly::operator*=(const Poly& other) {
    Poly prod;
    for (auto [deg_this, coef_this] : poly_ins_) {
        for (auto [deg_other, coef_other] : other.poly_ins_) {
            prod.poly_ins_[deg_this + deg_other] += coef_this * coef_other;
        }
    }
    *this = prod;
    EraseZeros();
}

Poly operator-(const Poly& p) {
    Poly opp = p;
    for (auto [deg, coef] : opp.poly_ins_) {
        opp.poly_ins_[deg] *= (-1);
    }
    return opp;
}

std::ostream& operator<<(std::ostream& out, const Poly& p) {
    out << "y =";
    if (p.poly_ins_.empty()) {
        out << " 0";
        return out;
    }
    for (auto [deg, coef] : p.poly_ins_) {
        if (p.poly_ins_.find(deg) == p.poly_ins_.begin()) {
            if (deg == 0) {
                out << " " << coef;
                continue;
            }
            if (deg == 1) {
                out << " " << coef << "x";
                continue;
            }
            out << " " << coef << "x^" << deg;
            continue;
        }
        if (coef > 0) {
            out << " +";
        }
        if (coef < 0) {
            out << " -";
        }
        if (deg == 0) {
            out << " " << std::abs(coef);
            continue;
        }
        if (deg == 1) {
            out << " " << std::abs(coef) << "x";
            continue;
        }
        out << " " << std::abs(coef) << "x^" << deg;
    }
    return out;
}