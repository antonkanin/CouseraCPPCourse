//#include "pch.h"
#include <iostream>
#include <sstream>
#include <set>
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

bool operator<(const Rational& lhs, const Rational& rhs)
{
	const int left = lhs.Numerator() * rhs.Denominator();
	const int right = rhs.Numerator() * lhs.Denominator();

	return left < right;
}

int main()
{
	{
		const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
		if (rs.size() != 3)
		{
			cout << "Wrong amount of items in the set" << endl;
			return 1;
		}

		vector<Rational> v;
		for (auto x : rs)
		{
			v.push_back(x);
		}
		if (v != vector<Rational>{
			{
				1, 25
			}, { 1, 2 }, { 3, 4 }})
		{
			cout << "Rationals comparison works incorrectly" << endl;
			return 2;
		}
	}

	{
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];

		++count[{2, 3}];

		if (count.size() != 2)
		{
			cout << "Wrong amount of items in the map" << endl;
			return 3;
		}
	}

	cout << "OK" << endl;
	return 0;
}
