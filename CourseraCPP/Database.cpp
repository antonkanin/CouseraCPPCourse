#include "database.h"

void Database::Add(const Date& date, const string& event)
{
	if (storage.count(date) == 0 || storage[date].first.count(event) == 0)
	{
		storage[date].first.insert(event);
		storage[date].second.push_back(event);
	}
}

string Database::Last(Date date)
{
	const auto it = storage.upper_bound(date);
	if (it != begin(storage))
	{
		const auto record = prev(it);
		const auto lastDate = record->first;
		const auto lastEvent = record->second.second.back();
		stringstream result;
		result << lastDate << " " << lastEvent;
		return result.str();
	}

	throw invalid_argument("No entries");
}

int Database::DeleteDate(const Date& date)
{
	if (storage.count(date) == 0)
	{
		return 0;
	}
	else
	{
		const int event_count = storage[date].second.size();
		storage.erase(date);
		return event_count;
	}
}

void Database::Print(ostream& outputStream) const
{
	for (const auto& item : storage)
	{
		for (const string& event : item.second.second)
		{
			outputStream << item.first << " " << event << endl;
		}
	}
}
