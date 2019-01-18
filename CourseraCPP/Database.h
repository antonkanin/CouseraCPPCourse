#pragma once

#include "Date.h"
#include <map>
#include <set>
#include <utility>
#include <sstream>

using namespace std;

class Database
{
public:
	void Add(const Date& date, const string& events);

	template <typename Pr>
	int RemoveIf(Pr);

	template <typename Pr>
	vector<string> FindIf(Pr) const;

	string Last(Date date);

	int DeleteDate(const Date& date);

	void Print(ostream& outputStream) const;

private:
	map<Date, set<string>> storage;
};

template <typename Pr>
int Database::RemoveIf(Pr predicate)
{
	int removedCount = 0;

	for (auto it = storage.begin(); it != storage.end();)
	{
		if (predicate(it->first, {}))
		{
			removedCount += storage[it->first].size();
			storage.erase(it++);
		}
		else
		{
			if (storage.count(it->first) > 0)
			{
				removedCount += storage.count(it->first);
				auto& events = storage.at(it->first);

				for (auto it_event = events.begin(); it_event != events.end();)
				{
					if (predicate(it->first, *it_event))
					{
						events.erase(it_event++);
					}
					else
					{
						++it_event;
					}
				}
			}

			++it;
		}
	}

	return removedCount;
}

template <typename Pr>
vector<string> Database::FindIf(Pr predicate) const
{
	vector<string> result;

	for (auto& date : storage)
	{
		for (auto& event : date.second)
		{
			if (predicate(date.first, event))
			{
				stringstream ss;
				ss << date.first << " " << event;
				result.push_back(ss.str());
			}
		}
	}

	return result;
}
