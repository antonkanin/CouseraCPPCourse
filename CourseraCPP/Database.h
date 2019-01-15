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

	// old events
	void AddEvent(const Date& date, const string& event);

	bool DeleteEvent(const Date& date, const string& event);

	int DeleteDate(const Date& date);

	set<string> Find(const Date& date) const;

	void Print(ostream& outputStream) const;

private:
	map<Date, set<string>> storage;
};