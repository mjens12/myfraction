#include "Fraction.h"
#include <algorithm>
#include <iomanip>
#include <regex>

using namespace std;

/* Friend functions */
Fraction operator+(int val, const Fraction &f) {
	return {};
}

Fraction operator-(int val, const Fraction &f) {
	return {};
}

Fraction operator*(int val, const Fraction &f) {
	return {};
}

//Constructors
Fraction::Fraction() {
	this->wholeNum = 0;
	this->numer = 0;
	this->denom = 0;
	this->isPos = true;
}

Fraction::Fraction(int v) {
	if (v <= 0){
		this->isPos = false;
	}
	this->wholeNum = abs(v);
	this->numer = 0;
	this->denom = 0;
	this->isPos = true;
}

Fraction::Fraction(const Fraction &other) {
}

Fraction::Fraction(Fraction &&other) {
}

Fraction::Fraction(std::string s) {
	this->wholeNum = 0;
	this->numer = 0;
	this->denom = 0;
	this->isPos = true;

	if (s[0] == '-') {
		isPos = false;
		s = s.substr(1);
	}

	if (s.find('/') == string::npos) {
		this->wholeNum = stoi(s);
		break;
	}

	if (s.find(' ') == std::string::npos && s.find('/') != string::npos) {
		int pos = s.find("/");
		this->numer = stoi(s.substr(0, pos));
		this->denom = stoi(s.substr(pos + 1));
	}

	if (s.find(' ') != std::string::npos && s.find('/') != string::npos) {
		int pos1 = s.find(" ");
		int pos2 = s.find("/");
		this->wholeNum = stoi(s.substr(0, pos1));
		this->numer = stoi(s.substr(pos1 + 1, pos2));
		this->denom = stoi(s.substr(pos2 + 1));
	}

}

// Access functions
int Fraction::whole() const {
	return (this->wholeNum);
}

int Fraction::numerator() const {
	return (this->numer);
}

int Fraction::denominator() const {
	return (this->denom);
}

bool Fraction::isPositive() const {
	return (this->isPos);
}

// Operator functions
Fraction& Fraction::operator=(const Fraction &other) {
	return *this;
}

Fraction& Fraction::operator=(Fraction &&other) {
	return *this;
}

Fraction Fraction::operator+(int num) const {
	return {};
}

Fraction Fraction::operator+(const Fraction &other) const {
	return {};
}

Fraction Fraction::operator-() const {
	return {};
}

Fraction Fraction::operator-(int val) const {
	return {};
}

Fraction Fraction::operator-(const Fraction &other) const {
	return {};
}

Fraction Fraction::operator*(int val) const {
	return {};
}

Fraction Fraction::operator*(const Fraction &other) const {
	return {};
}

optional<int> Fraction::operator[](int pos) const {
	return {};
}

bool Fraction::operator<(const Fraction &other) const {
	return {};
}

bool Fraction::operator==(const Fraction &other) const {
	return {};
}

// Conversion functions
void Fraction::makeProper() {
	reduce();
	if (this->numer >= this->denom) {
		int temp1 = this->numer / this->denom;
		int temp2 = this->numer % this->denom;
		this->wholeNum = this->wholeNum + temp1;
		this->numer = temp2;
	}
}

Fraction Fraction::toProper() const {
	Fraction temp = toReduced();
	if (temp.numer >= temp.denom) {
		int temp1 = temp.numer / temp.denom;
		int temp2 = temp.numer % temp.denom;
		temp.wholeNum = temp.wholeNum + temp1;
		temp.numer = temp2;
	}
	return (temp);
}

void Fraction::reduce() {
	int tempGCD = __gcd(this->numer, this->denom);
	this->numer = (this->numer / tempGCD);
	this->denom = (this->denom / tempGCD);
}

Fraction Fraction::toReduced() const {
	// Use this syntax for declaring Fractions
	Fraction temp;
	int tempGCD = __gcd(this->numer, this->denom);
	temp.numer = (this->numer / tempGCD);
	temp.denom = (this->denom / tempGCD);
	return (temp);
}

ostream &Fraction::writeTo(ostream &os) const {
	return os;
}


// You don't want to consume things outside of brackets
// read character by character, if the first char isn't a left bracket throw an error
istream &Fraction::readFrom(istream &sr) /*throw(std::invalid_argument) */{
	return sr;
}

bool Fraction::isReduced() const {
	if ((__gcd(this->numer, this->denom)) == 1) {
		return {true};
	}
	return {false};
}

bool Fraction::isProper() const {
	if (((__gcd(this->numer, this->denom)) == 1)
			&& (this->numer < this->denom)) {
		return {true};
	}
	return {false};
}

// Private input and output methods
ostream &operator<<(ostream &os, const Fraction &f) {
	return os;
}

istream &operator>>(istream &s, Fraction &f) {
	return (f.readFrom(s));
}

/*
 #if I_DO_EXTRA_CREDIT
 optional<string> Fraction::isRepeating() const { return {}; }

 string Fraction::operator()(int len) const { return {}; }
 #endif
 */
