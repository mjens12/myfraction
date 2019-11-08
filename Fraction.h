#pragma once
#include <iostream>
#include <optional>
#include <string>

using std::istream;
using std::optional;
using std::ostream;
using std::string;

//https://cis.gvsu.edu/~dulimarh/vp/cs343/02-fraction.html


// Each non member function resolves to one call to a membet function
class Fraction {
    // Only two of these actually need to be friend functions
	friend ostream &operator<<(ostream &, const Fraction &);
    friend istream &operator>>(istream &, Fraction &);
    friend Fraction operator+(int, const Fraction &);
    friend Fraction operator-(int, const Fraction &);
    friend Fraction operator*(int, const Fraction &);

  public:
    /* Constructors */
    Fraction();
    Fraction(int);
    Fraction(string);
    Fraction(const Fraction &);
    Fraction(Fraction &&);

    // Access functions
    int whole() const;
    int numerator() const;
    int denominator() const;
    bool isPositive() const;

    // Conversion functions
    void reduce();     // Convert fraction to reduced form
    void makeProper(); // Convert fraction to proper form
    Fraction toProper() const;
    Fraction toReduced() const;
    bool isReduced() const;
    bool isProper() const;

    // Operator functions
    Fraction &operator=(const Fraction &);      // Copy assignment
    Fraction &operator=(Fraction &&);           // Move assignment
    Fraction operator+(int) const;              // Add Fraction + int
    Fraction operator+(const Fraction &) const; // Add Fraction + Fraction
    Fraction operator-() const;                 // unary minus
    Fraction operator-(int) const;              // binary minus: Frac - int
    Fraction operator-(const Fraction &) const; // binary minus: Frac - Frac
    Fraction operator*(int)const;               // Multiply: Frac * int
    Fraction operator*(const Fraction &)const;  // Multiply: Frac * Frac
    bool operator<(const Fraction &) const;     // Compare Frac < Frac
    bool operator==(const Fraction &) const;    // Compare Frac == Frac
    optional<int> operator[](int) const;        // Component access Frac[i]

/*#if I_DO_EXTRA_CREDIT
    // Implement these two OR add your own operator(s)
    optional<string> isRepeating() const;
    string operator()(int) const;
#endif
*/

  private:
    ostream &writeTo(ostream &) const;
    istream &readFrom(istream &);
    int wholeNum;
	int numer;
	int denom;
	bool isPos;
};

/* Friend functions (non-member functions) */
ostream &operator<<(ostream &, const Fraction &);
// It returns the same istream so that you can chain the operators
istream &operator>>(istream &, Fraction &);
Fraction operator+(int, const Fraction &); // Add: int + Fraction
