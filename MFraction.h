#ifndef MFRACTION_H
#define MFRACTION_H

class MFraction
{
	public:
		MFraction(int w = 0, int n = 0, int d = 1);
		MFraction setWhole(int w);
		MFraction setNumerator(int n);
		MFraction setDenominator(int d);
		int getWhole() const;
		int getNumerator() const;
		int getDenominator() const;
		MFraction operator+(const MFraction& s) const;
		MFraction operator-(const MFraction& s) const;
		MFraction operator*(const MFraction& s) const;
		MFraction operator/(const MFraction& s) const;
		MFraction operator-() const;
		friend istream &operator>>(istream& in, MFraction& f);
		friend ostream &operator<<(ostream& out, const MFraction& f);
		void printFloat() const;
		bool operator<(const MFraction& s) const;
		bool operator<=(const MFraction& s) const;
		bool operator>(const MFraction& s) const;
		bool operator>=(const MFraction& s) const;
		bool operator==(const MFraction& s) const;
		bool operator!=(const MFraction& s) const;


	private:
		int whole;
		int numerator;
		int denominator;
};

#endif