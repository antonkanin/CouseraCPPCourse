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

//string FindNameByYear(const map<int, string>& names, int year)
//{
//	string name;
//
//	for (const auto& item : names)
//	{
//		if (item.first <= year)
//		{
//			name = item.second;
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	return name;
//}
//

//class Person
//{
//public:
//	void ChangeFirstName(int year, const string& first_name)
//	{
//		first_names[year] = first_name;
//	}
//	void ChangeLastName(int year, const string& last_name)
//	{
//		last_names[year] = last_name;
//	}
//
//	string GetFullName(int year)
//	{
//		const string first_name = FindNameByYear(first_names, year);
//		const string last_name = FindNameByYear(last_names, year);
//
//		if (first_name.empty() && last_name.empty())
//		{
//			return "Incognito";
//		}
//		else if (first_name.empty())
//		{
//			return last_name + " with unknown first name";
//		}
//		else if (last_name.empty())
//		{
//			return first_name + " with unknown last name";
//		}
//		else
//		{
//			return first_name + " " + last_name;
//		}
//	}
//private:
//		map<int, string> first_names;
//		map<int, string> last_names;
//};

void TestIncognito()
{
	Person p{};
	Assert(p.GetFullName(0) == "Incognito", "Testing incognito");
}

void TestNoLastName()
{
	Person p{};
	p.ChangeFirstName(0, "firstname_1");
	Assert(p.GetFullName(1) == "firstname_1 with unknown last name", "Testing firstname_1 with no last name");

	p.ChangeFirstName(1, "firstname_2");
	Assert(p.GetFullName(2) == "firstname_2 with unknown last name", "Testing firstname_2 with no last name");
}

void TestNoFirstNameName()
{
	Person p{};
	
	p.ChangeLastName(0, "lastname_1");
	Assert(p.GetFullName(1) == "lastname_1 with unknown first name", "Testing no first name");

	p.ChangeLastName(1, "lastname_2");
	Assert(p.GetFullName(2) == "lastname_2 with unknown first name", "Testing no first name");
}

void TestWithFirstAndLastName()
{
	Person p{};

	p.ChangeFirstName(1, "firstname_1");
	p.ChangeLastName(1, "lastname_1");

	Assert(p.GetFullName(0) == "Incognito", "Testing incognito");
	Assert(p.GetFullName(1) == "firstname_1 lastname_1", "Correct firstname_1 lastname_1 in the year 1");
	Assert(p.GetFullName(2) == "firstname_1 lastname_1", "Correct firstname_1 lastname_1 in the year 2");
	

	p.ChangeFirstName(0, "firstname_0");
	p.ChangeLastName(0, "lastname_0");

	Assert(p.GetFullName(0) == "firstname_0 lastname_0", "Correct firstname_1 lastname_1 in the year 1");
	Assert(p.GetFullName(1) == "firstname_1 lastname_1", "Correct firstname_1 lastname_1 in the year 1");
	Assert(p.GetFullName(2) == "firstname_1 lastname_1", "Correct firstname_1 lastname_1 in the year 2");
}

int main()
{
	TestRunner runner;
	runner.RunTest(TestIncognito, "TestIncognito");
	runner.RunTest(TestNoLastName, "TestNoLastName");
	runner.RunTest(TestNoFirstNameName, "TestNoFirstNameName");
	runner.RunTest(TestWithFirstAndLastName, "TestWithFirstAndLastName");
	
	return 0;
}
