//#include "pch.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Year
{
	explicit Year(int year) : value(year)
	{}
	int value;
};

struct Month
{
	explicit Month(int month) : value(month)
	{}
	int value;
};

struct Day
{
	explicit Day(int day) : value(day)
	{}
	int value;
};

class Date
{
public:
	Date(Year year, Month month, Day day) : year(year), month(month), day(day)
	{}

	int GetYear() const
	{
		return year.value;
	}

	int GetMonth() const
	{
		return month.value;
	}

	int GetDay() const
	{
		return day.value;
	}

private:
	Year year;
	Month month;
	Day day;
};


bool operator<(const Date& lhs, const Date& rhs)
{
	return 
		(lhs.GetYear() < rhs.GetYear()) ||
		(lhs.GetYear() == rhs.GetYear() &&	lhs.GetMonth() < rhs.GetMonth()) ||
		(lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() < rhs.GetDay());
}

ostream& operator<<(ostream& stream, const Date& date)
{
	stream <<
		setw(4) << setfill('0') << date.GetYear() << "-" <<
		setw(2) << setfill('0') << date.GetMonth() << "-" << 
		setw(2) << setfill('0') << date.GetDay();

	return stream;
}

class Database
{
public:
	void AddEvent(const Date& date, const string& event)
	{
		if (database.count(date) > 0)
		{
			database.at(date).insert(event);
		}
		else
		{
			database[date] = { event };
		}
	}

	bool DeleteEvent(const Date& date, const string& event)
	{
		if (database.count(date) > 0 && database.at(date).count(event) > 0)
		{
			database[date].erase(event);
			cout << "Deleted successfully" << endl;
			return true;
		}
		cout << "Event not found" << endl;
		return false;
	}

	int DeleteDate(const Date& date)
	{
		const int count = database.count(date);

		if (count > 0)
		{
			cout << "Deleted " + to_string(database.at(date).size()) + " events" << endl;
			database.erase(date);
		}
		else
		{
			cout << "Deleted 0 events" << endl;
		}

		return count;
	}

	void Find(const Date& date) const
	{
		if (database.count(date) > 0)
		{
			for (const auto& item : database.at(date))
			{
				cout << item << endl;
			}
		}
	}

	void Print() const
	{
		for (const auto& date : database)
		{
			for (const auto& event : date.second)
			{
				cout << date.first << " " << event << endl;
			}
		}
	}

private:
	map<Date, set<string>> database;
};

Date TryParseDate(const string& date)
{
	if (date.size() == 0)
	{
		throw runtime_error("Wrong date format: " + date);
	}

	stringstream ss(date);

	int year;
	if ((ss >> year).fail())
	{
		throw runtime_error("Wrong date format: " + date);
	}

	if (ss.peek() != '-')
	{
		throw runtime_error("Wrong date format: " + date);
	}

	ss.ignore(1);

	int month;
	if ((ss >> month).fail() || ss.peek() != '-')
	{
		throw runtime_error("Wrong date format: " + date);
	}

	ss.ignore(1);

	int day;
	
	if ((ss >> day).fail() || !ss.eof())
	{
		throw runtime_error("Wrong date format: " + date);
	}

	if (month < 1 || month > 12)
	{
		throw runtime_error("Month value is invalid: " + to_string(month));
	}

	if (day < 1 || day > 31)
	{
		throw runtime_error("Day value is invalid: " + to_string(day));
	}


	return { Year(year), Month(month), Day(day) };
}

void DoWork(istream& inputStream)
{
	Database db;

	string inputLine;
	while (getline(inputStream, inputLine))
	{
		if (inputLine == "")
		{
			continue;
		}

		stringstream commandStream(inputLine);
		string command;
		commandStream >> command;

		if (command == "Add")
		{
			string date, event;
			commandStream >> date >> event;
			db.AddEvent(TryParseDate(date), event);
		}
		else if (command == "Del")
		{
			string date;
			commandStream >> date;
			if (commandStream.eof())
			{
				db.DeleteDate(TryParseDate(date));
			}
			else
			{
				string event;
				commandStream >> event;
				db.DeleteEvent(TryParseDate(date), event);
			}
		}
		else if (command == "Find")
		{
			string date;
			commandStream >> date;
			db.Find(TryParseDate(date));
		}
		else if (command == "Print")
		{
			db.Print();
		}
		else
		{
			throw runtime_error("Unknown command: " + command);
		}
	}
}

int main()
{
	//ifstream inputFile("input.txt");
	//string line;
	//while (getline(inputFile, line))
	//{
	//	try
	//	{
	//		stringstream ss(line);
	//		DoWork(ss);
	//	}
	//	catch (runtime_error ex)
	//	{
	//		cout << ex.what() << endl;
	//	}
	//}

	try
	{
		//ifstream inputFile("input.txt");
		//DoWork(inputFile);
		DoWork(cin);
	}
	catch (runtime_error ex)
	{
		cout << ex.what() << endl;
	}

	return 0;
}
