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
	this->denom = 1;
	this->isPos = true;
}

Fraction::Fraction(int v) {
	if (v < 0) {
		this->isPos = false;
	}
	if (v >= 0) {
		this->isPos = true;
	}
	this->wholeNum = abs(v);
	this->numer = 0;
	this->denom = 1;

}

Fraction::Fraction(const Fraction &other) {
	this->isPos = other.isPos;
	this->numer = other.numer;
	this->denom = other.denom;
	this->wholeNum = other.wholeNum;
}

Fraction::Fraction(Fraction &&other) {
	this->isPos = std::move(other.isPos);
	this->numer = std::move(other.numer);
	this->denom = std::move(other.denom);
	this->wholeNum = std::move(other.wholeNum);
}

Fraction::Fraction(std::string s) {
	this->wholeNum = 0;
	this->numer = 0;
	this->denom = 1;
	this->isPos = true;

	if (s[0] == '-') {
		isPos = false;
		s = s.substr(1);
	}

	if (s.find('/') == string::npos) {
		this->wholeNum = stoi(s);
		return;
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
	if (this->denom == 0)
		throw std::invalid_argument("No zeroes as denominators allowed!");
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
	this->isPos = other.isPos;
	this->numer = other.numer;
	this->denom = other.denom;
	this->wholeNum = other.wholeNum;
	return (*this);
}

Fraction& Fraction::operator=(Fraction &&other) {
	this->isPos = std::move(other.isPos);
	this->numer = std::move(other.numer);
	this->denom = std::move(other.denom);
	this->wholeNum = std::move(other.wholeNum);
	return (*this);
}

Fraction Fraction::operator+(int num) const {
	Fraction temp;
	int tempInt;
	temp = *this;
	if (temp.isPos == false) {
		tempInt = 0 - temp.wholeNum;
	} else
		tempInt = temp.wholeNum;
	tempInt = num + tempInt;
	if (tempInt < 0) {
		temp.wholeNum = abs(tempInt);
		temp.isPos = false;
	} else
		temp.wholeNum = tempInt;

	/*if (temp.isPos == false && num > 0) {
	 if (num >= temp.wholeNum) {
	 temp.wholeNum -= num;
	 temp.wholeNum = abs(temp.wholeNum);
	 temp.isPos = true;
	 }
	 if (num < temp.wholeNum) {
	 temp.wholeNum -= num;
	 }
	 }
	 if (temp.isPos == true && num < 0) {
	 if (abs(num) > temp.isPos) {
	 temp.wholeNum -= num;
	 temp.wholeNum = abs(temp.wholeNum);
	 temp.isPos = true;
	 }
	 if (abs(num) <= temp.isPos) {
	 temp.wholeNum -= num;
	 }
	 }
	 if (temp.isPos == false && num < 0) {
	 temp.wholeNum += abs(num);
	 }

	 else {
	 temp.wholeNum += num;
	 }
	 */

	return (temp);
}

Fraction Fraction::operator+(const Fraction &other) const {
	Fraction temp1;
	Fraction temp2;

	temp1.denom = this->denom * other.denom;
	temp2.denom = this->denom * other.denom;
	temp1.numer *= other.denom;
	temp2.numer *= this->denom;
	temp1.numer += this->wholeNum * temp1.denom;
	temp2.numer += other.wholeNum * temp2.denom;
	if (this->isPos == false)
		temp1.numer *= -1;
	if (other.isPos == false)
		temp2.numer *= -1;
	temp1.numer += temp2.numer;
	if (temp1.numer < 0) {
		temp1.isPos = false;
		temp1.numer = abs(temp1.numer);
	}

	/*if ((other.isPos == true && this->isPos == true)
	 | (other.isPos == false && this->isPos == false)) {
	 temp.wholeNum = this->wholeNum + other.wholeNum;
	 temp.denom = this->denom * other.denom;
	 temp.numer = (this->numer * other.denom) + (other.numer * this->denom);
	 temp.toProper();
	 }
	 if ((other.isPos == false && this->isPos == true)
	 | (other.isPos == true && this->isPos == false)) {
	 temp.wholeNum = this->wholeNum - other.wholeNum;
	 temp.denom = this->denom * other.denom;
	 temp.numer = (this->numer * other.denom) + (other.numer * this->denom);
	 temp.toProper();
	 }
	 */
	temp1.toProper();
	return {temp1};
}

Fraction Fraction::operator-() const {
	Fraction temp;
	temp = *this;
	if (temp.isPos == true)
		temp.isPos = false;
	if (temp.isPos == false)
		temp.isPos = true;
	return {temp};
}

Fraction Fraction::operator-(int val) const {
	Fraction temp;
	temp = *this;
	temp.wholeNum -= val;
	if (temp.wholeNum < 0) {
		temp.wholeNum = abs(temp.wholeNum);
		temp.isPos = false;
	}
	return (temp);
}

Fraction Fraction::operator-(const Fraction &other) const {
	Fraction temp1;
	Fraction temp2;

	temp1.denom = this->denom * other.denom;
	temp2.denom = this->denom * other.denom;
	temp1.numer *= other.denom;
	temp2.numer *= this->denom;
	temp1.numer += this->wholeNum * temp1.denom;
	temp2.numer += other.wholeNum * temp2.denom;
	if (this->isPos == false)
		temp1.numer *= -1;
	if (other.isPos == false)
		temp2.numer *= -1;
	temp1.numer -= temp2.numer;
	if (temp1.numer < 0) {
		temp1.isPos = false;
		temp1.numer = abs(temp1.numer);
	}
	temp1.toProper();
	return {temp1};
}

Fraction Fraction::operator*(int val) const {
	Fraction temp;
	temp.numer = this->numer * val;
	temp = temp.toProper();
	if (val < 0 && this->isPos == true)
		temp.isPos = false;
	if (val < 0 && this->isPos == false)
		temp.isPos = true;
	if (val > 0 && this->isPos == false)
		temp.isPos = false;
	if (val > 0 && this->isPos == true)
		temp.isPos = true;
	if (val == 0) {
		temp.wholeNum = 0;
		temp.numer = 0;
		temp.denom = 0;
		temp.isPos = true;
	}
	temp.toProper;
	return (temp);
}

Fraction Fraction::operator*(const Fraction &other) const {
	Fraction temp1;
	Fraction temp2;
	temp1 = *this;
	temp2 = other;
	temp1.numer += temp1.wholeNum * temp1.denom;
	temp2.numer += temp2.wholeNum * temp2.denom;
	temp1.numer = temp1.numer * temp2.numer;
	temp1.denom = temp1.denom * temp2.denom;
	if (temp1.isPos == temp2.isPos)
		temp1.isPos = true;
	else
		temp1.isPos = false;
	temp1.toProper();
	return {temp1};
}

optional<int> Fraction::operator[](int pos) const {
	return {};
}

bool Fraction::operator<(const Fraction &other) const {
	Fraction temp1;
	Fraction temp2;
	temp1 = this->toProper();
	temp2 = other.toProper();
	temp1.denom = this->denom * other.denom;
	temp2.denom = this->denom * other.denom;
	temp1.numer *= other.denom;
	temp2.numer *= this->denom;
	temp1.numer += this->wholeNum * temp1.denom;
	temp2.numer += other.wholeNum * temp2.denom;
	if (temp1.isPos == false && temp2.isPos == true)
		return (true);
	if (temp2.isPos == false && temp1.isPos == true)
		return (false);
	if ((temp1.numer < temp2.numer) && temp1.isPos == true)
		return (true);
	if ((temp1.numer < temp2.numer) && temp1.isPos != true)
		return (false);
	return (false);
}

bool Fraction::operator==(const Fraction &other) const {
	Fraction temp1;
	Fraction temp2;
	temp1 = this->toProper();
	temp2 = other.toProper();
	if (temp1.isPos == temp2.isPos && temp1.numer == temp2.numer
			&& temp1.denom == temp2.denom && temp1.wholeNum == temp2.wholeNum)
		return (true);
	return (false);
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

ostream& Fraction::writeTo(ostream &os) const {
	return os;
}

// You don't want to consume things outside of brackets
// read character by character, if the first char isn't a left bracket throw an error
istream& Fraction::readFrom(istream &sr) /*throw(std::invalid_argument) */{
	return sr;
}

bool Fraction::isReduced() const {
	if ((__gcd(this->numer, this->denom)) == 1) {
		return (true);
	}
	return (false);
}

//Maybe a mistake here in the tests
bool Fraction::isProper() const {
	/*if ((((__gcd(this->numer, this->denom)) == 1)
	 && (this->numer < this->denom)) | ((this->numer == 0))) {
	 return (true);
	 }
	 */
	if ((this->numer < this->denom) | (this->numer == 0)) {
		return (true);
	}
	return (false);
}

// Private input and output methods
ostream& operator<<(ostream &os, const Fraction &f) {
	return os;
}

istream& operator>>(istream &s, Fraction &f) {
	return (f.readFrom(s));
}

/*
 #if I_DO_EXTRA_CREDIT
 optional<string> Fraction::isRepeating() const { return {}; }

 string Fraction::operator()(int len) const { return {}; }
 #endif
 */
