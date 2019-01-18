#pragma once
#include <string>
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

inline ostream& operator<<(ostream& stream, const Date& date)
{
	stream << setw(4) << setfill('0') << date.GetYear() <<
		"-" << setw(2) << setfill('0') << date.GetMonth() <<
		"-" << setw(2) << setfill('0') << date.GetDay();
	return stream;
}

Date ParseDate(istream& date_stream)
{
	bool ok = true;

	int year;
	ok = ok && (date_stream >> year);
	ok = ok && (date_stream.peek() == '-');
	date_stream.ignore(1);

	int month;
	ok = ok && (date_stream >> month);
	ok = ok && (date_stream.peek() == '-');
	date_stream.ignore(1);

	int day;
	ok = ok && (date_stream >> day);
	ok = ok && date_stream.eof();

	if (!ok)
	{
		throw logic_error("Wrong Date format");
	}
	return Date(year, month, day);
}