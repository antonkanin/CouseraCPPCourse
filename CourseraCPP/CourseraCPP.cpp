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

double FindDiscriminant(double a, double b, double c)
{
	return b * b - 4 * a * c;
}

int GetDistinctRealRootCount(double A, double B, double C)
{
	// find D
	double D = FindDiscriminant(A, B, C);

	// if D == 0 then it's a linear equation: Bx + C = 0
	if (A == 0)
	{
		if (B != 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	if (D == 0) // there is just one root
	{  
		return 1;
	}

	if (D > 0) // two roots
	{  
		return 2;
	}

	// D < 0
	return 0;
}

// D < 0, 0 roots
void TestRootsCount_Dl0()
{
	Assert(GetDistinctRealRootCount(1, 1, 1) == 0, "A 1 / B 1 / C 1 - 0 root, D < 0");
}

// A == 0, B != 0
void TestRootsCount_A0_Bn0()
{
	Assert(GetDistinctRealRootCount(0, 1, 1) == 1, "A 0 / B 1 / C 1 - 1 root");
}

// A == 0, B == 0
void TestRootsCount_A0B0()
{
	Assert(GetDistinctRealRootCount(0, 0, 1) == 0, "A 0 / B 0 / C 1 - 0 root");
}

// D == 0
void TestRootsCount_D0()
{
	Assert(GetDistinctRealRootCount(1, 2, 1) == 1, "A 1 / B 2 / C 1 - 1 root");
}

// D > 0, A != 0
void TestRootsCount_D0Am0()
{
	Assert(GetDistinctRealRootCount(3, -5, 1) == 2, "A 3 / B -5 / C 1 - 2 root");
}

int main()
{
	TestRunner runner;
	runner.RunTest(TestRootsCount_Dl0, "TestRootsCount_Dl0");
	runner.RunTest(TestRootsCount_A0_Bn0, "TestRootsCount_A0_Bn0");
	runner.RunTest(TestRootsCount_A0B0, "TestRootsCount_A0B0");
	runner.RunTest(TestRootsCount_D0, "TestRootsCount_D0");
	runner.RunTest(TestRootsCount_D0Am0, "TestRootsCount_D0Am0");

	// adding your own tests

	return 0;
}