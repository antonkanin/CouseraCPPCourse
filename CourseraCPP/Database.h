#pragma once

#include "Date.h"
#include <map>
#include <set>
#include <iostream>

using namespace std;

class Database
{
public:
	void Add(const Date& date, const string& events);

	template <typename Pr>
	int RemoveIf(Pr);

	template <typename Pr>
	set<string> FindIf(Pr) const;

	string Last(Date date);



	// old events
	void AddEvent(const Date& date, const string& event);

	bool DeleteEvent(const Date& date, const string& event);

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
set<string> Database::FindIf(Pr) const
{
	return { {} };
}
