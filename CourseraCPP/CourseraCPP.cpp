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
	int count;
	inputStream >> count;

	// mas of bus routes, each route is a vector of stops
	map<string, vector<string>> busRoutes;

	// map of stops, each stop is a vector 
	map<string, vector<string>> busStops;

	map<string, string> capitals;
	vector<string> result;

	for (int i = 0; i < count; ++i)
	{
		string command;
		inputStream >> command;

		if (command == "NEW_BUS")
		{
			string bus;
			inputStream >> bus;
			
			int stopsCount;
			inputStream >> stopsCount;

			vector<string> stops;
			for (int stopIndex = 0; stopIndex < stopsCount; ++stopIndex)
			{
				string stopName;
				inputStream >> stopName;
				stops.push_back(stopName);

				// adding the bus route to the current stop
				busStops[stopName].push_back(bus);
			}

			busRoutes[bus] = stops;
		}

		else if (command == "BUSES_FOR_STOP")
		{
			string stop;
			inputStream >> stop;
			if (busStops.count(stop) == 0)
			{
				result.push_back("No stop");
			}
			else
			{
				string busesList;
				for (const auto& bus : busStops[stop])
				{
					busesList += bus + " ";
				}
				result.push_back(busesList);
			}
				
		}
		else if (command == "STOPS_FOR_BUS")
		{
			string busInput;
			inputStream >> busInput;
			if (busRoutes.count(busInput) == 0)
			{
				result.push_back("No bus");
			}
			else
			{
				// go through each Bus Stop for a given bus
				for (const auto& stop : busRoutes[busInput])
				{
					// if this stop has more then 1 buses
					if (busStops[stop].size() > 1)
					{
						string resultLine = "Stop " + stop + ": ";
						for (const auto& bus : busStops[stop])
						{
							if (bus != busInput)
							{
								resultLine += bus + " ";
							}
						}
						result.push_back(resultLine);
					}
					else
					{
						result.push_back("Stop " + stop + ": no interchange");
					}
				}
			}
		}

		else if (command == "ALL_BUSES")
		{
			//sort(busRoutes.begin(), busRoutes.end(), 
			//	[](const string& a, const string& b) -> bool
			//{
			//	return a > b;
			//});

			if (busRoutes.size() == 0)
			{
				result.push_back("No buses");
			}
			else
			{
				for (const auto& route : busRoutes)
				{
					string resultLine = "Bus " + route.first + ": ";
					for (const auto& stop : route.second)
					{
						resultLine += stop + " ";
					}
					result.push_back(resultLine);
				}

			}
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

