#include "pch.h"

#include "Database.h"

void Database::Add(const Date& date, const string& event)
{
	storage[date].insert(event);
}

string Database::Last(Date date)
{
	return {};
}

bool Database::DeleteEvent(const Date& date, const string& event)
{
	if (storage.count(date) > 0 && storage[date].count(event) > 0)
	{
		storage[date].erase(event);
		return true;
	}
	return false;
}

int Database::DeleteDate(const Date& date)
{
	if (storage.count(date) == 0)
	{
		return 0;
	}
	else
	{
		const int event_count = storage[date].size();
		storage.erase(date);
		return event_count;
	}
}

void Database::Print(ostream& outputStream) const
{
	for (const auto& item : storage)
	{
		for (const string& event : item.second)
		{
			outputStream << item.first << " " << event << endl;
		}
	}
}
