#include "Fraction.h"
#include <algorithm>
#include <iomanip>
#include <regex>

using namespace std;

/* Friend functions */
Fraction operator+(int val, const Fraction &f) { return {}; }

Fraction operator-(int val, const Fraction &f) { return {}; }

Fraction operator*(int val, const Fraction &f) { return {}; }

//Constructors
Fraction::Fraction() {}

Fraction::Fraction(int v) {}

Fraction::Fraction(const Fraction &other) {}

Fraction::Fraction(Fraction &&other) {}

Fraction::Fraction(std::string s) {
	wholeNum = 0;
	numer = 0;
	denom = 0;
	isPos = true;

	// do this one first
	// Need to parse out the negative
	if(s[0]=='-')
		isPos = false;
	if (s.find('/') == std::string::npos){
		this->wholeNum=std::stoi(s);
	}
}

// Access functions
int Fraction::whole() const { return (this->wholeNum); }

int Fraction::numerator() const { return (this->numer); }

int Fraction::denominator() const { return (this->denom); }

bool Fraction::isPositive() const { return (this->isPos); }


// Operator functions
Fraction& Fraction::operator=(const Fraction &other) { return *this; }

Fraction& Fraction::operator=(Fraction &&other) { return *this; }

Fraction Fraction::operator+(int num) const { return {}; }

Fraction Fraction::operator+(const Fraction &other) const { return {}; }

Fraction Fraction::operator-() const { return {}; }

Fraction Fraction::operator-(int val) const { return {}; }

Fraction Fraction::operator-(const Fraction &other) const { return {}; }

Fraction Fraction::operator*(int val) const { return {}; }

Fraction Fraction::operator*(const Fraction &other) const { return {}; }

optional<int> Fraction::operator[](int pos) const { return {}; }

bool Fraction::operator<(const Fraction &other) const { return {}; }

bool Fraction::operator==(const Fraction &other) const { return {}; }


// Conversion functions
void Fraction::makeProper() {}

Fraction Fraction::toProper() const { return {}; }

void Fraction::reduce() {}

Fraction Fraction::toReduced() const { return {}; }

ostream &Fraction::writeTo(ostream &os) const { return os; }

istream &Fraction::readFrom(istream &sr) /*throw(std::invalid_argument) */ {
    return sr;
}

bool Fraction::isReduced() const { return {}; }

bool Fraction::isProper() const { return {}; }


// Private input and output methods
ostream &operator<<(ostream &os, const Fraction &f) { return os; }

istream &operator>>(istream &s, Fraction &f) { return s; }

#if I_DO_EXTRA_CREDIT
optional<string> Fraction::isRepeating() const { return {}; }

string Fraction::operator()(int len) const { return {}; }
#endif
