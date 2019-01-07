//#include "pch.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

template<typename T> T Sqr(T value);
template<typename T> vector<T> Sqr(vector<T> value);
template<typename T1, typename T2> pair<T1, T2> Sqr(pair<T1, T2> p);
template<typename Key, typename Value> map<Key, Value> Sqr(map<Key, Value> m);

template<typename T>
T Sqr(T value)
{
	return value * value;
}

template<typename T>
vector<T> Sqr(vector<T> value)
{
	for (auto& item : value)
	{
		item = Sqr(item);
	}
	return value;
}

template<typename T1, typename T2>
pair<T1, T2> Sqr(pair<T1, T2> p)
{
	return { Sqr(p.first), Sqr(p.second) };
}

template<typename Key, typename Value> 
map<Key, Value> Sqr(map<Key, Value> m)
{
	for (auto& item : m)
	{
		item.second = Sqr(item.second);
	}
	return m;
}

int main()
{
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v))
	{
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};

	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs))
	{
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}

	return 0;
}
