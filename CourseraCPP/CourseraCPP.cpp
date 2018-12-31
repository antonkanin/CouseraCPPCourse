#include "pch.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

void RunProgram(istream& inputStream)
{
	int linesCount;
	inputStream >> linesCount;

	// mas of bus routes, each route is a vector of stops
	map<vector<string>, int> busRoutes;

	vector<string> result;

	for (int lineIndex = 0; lineIndex < linesCount; ++lineIndex)
	{
		int numberOfStops;
		inputStream >> numberOfStops;

		vector<string> route;

		for (int stopIndex = 0; stopIndex < numberOfStops; stopIndex++)
		{
			string stopName;
			inputStream >> stopName;

			route.push_back(stopName);
		}

		if (busRoutes.count(route) == 0)
		{
			const int newSize = busRoutes.size() + 1;
			busRoutes[route] = newSize;
			result.push_back("New bus " + to_string(newSize));
		}
		else
		{
			result.push_back("Already exists for " + to_string(busRoutes[route]));
		}
	}

	for (const auto& value : result)
	{
		cout << value << endl;
	}
}

int main()
{
	/*ifstream file("input.txt");
	if (file.is_open())
	{
		RunProgram(file);
		file.close();
	}*/

	//RunProgram(cin);
	map<int, string> m = { {1, "odd"}, {2, "even"}, {1, "one"} };
	m[2] = "two";
	m.erase(1);
	m[3] = "three";
	m.erase(4);
	m[5] = "five";
	cout << m.size();

}

