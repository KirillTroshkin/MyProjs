#pragma once
#include <cstdint>
#include <map>
#include <ostream>
#include <vector>

class Poly {
public:
    Poly() = default;
    Poly(std::initializer_list<std::pair<const size_t, int64_t>> poly_ins);
    explicit Poly(const std::vector<int64_t>& poly_ins);
    int64_t operator()(const int64_t x) const;
    bool operator==(const Poly& other) const;
    bool operator!=(const Poly& other) const;
    void operator=(const Poly& other);
    Poly operator+(const Poly& other) const;
    Poly operator-(const Poly& other) const;
    void operator+=(const Poly& other);
    void operator-=(const Poly& other);
    Poly operator*(const Poly& other) const;
    void operator*=(const Poly& other);
    friend Poly operator-(const Poly& p);
    friend std::ostream& operator<<(std::ostream& o, const Poly& p);

private:
    std::map<const size_t, int64_t, std::greater<const size_t>> poly_ins_;
};

Poly operator-(const Poly& p);
std::ostream& operator<<(std::ostream& o, const Poly& p);