//#include "pch.h"
#include <iostream>

using namespace std;

int getGCD(int a, int b)
{
	return b == 0 ? a : getGCD(b, a % b);
}

class Rational
{
public:
	Rational()
	{
		numberator = 0;
		denominator = 1;
	}

	Rational(int numerator, int denominator)
	{
		if (denominator < 0)
		{
			denominator = abs(denominator);
			numerator = -1 * numerator;
		}

		int gcd = getGCD(abs(numerator), abs(denominator));
		this->numberator = numerator / gcd;

		if (numerator == 0)
		{
			this->denominator = 1;
		}
		else
		{
			this->denominator = denominator / gcd;
		}
	}

	int Numerator() const
	{
		return numberator;
	}

	int Denominator() const
	{
		return denominator;
	}

private:
	int numberator;
	int denominator;
};

bool operator==(const Rational& lhs, const Rational& rhs)
{
	return (lhs.Numerator() == rhs.Numerator()) &&
		(lhs.Denominator() == rhs.Denominator());
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
	return { lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator() };
};

Rational operator-(const Rational& lhs, const Rational& rhs)
{
	return { lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator() };
};

Rational operator*(const Rational& lhs, const Rational& rhs)
{
	return { lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator() };
};

Rational operator/(const Rational& lhs, const Rational& rhs)
{
	return { lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator() };
};

int main()
{
	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a * b;
		bool equal = c == Rational(8, 9);
		if (!equal)
		{
			cout << "2/3 * 4/3 != 8/9" << endl;
			return 1;
		}
	}

	{
		Rational a(5, 4);
		Rational b(15, 8);
		Rational c = a / b;
		bool equal = c == Rational(2, 3);
		if (!equal)
		{
			cout << "5/4 / 15/8 != 2/3" << endl;
			return 2;
		}
	}

	cout << "OK" << endl;
	return 0;
}