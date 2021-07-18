#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

#include "MFraction.h"

int GCD(int a, int b) {
	if (b == 0) {
		return abs(a);
	}
	else {
		GCD(b, a % b);
	}
}

MFraction::MFraction(int w, int n, int d) {
	whole = w;
	numerator = n;
	denominator = d;                                                       //denominator can not be 0
}

MFraction MFraction::setWhole(int w) {                                     //sets the whole number
	whole = w;
	return *this;
}
 
MFraction MFraction::setNumerator(int n) {								   //sets the numerator
	numerator = n;
	return *this;
}
MFraction MFraction::setDenominator(int d) {                               //sets the denominator
	denominator = d;
	return *this;
}

int MFraction::getWhole() const {                                          //gets the whole number
	return whole;                           
}

int MFraction::getNumerator() const {									   //gets the numerator
	return numerator; 
}

int MFraction::getDenominator() const {									  //gets the denominator
	return denominator;
}

MFraction MFraction::operator+(const MFraction& s) const {
	MFraction sum;
	MFraction mixedFract1;
	MFraction mixedFract2;                                                 //mixedFract1 + mixedFract2 = sum

	//changes to improper before adding
	if (whole != 0 && s.whole != 0) {                                      //both inputs have a whole number
		mixedFract1.numerator = (abs(whole) * denominator) + numerator;
		mixedFract2.numerator = (abs(s.whole) * s.denominator) + s.numerator;
	}
	else if (whole == 0 && s.whole != 0) {                                 //second input has whole and first doesnt
		mixedFract1.numerator = numerator;
		mixedFract2.numerator = (abs(s.whole) * s.denominator) + s.numerator;
	}
	else if (whole != 0 && s.whole == 0) {                                 //first input has whole and second doesnt
		mixedFract1.numerator = (abs(whole) * denominator) + numerator;
		mixedFract2.numerator = s.numerator;
	}
	else if (whole == 0 && s.whole == 0) {                                 //both inputs do not have whole number
		mixedFract1.numerator = numerator;
		mixedFract2.numerator = s.numerator;
	}
	if (whole < 0) {
		mixedFract1.numerator *= -1;
	}
	if (s.whole < 0) {
		mixedFract1.numerator *= -1;
	}
	//set to common denominators before adding
	int lcm;															   //least common multiple

	lcm = (denominator * s.denominator) / GCD(denominator, s.denominator); //lcm = (a*b)/GCD(a,b)
	mixedFract1.numerator *= (lcm / denominator);						   //numerators get multiplied by the same number denominators get multiplied by
	mixedFract2.numerator *= (lcm / s.denominator);

	sum.numerator = mixedFract1.numerator + mixedFract2.numerator;         //add numerators
	sum.denominator = lcm;												   //denominators do not add

	while (abs(sum.numerator) >= sum.denominator) {                         //change improper to mixed fraction
		if (sum.numerator > 0) {										   	
			sum.numerator -= sum.denominator;
			sum.whole += 1;												   //add 1 if numerator is positive				
		}
		else if (sum.numerator < 0) {
			sum.numerator += sum.denominator;
			sum.whole -= 1;										           //minus 1 if numerator is negative
			sum.numerator = abs(sum.numerator);                            //whole number holds negative instead of numerator
		}
	}
	//reduced form
	int gcd;

	gcd = GCD(sum.numerator, sum.denominator);
	sum.numerator /= gcd; 
	sum.denominator /= gcd;                                                //divide numerator & denominator by GCD

	return sum;
}

MFraction MFraction::operator-(const MFraction& s) const {
	MFraction mixedFract1;
	MFraction mixedFract2;												   
	MFraction diff;							 							   //mixedFract1 - mixedFract2 = diff

	//changes to improper before subtracting
	if (whole != 0 && s.whole != 0) {                                      //both inputs have a whole number
		mixedFract1.numerator = ((abs(whole) * denominator) + numerator);
		mixedFract2.numerator = ((abs(s.whole) * s.denominator) + s.numerator);
	}
	else if (whole == 0 && s.whole != 0) {								   //second input has whole and first doesnt
		mixedFract1.numerator = numerator;
		mixedFract2.numerator = ((abs(s.whole) * s.denominator) + s.numerator);
	}
	else if (whole != 0 && s.whole == 0) {								   //first input has whole and second doesnt
		mixedFract1.numerator = ((abs(whole) * denominator) + numerator);
		mixedFract2.numerator = s.numerator;
	}
	else if (whole == 0 && s.whole == 0) {								   //both inputs do not have whole number
		mixedFract1.numerator = numerator;
		mixedFract2.numerator = s.numerator;
	}
	if (whole < 0) {
		mixedFract1.numerator *= -1;
	}
	if (s.whole < 0) {
		mixedFract2.numerator *= -1;
	}
	//set denominators equal to each other 
	int lcm;													           //least common multiple

	lcm = (denominator * s.denominator) / GCD(denominator, s.denominator); //lcm = (a*b)/gcd
	mixedFract1.numerator *= (lcm / denominator);						   //numerators get multiplied by the same number denominators get multiplied by
	mixedFract2.numerator *= (lcm / s.denominator);

	diff.numerator = mixedFract1.numerator - mixedFract2.numerator;        //subtract numerators
	diff.denominator = lcm;												   //denominators do not get subtracted

	//change from improper to mixed fraction
	while (abs(diff.numerator) >= diff.denominator) {                       
		if (diff.numerator > 0) {
			diff.numerator -= diff.denominator;
			diff.whole += 1;                                               //add 1 to whole if numerator is positive
		}
		else if (diff.numerator < 0){
			diff.numerator += diff.denominator;
			diff.whole -= 1;
			diff.numerator = abs(diff.numerator);						   //whole # holds negative sign
		}
	}
	//reduced form
	int gcd;

	gcd = GCD(diff.numerator, diff.denominator);
	diff.numerator /= gcd;
	diff.denominator /= gcd;                                               //divide numerator & denominator by GCD

	return diff;	
}

MFraction MFraction::operator*(const MFraction& s) const {
	MFraction p;														   //product

	//convert to improper form
	if (whole != 0 && s.whole != 0) {									   //both inputs have whole numbers
		p.numerator = ((abs(whole) * denominator) + numerator) * ((abs(s.whole) * s.denominator) + s.numerator);
	}
	else if (whole == 0 && s.whole != 0) {								   //second input has whole, first doesnt
		p.numerator = numerator * ((abs(s.whole) * s.denominator) + s.numerator);
	}
	else if (whole != 0 && s.whole == 0) {								   //first input has whole, second doesnt
		p.numerator = ((abs(whole) * denominator) + numerator) * s.numerator;
	}
	else if (whole == 0 && s.whole == 0) {								   //both inputs do not have whole numbers
		p.numerator = numerator * s.numerator;
	}
	if ((whole < 0 && s.whole >= 0) ||(whole >= 0 && s.whole < 0)) {
		p.numerator *= -1;
	}
	p.denominator = denominator * s.denominator;                           //multiply numerator and denominator across

	//convert back to mixed
	while (abs(p.numerator) >= p.denominator) {
		if (p.numerator > 0) {
			p.numerator -= p.denominator;                                  
			p.whole += 1;												   //add 1 to whole when numerator is positive
		}
		else if (p.numerator < 0) {
			p.numerator += p.denominator;
			p.whole -= 1;												   //minus 1 to whole when numerator is negative
			p.numerator = abs(p.numerator);                                //whole number holds the negative sign
		}
	}
	//reduced form
	int gcd;

	gcd = GCD(p.numerator, p.denominator);
	p.numerator /= gcd;
	p.denominator /= gcd;                                                  //divide numerator & denominator by GCD

	return p;
}

MFraction MFraction::operator/(const MFraction& s) const {
	MFraction q;														   //quotient

	//convert to improper form
	if (whole != 0 && s.whole != 0) {									   //both inputs have whole numbers
		q.numerator = ((abs(whole) * denominator) + numerator) * s.denominator;
		q.denominator = denominator * (abs(s.whole) * s.denominator + s.numerator);
	}
	else if (whole == 0 && s.whole != 0) {								   //second input has whole, first doesnt
		q.numerator = numerator * denominator;
		q.denominator = denominator * ((abs(s.whole) * s.denominator) + s.numerator);
	}
	else if (whole != 0 && s.whole == 0) {								   //first input has whole, second doesnt
		q.numerator = ((abs(whole) * denominator) + numerator) * s.denominator;
		q.denominator = denominator * s.numerator;
	}
	else if (whole == 0 && s.whole == 0) {								   //both inputs have no whole number
		q.numerator = numerator * s.denominator;
		q.denominator = denominator * s.numerator;                         //multiply by reciprocol
	}

	if (whole < 0) {
		q.numerator *= -1;
	}
	if (s.whole < 0) {
		q.numerator *= -1;
	}
	//convert from improper to mixed
	while (abs(q.numerator) >= q.denominator) {
		if (q.numerator > 0) {
			q.numerator -= q.denominator;
			q.whole += 1;                                                   //plus 1 to whole when numerator is postive
		}
		else if (q.numerator < 0) {
			q.numerator += q.denominator;
			q.whole -= 1;                                                   //minus 1 to whole when numerator is negative
			q.numerator = abs(q.numerator);                                 //whole number holds the negative sign
		}
	}
	//reduced form
	int gcd;

	gcd = GCD(q.numerator, q.denominator);
	q.numerator /= gcd;
	q.denominator /= gcd;                                                //divide numerator & denominator by GCD

	return q;
}

MFraction MFraction::operator-() const {
	MFraction negation;

	negation.whole = whole * -1;                                            //whole number holds the negative
	negation.numerator = numerator;
	negation.denominator = denominator;

	return negation;
}

istream &operator>>(istream& in, MFraction& f){
	char dummy1;
	char dummy2;
	int whole;
	int numerator;
	int denominator;
                                                                                                                                   
	in.clear();
	in >> whole;
	in >> noskipws >> dummy1; 

	if (in.good() && dummy1 == '/') {									   //case 1: fraction is inputted as n/d (no whole)
		in >> skipws >> denominator;												   
		f.numerator = whole;
		f.denominator = denominator;
		f.whole = 0;

	}
	else {																   //case 2: fraction is inputted as w n/d
		in >> skipws >> numerator >> dummy2;
		if (in.good()) {
			in >> denominator;
			if (in.good()) {
				f.whole = whole;
				f.numerator = numerator;
				f.denominator = denominator;
			}
		}
	}
	return in;
}

ostream &operator<<(ostream& out, const MFraction& f) {
	if (f.whole != 0) {
		out << f.whole << " " << f.numerator << "/" << f.denominator;	   //output form: w n/d
	}
	else {
		out << f.numerator << "/" << f.denominator;						   //output form: n/d
	}
	return out;
}

void MFraction::printFloat() const {
	float n = numerator;
	float d = denominator;
	float w = whole;
	float output;
	if (w < 0) {
		output = ((-n / d + w));
	}
	else {
		output = ((n / d + w));
	}
	cout << "Its floating-point value is " << setprecision(2) << fixed << output << endl;
}

bool MFraction::operator<(const MFraction& s) const {
	return (whole < s.whole) && (numerator < s.numerator) && (denominator < s.denominator);
}

bool MFraction::operator<=(const MFraction& s) const {
	return (whole <= s.whole) && (numerator <= s.numerator) && (denominator <= s.denominator);
}

bool MFraction::operator>(const MFraction& s) const {
	return (whole > s.whole) && (numerator > s.numerator) && (denominator > s.denominator);
}

bool MFraction::operator>=(const MFraction& s) const {
	return (whole >= s.whole) && (numerator >= s.numerator) && (denominator >= s.denominator);
}

bool MFraction::operator==(const MFraction& s) const {
	return (whole == s.whole) && (numerator == s.numerator) && (denominator == s.denominator);
}

bool MFraction:: operator!=(const MFraction& s) const {
	return (whole != s.whole) && (numerator != s.numerator) && (denominator != s.denominator);
}

