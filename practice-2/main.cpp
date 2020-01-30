#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

static default_random_engine rnd_gen;

int randint(const int low, const int high) {
    return uniform_int_distribution(low, high)(rnd_gen);
}

using namespace std;

class Polynomial {
    vector<int> coefficients;

public:
    Polynomial() {
        coefficients.resize(randint(0, 1000));
        for (int i = 0; i < coefficients.size(); i += 1) {
            coefficients.at(i) = randint(-1000, 1000);
        }
    }

    explicit Polynomial(const string &file_name) {
        ifstream file(file_name);
        int power;
        file >> power; // # of coefs
        file.ignore(); // \n
        coefficients.resize(power);
        for (int i = 0; i < power; i += 1) {
            file >> coefficients.at(i);
            file.ignore();
        };
    }

    explicit Polynomial(vector<int> coefs) : coefficients(std::move(coefs)) {};

    Polynomial(int *coefs, int size) {
        coefficients.resize(size);
        for (int i = 0; i < size; i += 1) {
            coefficients[i] = *coefs;
            coefs++;
        }
    }

    [[nodiscard]] int order() const {
        return coefficients.size();
    };

    bool operator==(const Polynomial &p2) const {
        return (
                // Are they of the same order?
                order() == p2.order() &&
                // Are the contents the same?
                equal(coefficients.begin(), coefficients.end(), p2.coefficients.begin());
        );
    };

    Polynomial operator*(const Polynomial &p) const {
        vector<int> coefs(order() * p.order());
        const Polynomial *lhs = this;
        const Polynomial *rhs = &p;

        for (int lh_power = 0; lh_power < lhs->order(); lh_power++) {
            for (int rh_power = 0; rh_power < rhs->order(); rh_power++) {
                coefs[lh_power * rh_power] += lhs->coefficients.at(lh_power) * rhs->coefficients.at(rh_power);
            }
        }

        return Polynomial(coefs);
    };

    Polynomial operator+(const Polynomial &p) const {
        // Ensure that we have a smaller one and a bigger one
        const Polynomial *smaller = this;
        const Polynomial *bigger = &p;
        if (smaller->order() > bigger->order()) {
            const Polynomial *tmp = bigger;
            bigger = smaller;
            smaller = tmp;
        }

        // Create a new vector for the summed coefficients
        vector<int> summed_coefs(bigger->coefficients);
        // Add the smaller polynomial's coefficients to this new vector
        for (int i = 0; i < smaller->coefficients.size(); i += 1) {
            summed_coefs.at(i) += smaller->coefficients.at(i);
        };

        return Polynomial(summed_coefs);
    };

    Polynomial operator-(const Polynomial &p) const {
        // Ensure that we have a smaller one and a bigger one
        const Polynomial *smaller = this;
        const Polynomial *bigger = &p;
        if (smaller->order() > bigger->order()) {
            const Polynomial *tmp = bigger;
            bigger = smaller;
            smaller = tmp;
        }

        // Create a new vector for the summed coefficients
        vector<int> summed_coefs(bigger->coefficients);
        // Add the smaller polynomial's coefficients to this new vector
        for (int i = 0; i < smaller->coefficients.size(); i += 1) {
            summed_coefs.at(i) -= smaller->coefficients.at(i);
        };

        return Polynomial(summed_coefs);
    }

    [[nodiscard]] Polynomial derivative() const {
        vector<int> derived_coefs(order() - 1);
        // For every coefficient *EXCEPT THE ZERO'TH ONE*
        for (int power = 1; power < order(); power += 1) {
            derived_coefs.at(power - 1) = coefficients.at(power) * power;
        };

        return Polynomial(derived_coefs);
    }

    friend ostream operator<<(ostream &os, const Polynomial &p);

    void print() const {
        cout << this;
    }
};

ostream operator<<(ostream &os, const Polynomial &p) {
    stringstream equation;

    for (int power = p.order() - 1; power >= 0; power--) {
        stringstream term;
        int coef = p.coefficients.at(power);

        if (coef > 0) {
            term << coef;
        } else {
            term << "(" << coef << ")";
        }

        if (power != 0) {
            term << "x^" << power << " + ";
        }

        equation << term.str();
    };

    os << equation.str();
};

void test_empty_constructor() {
    cout << "\t" << "empty constructor" << endl;
    // Check that 2 consecutive calls to this constructor generate different polynomials.
}

void test_print() {
    cout << "\t" << "print" << endl;
}

void test_operator_equals() {
    cout << "\t" << "operator==" << endl;
    // Test ==
}

void test_operator_plus() {
    cout << "\t" << "operator+" << endl;
    // Test p1 + p2 = expected
    // 3 different test cases — p1.order() < p2.order(), p2.order() > p1.order(), p1.order() == p2.order()
}

void test_operator_minus() {
    cout << "\t" << "operator-" << endl;
    // Test p1 + p2 = expected
    // Test p1 - p2 = expected
    // 3 different test cases — p1.order() < p2.order(), p2.order() > p1.order(), p1.order() == p2.order()
}

void test_operator_times() {
    cout << "\t" << "operator*" << endl;
    // Test p1 * p2 = expected
    // 3 different test cases — p1.order() < p2.order(), p2.order() > p1.order(), p1.order() == p2.order()
}

void test_derivative() {
    cout << "\t" << "derivative()" << endl;
    // Test p.derivative()
    // 3 different test cases
}

int main() {
    srand(time(nullptr));

    cout << endl << "Polynomial" << endl << endl;
    test_empty_constructor();
    cout << endl;
    test_print();
    cout << endl;
    test_operator_equals();
    cout << endl;
    test_operator_plus();
    cout << endl;
    test_operator_minus();
    cout << endl;
    test_operator_times();
    cout << endl;
    test_derivative();

    cout << endl << endl << "All tests completed successfully!" << endl;

    return 0;
}
