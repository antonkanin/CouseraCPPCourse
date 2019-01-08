//#include "pch.h"
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s)
{
	os << "{";
	bool first = true;
	for (const auto& x : s)
	{
		if (!first)
		{
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s)
{
	os << "{";
	bool first = true;
	for (const auto& x : s)
	{
		if (!first)
		{
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m)
{
	os << "{";
	bool first = true;
	for (const auto& kv : m)
	{
		if (!first)
		{
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {})
{
	if (t != u)
	{
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty())
		{
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint)
{
	AssertEqual(b, true, hint);
}

class TestRunner
{
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name)
	{
		try
		{
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (exception& e)
		{
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
		catch (...)
		{
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner()
	{
		if (fail_count > 0)
		{
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

//int GreatestCommonDivisor(int a, int b)
//{
//	if (b == 0)
//	{
//		return a;
//	}
//	else
//	{
//		return GreatestCommonDivisor(b, a % b);
//	}
//}
//
//class Rational
//{
//public:
//	Rational()
//	{  
//		numerator = 0;
//		denominator = 1;
//	}
//
//	Rational(int new_numerator, int new_denominator)
//	{
//		const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
//		numerator = new_numerator / gcd;
//		denominator = new_denominator / gcd;
//		
//		if (denominator < 0)
//		{
//			denominator = -denominator;
//			numerator = -numerator;
//		}
//	}
//
//	int Numerator() const
//	{
//		return numerator;
//	}
//
//	int Denominator() const
//	{
//		return denominator;
//	}
//
//private:
//	int numerator;
//	int denominator;
//};

void TestEmptyCtor()
{
	Rational r;
	Assert(r.Numerator() == 0, "Empty rational numerator is 0");
	Assert(r.Denominator() == 1, "Empty rational numerator is 1");
}

void TestFractionReduction()
{
	Rational r1(2, 2);
	Assert(r1.Numerator() == 1, "2/2 numerator is 1");
	Assert(r1.Denominator() == 1, "2/2 denominator is 1");

	Rational r2(8, 8);
	Assert(r2.Numerator() == 1, "8/8 numerator is 1");
	Assert(r2.Denominator() == 1, "8/8 denominator is 1");

	Rational r3(2, 4);
	Assert(r3.Numerator() == 1, "2/4 numerator is 1");
	Assert(r3.Denominator() == 2, "2/4 denominator is 2");
}

void TestNegative()
{
	Rational r1(-1, 1);
	Assert(r1.Numerator() == -1, "-1/1 numerator is -1");
	Assert(r1.Denominator() == 1, "-1/1 denominator is 1");

	Rational r2(1, -1);
	Assert(r2.Numerator() == -1, "1/-1 numerator is -1");
	Assert(r2.Denominator() == 1, "1/-1 denominator is 1");

	Rational r3(-1, -1);
	Assert(r3.Numerator() == 1, "-1/-1 numerator is 1");
	Assert(r3.Denominator() == 1, "-1/-1 denominator is 1");
}

void TestZeroNumerator()
{
	Rational r1(0, 2);
	Assert(r1.Numerator() == 0, "0/2 numerator is 0");
	Assert(r1.Denominator() == 1, "0/2 denominator is 1");
}

int main()
{
	TestRunner runner;
	runner.RunTest(TestEmptyCtor, "TestEmptyCtor");
	runner.RunTest(TestFractionReduction, "TestFractionReduction");
	runner.RunTest(TestNegative, "TestNegative");
	runner.RunTest(TestZeroNumerator, "TestZeroNumerator");

	// tests
	
	return 0;
}
