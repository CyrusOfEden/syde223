#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <random>
#include <fstream>
#include <filesystem>
#include "main.hpp"

using namespace std;

static default_random_engine rnd_gen;

int randint(const int low, const int high) {
    return uniform_int_distribution(low, high)(rnd_gen);
}

using namespace std;

void Polynomial::remove_zero_coefficients() {
    for (int i = coefficients.size() - 1; i >= 0; i -= 1) {
        if (coefficients.at(i) == 0) {
            coefficients.pop_back();
        } else {
            break;
        }
    }
    coefficients.shrink_to_fit();
}

Polynomial::Polynomial() {
    coefficients.resize(randint(0, 1000));
    for (int i = 0; i < coefficients.size(); i += 1) {
        coefficients.at(i) = randint(-1000, 1000);
    }
}

Polynomial::Polynomial(const string &file_name) {
    ifstream file(file_name);
    assert(file.is_open() && file.good());

    int power = 0;
    file >> power;
    coefficients.resize(power, 0);
    for (int i = 0; i < power; i += 1) {
        file >> coefficients.at(i);
    };
    file.close();
}

Polynomial::Polynomial(vector<int> coefs) {
    coefficients = std::move(coefs);
    remove_zero_coefficients();
};

Polynomial::Polynomial(int *coefs, int size) {
    coefficients.resize(size);
    for (int i = 0; i < size; i += 1) {
        coefficients.at(i) = *coefs;
        coefs++;
    }
    remove_zero_coefficients();
}

[[nodiscard]] int Polynomial::order() const {
    return coefficients.size();
};

bool Polynomial::operator!=(const Polynomial &p2) const {
    return !(this == &p2);
}

bool Polynomial::operator!=(const vector<int> p2) const {
    return !(*this == p2);
}

// Polynomial  == Polynomial
bool Polynomial::operator==(const Polynomial &p2) const {
    return p2 ==
           coefficients;
};

// Polynomial == vector
bool Polynomial::operator==(const vector<int> p2) const {
    return (
            order() == p2.size() &&
            equal(coefficients.cbegin(), coefficients.cend(), p2.cbegin())
    );
}

Polynomial Polynomial::operator*(const Polynomial &p) const {
    vector<int> coefs(order() + p.order(), 0);
    const Polynomial *lhs = this;
    const Polynomial *rhs = &p;

    for (int lh_power = 0; lh_power < lhs->order(); lh_power++) {
        for (int rh_power = 0; rh_power < rhs->order(); rh_power++) {
            coefs[lh_power + rh_power] += lhs->coefficients.at(lh_power) * rhs->coefficients.at(rh_power);
        }
    }

    return Polynomial(coefs);
};

Polynomial Polynomial::operator+(const Polynomial &p) const {
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

Polynomial Polynomial::operator-(const Polynomial &p) const {
    const int bigger_size = order() < p.order() ? p.order() : order();

    // Create a new vector for the summed coefficients
    vector<int> summed_coefs(bigger_size, 0);
    // Add the smaller polynomial's coefficients to this new vector
    for (int power = 0; power < bigger_size; power += 1) {
        if (power < coefficients.size()) {
            summed_coefs.at(power) += coefficients.at(power);
        }
        if (power < p.coefficients.size()) {
            summed_coefs.at(power) -= p.coefficients.at(power);
        }
    };

    return Polynomial(summed_coefs);
}

[[nodiscard]] Polynomial Polynomial::derivative() const {
    vector<int> derived_coefs(order() - 1, 0);
    // For every coefficient *EXCEPT THE ZERO'TH ONE*
    for (int power = 1; power < order(); power += 1) {
        derived_coefs.at(power - 1) = coefficients.at(power) * power;
    };

    return Polynomial(derived_coefs);
}

void Polynomial::print() const {
    stringstream equation;

    for (int power = order() - 1; power >= 0; power--) {
        stringstream term;
        int coef = coefficients.at(power);

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

    cout << equation.str();
}

class PolynomialTest {
public:
    static void empty_constructor() {
        cout << "\t" << "empty constructor" << endl;

        Polynomial A;
        Polynomial B;

        cout << "\t\t" << "two consecutive calls generate different polynomials" << endl;
        assert(A != B);
    }

    static void file_constructor() {
        cout << "\t" << "file constructor" << endl;

        cout << "\t\t" << "single digit coefficients" << endl;
        Polynomial A(filesystem::absolute("testA.txt"));
        vector<int> expectedA = {2, 3};
        assert(A == expectedA);

        cout << "\t\t" << "negative coefficients" << endl;
        Polynomial B(filesystem::absolute("testB.txt"));
        vector<int> expectedB = {5, -3, -1};
        assert(B == expectedB);

        cout << "\t\t" << "coefficients > 9" << endl;
        Polynomial C(filesystem::absolute("testC.txt"));
        vector<int> expectedC = {25, -12};
        assert(C == expectedC);
    }

    static void print() {
        cout << "\t" << "print" << endl;

        Polynomial A;

        A.print();
        cout << endl;
    }

    static void operator_equals() {
        cout << "\t" << "operator==" << endl;

        int x[] = {1, 2, 3};
        int y[] = {1, 2, 3, 4};

        Polynomial One(x, 3);
        Polynomial Two(y, 4);

        int a[] = {1, 2, 3};
        vector<int> b = {1, 2, 3};

        Polynomial Three(a, 3);

        cout << "\t\t" << "checking if the polynomials are different" << endl;
        assert(!(One == Two)); // checks they are different

        cout << "\t\t" << "checking if the polynomials are the same" << endl;
        assert(Three == b); // checks they are the same
    }

    static void operator_plus() {
        cout << "\t" << "operator+" << endl;

        int x[] = {3, 2, 1};
        int y[] = {4, 6, 7};
        vector<int> expectedAnswer = {7, 8, 8};

        Polynomial One(x, 3);
        Polynomial Two(y, 3);

        cout << "\t\t" << "basic addition" << endl;
        assert(One + Two == expectedAnswer);
        cout << "\t\t" << "associative" << endl;
        assert(Two + One == expectedAnswer);

        int z[] = {1, 2, 3, 4};
        vector<int> expectedAnswerTwo = {4, 4, 4, 4};

        Polynomial Four(z, 4);

        cout << "\t\t" << "adding polynomials of different orders" << endl;
        assert(Four + One == expectedAnswerTwo);
    }

    static void operator_minus() {
        cout << "\t" << "operator-" << endl;

        int x[] = {3, 2, 6};
        int y[] = {4, 6, 4};
        vector<int> expectedAnswer = {-1, -4, 2};
        vector<int> expectedAnswerTwo = {1, 4, -2};

        Polynomial One(x, 3);
        Polynomial Two(y, 3);

        cout << "\t\t" << "basic subtraction" << endl;
        assert(One - Two == expectedAnswer);
        cout << "\t\t" << "not associative" << endl;
        assert(Two - One == expectedAnswerTwo);

        int z[] = {1, 2, 3, 4};
        vector<int> expectedAnswerThree = {-2, 0, -3, 4};

        Polynomial Four(z, 4);

        cout << "\t\t" << "subtracting polynomials of different orders" << endl;
        assert(Four - One == expectedAnswerThree);
    }

    static void operator_times() {
        cout << "\t" << "operator*" << endl;

        int x[] = {1, 2, 3};
        int y[] = {4, 5, 6, 4};
        int z[] = {1};

        Polynomial One(x, 3);
        Polynomial Two(y, 4);
        Polynomial Identity(z, 1);
        vector<int> expectedAnswer = {4, 13, 28, 31, 26, 12};

        cout << "\t\t" << "multiplying two polynomials" << endl;
        assert(One * Two == expectedAnswer);

        cout << "\t\t" << "associative" << endl;
        assert(Two * One == expectedAnswer);

        cout << "\t\t" << "checking multiplying two polynomials" << endl;
        assert((Identity * One) == One);
    }

    static void derivative() {
        cout << "\t" << "derivative()" << endl;

        int x[] = {1, 2, 3};
        Polynomial One(x, 3);
        vector<int> expectedAnswer = {2, 6};

        cout << "\t\t" << "taking the derivative of a polynomial" << endl;
        assert(One.derivative() == expectedAnswer);

        int y[] = {4, 5, 6, 4};
        Polynomial Two(y, 4);
        vector<int> expectedAnswerTwo = {5, 12, 12};

        cout << "\t\t" << "taking another derivative of a different polynomial" << endl;
        assert(Two.derivative() == expectedAnswerTwo);

        cout << "\t\t" << "checking derivative order" << endl;
        assert(Two.derivative().order() == Two.order() - 1);
    }
};

int main() {
    srand(time(nullptr));

    cout << endl << "Polynomial" << endl << endl;
    PolynomialTest::file_constructor();
    cout << endl;
    PolynomialTest::empty_constructor();
    cout << endl;
    PolynomialTest::print();
    cout << endl;
    PolynomialTest::operator_equals();
    cout << endl;
    PolynomialTest::operator_plus();
    cout << endl;
    PolynomialTest::operator_minus();
    cout << endl;
    PolynomialTest::operator_times();
    cout << endl;
    PolynomialTest::derivative();

    cout << endl << endl << "All tests completed successfully!" << endl;
    return 0;
}
