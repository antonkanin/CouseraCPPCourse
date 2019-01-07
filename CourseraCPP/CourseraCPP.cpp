#include "pch.h"
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
	map<string, vector<string>> stops_for_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r)
{
	if (r.stops_for_buses.empty())
	{
		cout << "No bus";
	}
	else
	{
		for (const auto& stop : r.stops_for_buses)
		{
			os << "Stop " << stop.first << ": ";
			if (stop.second.empty())
			{
				os << "no interchange";
			}
			else
			{
				for (const auto& bus : stop.second)
				{
					os << bus << " ";
				}
			}
			os << endl;
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
		for (const auto& bus : r.buses_to_stops)
		{
			os << "Bus " << bus.first << ":";
			for (const auto& stop : r.buses_to_stops.at(bus.first))
			{
				os << " " << stop;
			}
			os << endl;
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
		map<string, vector<string>> result;

		// if there are no records for this bus return empty map
		if (buses_to_stops.count(bus) == 0)
		{
			return {};
		}

		// iterate through each stop for this bus
		for (auto& stop : buses_to_stops.at(bus))
		{
			// if there is just one bus for a given stop its our input bus and we can skip it
			if (stops_to_buses.at(stop).size() == 1)
			{
				result[stop] = {};
			}
			else
			{
				for (const auto& other_bus : stops_to_buses.at(stop))
				{
					if (bus != other_bus)
					{
						result[stop].push_back(other_bus);
					}
				}
			}
		}

		return { result };
	}

	AllBusesResponse GetAllBuses() const
	{
		return { buses_to_stops };
	}

private:
	map<string, vector<string>> buses_to_stops;
	unordered_map<string, vector<string>> stops_to_buses;
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
