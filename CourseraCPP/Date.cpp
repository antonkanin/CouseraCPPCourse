#include "pch.h"
#include "Date.h"

Date::Date(int new_year, int new_month, int new_day)
{
	year = new_year;
	if (new_month > 12 || new_month < 1)
	{
		throw logic_error("Month value is invalid: " + to_string(new_month));
	}
	month = new_month;
	if (new_day > 31 || new_day < 1)
	{
		throw logic_error("Day value is invalid: " + to_string(new_day));
	}
	day = new_day;
}

int Date::GetYear() const
{
	return year;
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
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
