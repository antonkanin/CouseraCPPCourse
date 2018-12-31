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

	set<set<string>> dictionary;

	map<string, int> synonymCounter;

	vector<string> result;

	for (int lineIndex = 0; lineIndex < linesCount; ++lineIndex)
	{
		string command;
		inputStream >> command;

		if (command == "ADD")
		{
			string word1, word2;
			inputStream >> word1 >> word2;

			if (dictionary.count({ word1, word2 }) == 0)
			{
				synonymCounter[word1]++;
				synonymCounter[word2]++;
				dictionary.insert({ word1, word2 });
			}
			
		}

		else if (command == "COUNT")
		{
			string word;
			inputStream >> word;

			if (synonymCounter.count(word) > 0)
			{
				result.push_back(to_string(synonymCounter[word]));
			}
			else
			{
				result.push_back("0");
			}
		}

		else if (command == "CHECK")
		{
			string word1, word2;
			inputStream >> word1 >> word2;

			if (dictionary.count({word1, word2}) > 0)
			{
				result.push_back("YES");
			}
			else
			{
				result.push_back("NO");
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

