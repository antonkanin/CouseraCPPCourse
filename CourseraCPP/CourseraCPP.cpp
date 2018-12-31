//#include "pch.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

void RunProgram(istream& inputStream)
{
	int linesCount;
	inputStream >> linesCount;

	map<set<string>, int> busStops;

	vector<string> result;

	for (int lineIndex = 0; lineIndex < linesCount; ++lineIndex)
	{
		int stopsCount;
		inputStream >> stopsCount;

		set<string> stopsSet;

		for (int stopIndex = 0; stopIndex < stopsCount; stopIndex++)
		{
			string stop;
			inputStream >> stop;
			stopsSet.insert(stop);
		}

		if (busStops.count(stopsSet) == 0)
		{
			const int number = busStops.size() + 1;
			busStops[stopsSet] = number;
			result.push_back("New bus " + to_string(number));
		}
		else
		{
			result.push_back("Already exists for " + to_string(busStops[stopsSet]));
		}
	}

	for (const auto& value : result)
	{
		cout << value << endl;
	}
}

int main()
{
	//ifstream file("input.txt");
	//if (file.is_open())
	//{
	//	RunProgram(file);
	//	file.close();
	//}

	RunProgram(cin);
}

