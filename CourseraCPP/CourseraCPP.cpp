//#include "pch.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//enum class Lang
//{
//	DE, FR, IT
//};
//
//struct Region
//{
//	string std_name;
//	string parent_std_name;
//	map<Lang, string> names;
//	int64_t population;
//};

bool operator<(const Region& lhs, const Region& rhs)
{
	return 	tie(lhs.parent_std_name, lhs.std_name, lhs.names, lhs.population) <
		tie(rhs.parent_std_name, rhs.std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions)
{
	using pair_type = map<Region, int>::value_type;

	map<Region, int> regionsCount;
	for (const auto& region : regions)
	{
		regionsCount[region]++;
	}

	const auto it = max_element(begin(regionsCount), end(regionsCount), [](pair_type a, pair_type b)
	{
		return a.second < b.second;
	});

	if (it != end(regionsCount))
	{
		return it->second;
	}
	else
	{
		return 0;
	}
}


int main()
{
	cout << FindMaxRepetitionCount({
	  {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Moscow",
		  "Russia",
		  {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
		  89
	  }, {
		  "Russia",
		  "Eurasia",
		  {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
		  89
	  },
		}) << endl;

	cout << FindMaxRepetitionCount({
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Russia",
			"Eurasia",
			{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Toulouse",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			31
		},
		}) << endl;

	return 0;
}
