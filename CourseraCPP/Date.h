#pragma once
#include <vector>
#include <iomanip>

using namespace std;

class Date
{
public:
	Date(int new_year, int new_month, int new_day);

	int GetYear() const;

	int GetMonth() const;

	int GetDay() const;

private:
	int year;
	int month;
	int day;
};


inline bool operator<(const Date& lhs, const Date& rhs)
{
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
		vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

inline bool operator==(const Date& lhs, const Date& rhs)
{
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} ==
		vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

inline bool operator <=(const Date& lhs, const Date& rhs)
{
	return lhs < rhs || lhs == rhs;
}

inline bool operator>(const Date& lhs, const Date& rhs)
{
	return rhs < lhs;
}

inline bool operator>=(const Date& lhs, const Date& rhs)
{
	return rhs <= lhs;
}

inline bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs == rhs);
}

inline ostream& operator<<(ostream& stream, const Date& date)
{
	stream << setw(4) << setfill('0') << date.GetYear() <<
		"-" << setw(2) << setfill('0') << date.GetMonth() <<
		"-" << setw(2) << setfill('0') << date.GetDay();
	return stream;
}

Date ParseDate(istream& date_stream);
