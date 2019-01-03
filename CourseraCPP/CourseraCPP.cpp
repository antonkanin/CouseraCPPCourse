//#include "pch.h"
#include <iostream>
#include <sstream>

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

ostream& operator<<(ostream& stream, const Rational& value)
{
	stream << value.Numerator() << "/" << value.Denominator();
	return stream;
}

istream& operator>>(istream& stream, Rational& value)
{
	int numerator = 0;
	int denumerator = -1;
	if (!stream)
	{
		return stream;
	}

	stream >> numerator;
	stream.ignore(1);

	if (!stream)
	{
		return stream;
	}

	stream >> denumerator;

	value = Rational(numerator, denumerator);

	return stream;
}

int main()
{
	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4")
		{
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal)
		{
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct)
		{
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 3;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct)
		{
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 4;
		}
	}

	cout << "OK" << endl;
	return 0;
}
