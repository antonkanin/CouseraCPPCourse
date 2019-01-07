//#include "pch.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <unordered_map>

using namespace std;

enum class QueryType
{
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query
{
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;
};

istream& operator >> (istream& is, Query& q)
{
	string command;
	is >> command;

	if (command == "NEW_BUS")
	{
		q.type = QueryType::NewBus;
		is >> q.bus;

		int stop_count;
		is >> stop_count;

		q.stops.resize(0);

		while (stop_count > 0)
		{
			string stop_name;
			is >> stop_name;
			q.stops.push_back(stop_name);
			stop_count--;
		}
	}
	else if (command == "BUSES_FOR_STOP")
	{
		q.type = QueryType::BusesForStop;
		string stop;
		is >> q.stop;
	}
	else if (command == "STOPS_FOR_BUS")
	{
		q.type = QueryType::StopsForBus;
		string bus;
		is >> q.bus;
	}
	else if (command == "ALL_BUSES")
	{
		q.type = QueryType::AllBuses;
	}

	return is;
}

struct BusesForStopResponse
{
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r)
{
	if (r.buses.empty())
	{
		cout << "No stop";
	}
	else
	{
		for (const auto& bus : r.buses)
		{
			os << bus << " ";
		}
	}

	return os;
};

struct StopsForBusResponse
{
	vector<string> stops;
	vector<vector<string>> buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r)
{
	if (r.stops.empty())
	{
		cout << "No bus";
	}
	else
	{
		size_t counter = 0;
		for (size_t index = 0; index < r.stops.size(); ++index)
		// for (const auto& stop : r.stops_for_buses)
		{
			os << "Stop " << r.stops[index] << ": ";
			if (r.buses[index].empty())
			{
				os << "no interchange";
			}
			else
			{
				for (const auto& bus : r.buses[index])
				{
					os << bus << " ";
				}
			}

			if (counter < r.stops.size() - 1)
			{
				os << endl;
			}

			counter++;
		}
	}
	return os;
}

struct AllBusesResponse
{
	map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r)
{
	if (r.buses_to_stops.size() == 0)
	{
		os << "No buses";
	}
	else
	{
		size_t counter = 0;
		for (const auto& bus : r.buses_to_stops)
		{
			os << "Bus " << bus.first << ":";
			for (const auto& stop : r.buses_to_stops.at(bus.first))
			{
				os << " " << stop;
			}

			if (counter < r.buses_to_stops.size() - 1)
			{
				os << endl;
			}

			++counter;
		}
	}
	return os;
};

class BusManager
{
public:
	void AddBus(const string& bus, const vector<string>& stops)
	{
		if (buses_to_stops.count(bus) > 0)
		{
			return;
		}

		for (const auto& stop : stops)
		{
			buses_to_stops[bus].push_back(stop);
			stops_to_buses[stop].push_back(bus);
		}
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const
	{
		if (stops_to_buses.count(stop) == 0)
		{
			return {};
		}

		return { stops_to_buses.at(stop) };
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const
	{
		vector<string> stops;
		vector<vector<string>> buses;

		// if there are no records for this bus return empty map
		if (buses_to_stops.count(bus) == 0)
		{
			return {{}, {}};
		}

		// iterate through each stop for this bus
		for (const auto& stop : buses_to_stops.at(bus))
		{
			stops.push_back(stop);

			// if there is just one bus for a given stop its our input bus and we can skip it
			if (stops_to_buses.at(stop).size() == 1)
			{
				buses.push_back({});
			}
			else
			{
				buses.push_back({});
				for (const auto& other_bus : stops_to_buses.at(stop))
				{
					if (bus != other_bus)
					{
						buses[buses.size() - 1].push_back(other_bus);
					}
				}
			}
		}

		return { stops, buses };
	}

	AllBusesResponse GetAllBuses() const
	{
		return { buses_to_stops };
	}

private:
	map<string, vector<string>> buses_to_stops;
	map<string, vector<string>> stops_to_buses;
};

void DoWork(istream& inStream)
{
	int query_count;
	Query q;

	inStream >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i)
	{
		inStream >> q;
		switch (q.type)
		{
			case QueryType::NewBus:
				bm.AddBus(q.bus, q.stops);
				break;
			case QueryType::BusesForStop:
				cout << bm.GetBusesForStop(q.stop) << endl;
				break;
			case QueryType::StopsForBus:
				cout << bm.GetStopsForBus(q.bus) << endl;
				break;
			case QueryType::AllBuses:
				cout << bm.GetAllBuses() << endl;
				break;
		}
	}
}

int main()
{
	ifstream input("input.txt");
	DoWork(input);

	return 0;
}
