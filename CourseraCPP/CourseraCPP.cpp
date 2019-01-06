//#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main()
{
	int count;
	cin >> count;

	vector<long long> numbers;

	for (int i = 0; i < count; ++i)
	{
		long long temp;
		cin >> temp;
		numbers.push_back(temp);
	}

	long long average = 0;
	for (const auto& item : numbers)
	{
		average += item;
	}

	average = average / static_cast<long long>(numbers.size());

	const long long aboveAverageCount = count_if(begin(numbers), end(numbers), [average](long long value)
	{
		return value > average;
	});

	cout << aboveAverageCount << endl;

	for (size_t i = 0; i < numbers.size(); ++i)
	{
		if (numbers[i] > average)
		{
			cout << i << " ";
		}
	}
	
	return 0;
}
