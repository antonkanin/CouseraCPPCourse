//#include "pch.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m)
{
	set<string> result;
	for (const auto& item : m)
	{
		result.insert(item.second);
	}
	return result;
}

//void RunProgram(istream& inputStream)
//{
//	int linesCount;
//	inputStream >> linesCount;
//
//	set<string> stringsSet;
//
//	vector<string> result;
//
//	for (int lineIndex = 0; lineIndex < linesCount; ++lineIndex)
//	{
//		string s;
//		inputStream >> s;
//		stringsSet.insert(s);
//	}
//
//	cout << stringsSet.size();
//
//	//for (const auto& value : result)
//	//{
//	//	cout << value << endl;
//	//}
//}

//int main()
//{
//	/*ifstream file("input.txt");
//	if (file.is_open())
//	{
//		RunProgram(file);
//		file.close();
//	}*/
//
//	RunProgram(cin);
//}

