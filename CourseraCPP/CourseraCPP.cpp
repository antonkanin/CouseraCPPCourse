//#include "pch.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;

template<typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, const Key& key)
{
	if (m.count(key) == 0)
	{
		throw runtime_error("Key does not exist");
	}

	return m[key];
}

int main()
{
	map<int, string> m = { {0, "value"} };
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; 
	
	return 0;
}
