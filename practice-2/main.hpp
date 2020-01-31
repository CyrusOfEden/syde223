#ifndef PRACTICE_2_MAIN_HPP
#define PRACTICE_2_MAIN_HPP

#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

class Polynomial {
    vector<int> coefficients;
    friend class PolynomialTest;

public:
    Polynomial();

    explicit Polynomial(const string &file_name);

    explicit Polynomial(vector<int> coefs);

    Polynomial(int *coefs, int size);

    [[nodiscard]] int order() const;

    bool operator==(const Polynomial &p2) const;

    Polynomial operator+(const Polynomial &p) const;

    Polynomial operator-(const Polynomial &p) const;

    [[nodiscard]] Polynomial derivative() const;

    void print() const;
};


#endif //PRACTICE_2_MAIN_HPP
