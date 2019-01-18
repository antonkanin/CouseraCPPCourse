#pragma once

#include "Date.h"
#include <map>
#include <set>
#include <utility>
#include <sstream>
#include <algorithm>

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
int Database::RemoveIf(Pr)
{
	//if (storage.count(Pr.Date))
	//{
	//	
	//}
	return 0;
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
