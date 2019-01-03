//#include "pch.h"

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <set>

using namespace std;

int main() 
{
	ifstream file("input.txt");
	int height, width;
	file >> height >> width;
	file.ignore();

	string value;
	for (int row = 0; row < height; ++row)
	{
		for (int col = 0; col < width - 1; ++col)
		{
			getline(file, value, ',');
			int intValue = stoi(value);
			cout << setw(10) << intValue << ' ';
		}
		
		getline(file, value);
		int intValue = stoi(value);
		cout << setw(10) << intValue << endl;
	}
	
	return 0;
}