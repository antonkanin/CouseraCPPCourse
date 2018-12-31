//#include "pch.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

void processCapitals(istream& inputStream)
{
	int count;
	inputStream >> count;
	map<string, string> capitals;
	vector<string> result;

	for (int i = 0; i < count; ++i)
	{
		string command;
		inputStream >> command;

		if (command == "CHANGE_CAPITAL")
		{
			string country, newCapital;
			inputStream >> country >> newCapital;

			if (capitals.count(country) == 0)
			{
				result.push_back("Introduce new country " + country + " with capital " + newCapital);
			}
			else if (capitals[country] == newCapital)
			{
				result.push_back("Country " + country + " hasn't changed its capital");
			}
			else
			{
				result.push_back("Country " + country + " has changed its capital from " + capitals[country] +
					" to " + newCapital);
			}

			capitals[country] = newCapital;
		}

		else if (command == "RENAME")
		{
			string oldCountry, newCountry;
			inputStream >> oldCountry >> newCountry;

			if (oldCountry == newCountry || capitals.count(oldCountry) == 0 || capitals.count(newCountry) > 0)
			{
				result.push_back("Incorrect rename, skip");
			}
			else
			{
				result.push_back("Country " + oldCountry + " with capital " + capitals[oldCountry] +
					" has been renamed to " + newCountry);
				capitals[newCountry] = capitals[oldCountry];
				capitals.erase(oldCountry);
			}
		}
		else if (command == "ABOUT")
		{
			string country;
			inputStream >> country;

			if (capitals.count(country) == 0)
			{
				result.push_back("Country " + country + " doesn't exist");
			}
			else
			{
				result.push_back("Country " + country + " has capital " + capitals[country]);
			}
		}
		else if (command == "DUMP")
		{
			if (capitals.size() == 0)
			{
				result.push_back("There are no countries in the world");
			}
			else
			{
				string countriesList;
				for (const auto& country : capitals)
				{
					countriesList += country.first + "/" + country.second + " ";
				}
				result.push_back(countriesList);
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
	//	processCapitals(file);
	//	file.close();
	//}

	processCapitals(cin);
}

