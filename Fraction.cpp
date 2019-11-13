#include "Fraction.h"
#include <algorithm>
#include <iomanip>
#include <regex>

using namespace std;

// Calls the fraction plus integer method
Fraction operator+(int val, const Fraction &f) {
	Fraction temp;
	temp = f;
	temp = temp + val;
	return (temp);
}

// Calls the fraction minus integer method
Fraction operator-(int val, const Fraction &f) {
	Fraction temp;
	temp = f;
	temp = temp - val;
	if (temp.isPos == true)
		temp.isPos = false;
	else
		temp.isPos = true;
	return (temp);
}

// Calls the fraction times integer method
Fraction operator*(int val, const Fraction &f) {
	Fraction temp;
	temp = f;
	temp = temp * val;
	return (temp);
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

// Parses out the passed string into a fraction
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

// Copies one fraction into another
Fraction& Fraction::operator=(const Fraction &other) {
	this->isPos = other.isPos;
	this->numer = other.numer;
	this->denom = other.denom;
	this->wholeNum = other.wholeNum;
	return (*this);
}

// Moves fraction data from one to another (if there had been any non primitive data in the fractions)
Fraction& Fraction::operator=(Fraction &&other) {
	this->isPos = std::move(other.isPos);
	this->numer = std::move(other.numer);
	this->denom = std::move(other.denom);
	this->wholeNum = std::move(other.wholeNum);
	return (*this);
}

// Converts the fraction and int into similar denoms and adds them
Fraction Fraction::operator+(int num) const {
	Fraction temp1;
	Fraction temp2;

	temp1 = *this;
	temp2.numer = num;
	temp2.denom = 1;

	//temp1.numer *= other.denom;
	temp2.numer *= this->denom;
	//temp1.denom = this->denom * other.denom;
	temp2.denom = this->denom * temp2.denom;
	temp1.numer += temp1.wholeNum * temp1.denom;
	//temp2.numer += temp2.wholeNum * temp2.denom;
	if (temp1.isPos == false)
		temp1.numer = 0 - temp1.numer;
	if (temp2.isPos == false)
		temp2.numer = 0 - temp2.numer;
	temp1.numer += temp2.numer;
	if (temp1.numer < 0) {
		temp1.isPos = false;
		temp1.numer = abs(temp1.numer);
	}

	temp1 = temp1.toReduced();
	temp1 = temp1.toProper();
	return (temp1);
}

// Converts both fractions into similar denoms and adds them
Fraction Fraction::operator+(const Fraction &other) const {
	Fraction temp1;
	Fraction temp2;

	temp1 = *this;
	temp2 = other;

	temp1.numer *= other.denom;
	temp2.numer *= this->denom;
	temp1.denom = this->denom * other.denom;
	temp2.denom = this->denom * other.denom;
	temp1.numer += temp1.wholeNum * temp1.denom;
	temp2.numer += temp2.wholeNum * temp2.denom;
	if (temp1.isPos == false)
		temp1.numer = 0 - temp1.numer;
	if (temp2.isPos == false)
		temp2.numer = 0 - temp2.numer;
	temp1.numer += temp2.numer;
	if (temp1.numer < 0) {
		temp1.isPos = false;
		temp1.numer = abs(temp1.numer);
	}

	temp1 = temp1.toReduced();
	temp1 = temp1.toProper();
	return (temp1);
}

// Converts the fraction's isPos to the opposite
Fraction Fraction::operator-() const {
	Fraction temp;
	temp = *this;
	if (temp.isPos == true)
		temp.isPos = false;
	else
		temp.isPos = true;
	return (temp);
}

// Converts the fraction and int into similar denoms and subtracts them
Fraction Fraction::operator-(int val) const {
	Fraction temp1;
	Fraction temp2;

	temp1 = *this;
	temp2.numer = val;
	temp2.denom = 1;

	//temp1.numer *= other.denom;
	temp2.numer *= this->denom;
	//temp1.denom = this->denom * other.denom;
	temp2.denom = this->denom * temp2.denom;
	temp1.numer += temp1.wholeNum * temp1.denom;
	//temp2.numer += temp2.wholeNum * temp2.denom;
	if (temp1.isPos == false)
		temp1.numer = 0 - temp1.numer;
	if (temp2.isPos == false)
		temp2.numer = 0 - temp2.numer;
	temp1.numer -= temp2.numer;
	if (temp1.numer < 0) {
		temp1.isPos = false;
		temp1.numer = abs(temp1.numer);
	}

	temp1 = temp1.toReduced();
	temp1 = temp1.toProper();
	return (temp1);
}

// Converts the two fractions into similar denoms and subtracts them
Fraction Fraction::operator-(const Fraction &other) const {
	Fraction temp1;
	Fraction temp2;

	temp1 = *this;
	temp2 = other;

	temp1.numer *= other.denom;
	temp2.numer *= this->denom;
	temp1.denom = this->denom * other.denom;
	temp2.denom = this->denom * other.denom;
	temp1.numer += temp1.wholeNum * temp1.denom;
	temp2.numer += temp2.wholeNum * temp2.denom;
	if (temp1.isPos == false)
		temp1.numer = 0 - temp1.numer;
	if (temp2.isPos == false)
		temp2.numer = 0 - temp2.numer;
	temp1.numer -= temp2.numer;
	if (temp1.numer < 0) {
		temp1.isPos = false;
		temp1.numer = abs(temp1.numer);
	}

	temp1 = temp1.toReduced();
	temp1 = temp1.toProper();
	return (temp1);
}

// Multiplies the fraction's numerator by the int
Fraction Fraction::operator*(int val) const {
	Fraction temp;
	temp.numer = this->numer + (this->wholeNum * this->denom);
	temp.wholeNum = 0;
	temp.numer = temp.numer * abs(val);
	temp.denom = this->denom;
	temp.isPos = this->isPos;

	if (val < 0) {
		if (this->isPos == true)
			temp.isPos = false;
		else
			temp.isPos = true;
	}
	if (val > 0) {
		if (this->isPos != false)
			temp.isPos = true;
		else
			temp.isPos = false;
	}
	if (val == 0) {
		temp.wholeNum = 0;
		temp.numer = 0;
		temp.denom = 1;
		temp.isPos = true;
	}
	temp = temp.toReduced();
	temp = temp.toProper();
	return (temp);
}

// Multiplies the fractions across
Fraction Fraction::operator*(const Fraction &other) const {
	Fraction temp1;
	Fraction temp2;

	temp1 = *this;
	temp2 = other;

	temp1.numer = temp1.numer + (this->wholeNum * this->denom);
	temp2.numer = temp2.numer + (other.wholeNum * other.denom);

	temp1.numer = temp1.numer * temp2.numer;
	temp1.denom = temp1.denom * temp2.denom;
	if (temp1.isPos == temp2.isPos)
		temp1.isPos = true;
	else
		temp1.isPos = false;
	temp1 = temp1.toReduced();
	temp1 = temp1.toProper();
	return (temp1);
}

// Gets specific parts of the fraction, returns optional
// nothing if there is nothing in that part of the fraction
optional<int> Fraction::operator[](int pos) const {
	int temp;
	if (pos == 0) {
		if (this->wholeNum == 0)
			return {};
		else {
			if (this->isPos == false)
				temp = 0 - this->wholeNum;
			else
				temp = this->wholeNum;
		}
		return (temp);
	}
	if (pos == 1) {
		if (this->numer == 0)
			return {};
		else {
			if (this->isPos == false && this->wholeNum == 0)
				temp = 0 - this->numer;
			else
				temp = this->numer;
		}
		return (temp);
	}
	if (pos == 2) {
		if (this->denom == 1)
			return {};
		else
			return this->denom;
	}

}

// Checks if the first fraction is less than the second one
bool Fraction::operator<(const Fraction &other) const {

	Fraction temp1 = *this;
	Fraction temp2 = other;

	temp1 = *this;
	temp2 = other;

	temp1.numer *= other.denom;
	temp2.numer *= this->denom;
	temp1.denom = this->denom * other.denom;
	temp2.denom = this->denom * other.denom;
	temp1.numer += temp1.wholeNum * temp1.denom;
	temp2.numer += temp2.wholeNum * temp2.denom;

	if (temp1.isPos == false)
		temp1.numer = 0 - temp1.numer;
	if (temp2.isPos == false)
		temp2.numer = 0 - temp2.numer;
	if (temp1.numer < temp2.numer)
		return (true);
	return (false);
}

// Checks if two fractions are equal to each other
bool Fraction::operator==(const Fraction &other) const {
	Fraction temp1 = *this;
	Fraction temp2 = other;

	temp1 = temp1.toReduced();
	temp1 = temp1.toProper();

	temp2 = temp2.toReduced();
	temp2 = temp2.toProper();

	if ((temp1.isPos == temp2.isPos) && (temp1.numer == temp2.numer)
			&& (temp1.denom == temp2.denom)
			&& (temp1.wholeNum == temp2.wholeNum))
		return (true);
	return (false);
}

// Makes a fraction proper
void Fraction::makeProper() {
	if (this->numer >= this->denom) {
		int temp1 = this->numer / this->denom;
		int temp2 = this->numer % this->denom;
		if ((this->numer % this->denom) == 0) {
			this->denom = 1;
			this->numer = 0;
		}
		this->wholeNum = this->wholeNum + temp1;
		this->numer = temp2;
	}
}

// Returns a new fraction that is the proper version of the original fraction
Fraction Fraction::toProper() const {
	Fraction temp = *this;
	if (temp.numer >= temp.denom) {
		int temp1 = temp.numer / temp.denom;
		int temp2 = temp.numer % temp.denom;
		temp.wholeNum = temp.wholeNum + temp1;
		temp.numer = temp2;
	}
	if ((temp.numer % temp.denom) == 0) {

		temp.numer = 0;
		temp.denom = 1;
	}
	temp.isPos = this->isPos;

	return (temp);
}

// Reduces a fraction
void Fraction::reduce() {
	int tempGCD = __gcd(this->numer, this->denom);
	this->numer = (this->numer / tempGCD);
	this->denom = (this->denom / tempGCD);
}

// Returns a fraction that is the reduced version of the original one
Fraction Fraction::toReduced() const {
	Fraction temp;

	int tempGCD = __gcd(this->numer, this->denom);
	temp.numer = (this->numer / tempGCD);
	temp.denom = (this->denom / tempGCD);
	temp.isPos = this->isPos;
	return (temp);
}

// Prints out a fraction
ostream& Fraction::writeTo(ostream &os) const {
	string temp;
	temp += '[';
	if (this->isPos == false)
		temp += '-';
	if (this->wholeNum != 0) {
		temp += to_string(this->wholeNum);
	}
	if (this->wholeNum == 0 && this->numer == 0)
		temp += '0';
	if ((this->wholeNum != 0) && (this->numer != 0))
		temp += ' ';
	if (this->numer != 0) {
		temp += to_string(this->numer);
		temp += '/';
		temp += to_string(this->denom);
	}
	temp += ']';
	os << temp;
	return os;
}

// Reads in a fraction from an istream
istream& Fraction::readFrom(istream &sr) {
	this->wholeNum = 0;
	this->numer = 0;
	this->denom = 1;
	this->isPos = true;

	string st;
	int tempWhole = 0;
	int tempNum = 0;
	int tempDenom = 1;

	char ch;
	int i = 0;

	while (sr.peek() != '[') {
		sr.get();
		if (sr.fail())
			throw std::invalid_argument("Must start with [ !");
	}


	sr.get();

	while (sr.peek() != '/' | sr.peek() != ' ') {

		ch = sr.get();
		if (ch == '-') {
			this->isPos = false;
			ch = sr.get();
		}

		if (sr.fail())
			break;

		st += ch;
		if (sr.peek() == ']') {
			sr.get();
			break;
		}
	}
	if (sr.peek() == ' ') {
		tempWhole = stoi(st);
		st = "";
	}

	if (sr.peek() == '/') {
		tempNum = stoi(st);
	} else
		tempWhole = stoi(st);

	if (sr.peek() == '/') {
		st = "";
		while (sr.peek()
				== ('0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')) {
			ch = sr.get();
			st += ch;
		}
		if (sr.peek()
				!= ('0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')) {
			throw std::invalid_argument("Invalid input after the / !");
		}
		tempDenom = stoi(st);
	}

	this->wholeNum = tempWhole;
	this->numer = tempNum;
	this->denom = tempDenom;

	return (sr);
}

// Checks if a fraction is in reduced form
bool Fraction::isReduced() const {
	if ((__gcd(this->numer, this->denom)) == 1) {
		return (true);
	}
	return (false);
}

// Checks if a fraction is in proper form
bool Fraction::isProper() const {
	if ((this->numer >= this->denom)
			| (this->wholeNum != 0 && this->numer == 0))
		return (false);
	return (true);
}

// Private input and output methods
ostream& operator<<(ostream &os, const Fraction &f) {
	return (f.writeTo(os));
}

istream& operator>>(istream &s, Fraction &f) {
	return (f.readFrom(s));
}
