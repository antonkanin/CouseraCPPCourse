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
	map<Date, pair<set<string>, vector<string>>> storage;
};

template <typename Pr>
int Database::RemoveIf(Pr predicate)
{
	int removedCount = 0;

	for (auto it = storage.begin(); it != storage.end();)
	{
		if (predicate(it->first, {}))
		{
			removedCount += storage[it->first].second.size();
			storage.erase(it++);
		}
		else
		{
			if (storage.count(it->first) > 0)
			{
				// cleaning up the set
				auto& events_set = storage.at(it->first).first;
				for (auto it_set = events_set.begin(); it_set != events_set.end();)
				{
					if (predicate(it->first, *it_set))
					{
						++removedCount;
						events_set.erase(it_set++);
					}
					else
					{
						++it_set;
					}
				}

				// cleaning up the vector
				auto& events_vector = storage.at(it->first).second;
				for (auto it_vector = events_vector.begin(); it_vector != events_vector.end();)
				{
					if (predicate(it->first, *it_vector))
					{
						events_vector.erase(it_vector++);
					}
					else
					{
						++it_vector;
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
		for (auto& event : date.second.first)
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
