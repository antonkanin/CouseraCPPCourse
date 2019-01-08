//#include "pch.h"
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>


using namespace std;
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

//bool IsPalindrom(string s)
//{
//	for (size_t i = 0; i < s.size() / 2; ++i)
//	{
//		if (s[i] != s[s.size() - i - 1])
//		{
//			return false;
//		}
//	}
//	return true;
//}

void RunTests()
{
	// Positive
	Assert(IsPalindrom(""), "emptry string");
	Assert(IsPalindrom("a"), "one character");
	Assert(IsPalindrom("aa"), "a");
	Assert(IsPalindrom("a a"), "'a a'");
	Assert(IsPalindrom(" a a "), "' a a '");
	Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");

	// neagative
	Assert(!IsPalindrom("a "), "'a '");
	Assert(!IsPalindrom(" a"), "' a'");
	Assert(!IsPalindrom(" a  "), "' a  '");
	Assert(!IsPalindrom("  a "), "'  a '");
	Assert(!IsPalindrom("aabb"), "aabb");
	Assert(!IsPalindrom("122"), "122");
}

int main()
{
	TestRunner runner;
	runner.RunTest(RunTests, "RunTests");
	return 0;
}