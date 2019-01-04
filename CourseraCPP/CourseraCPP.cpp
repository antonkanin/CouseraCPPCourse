//#include "pch.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

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
		numerator = 0;
		denominator = 1;
	}

	Rational(int numerator, int denominator)
	{
		if (denominator == 0)
		{
			throw invalid_argument("Denominator is 0");
		}

		if (denominator < 0)
		{
			denominator = abs(denominator);
			numerator = -1 * numerator;
		}

		const int gcd = getGCD(abs(numerator), abs(denominator));
		this->numerator = numerator / gcd;

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
		return numerator;
	}

	int Denominator() const
	{
		return denominator;
	}

private:
	int numerator;
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
	if (rhs.Numerator() == 0)
	{
		throw domain_error("Denumerator is 0");
	}

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

bool operator<(const Rational& lhs, const Rational& rhs)
{
	const int left = lhs.Numerator() * rhs.Denominator();
	const int right = rhs.Numerator() * lhs.Denominator();

	return left < right;
}

void DoWork(istream& inputStream)
{
	Rational lhs, rhs;
	char operation;

	inputStream >> lhs >> operation >> rhs;

	if (operation == '+')
	{
		cout << lhs + rhs;
	}
	else if (operation == '-')
	{
		cout << lhs - rhs;
	}
	else if (operation == '*')
	{
		cout << lhs * rhs;
	}
	else if (operation == '/')
	{
		cout << lhs / rhs;
	}
}

int main()
{
	try
	{
		DoWork(cin);
	}
	catch (invalid_argument ex)
	{
		cout << "Invalid argument";
	}
	catch (domain_error ex)
	{
		cout << "Division by zero";
	}
	
	return 0;
}
