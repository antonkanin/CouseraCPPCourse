//#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

bool IsHigherPriority(const char& prev, const char& next)
{
	return (next == '*' || next == '/') && (prev == '+' || prev == '-');
}

int main()
{
	string originalNumber;
	cin >> originalNumber;

	int operationsCount;
	cin >> operationsCount;

	queue<pair<char, string>> operations;
	char prev_operation;
	char operation = ' ';
	int bracketsCounter = 0;

	while (operationsCount > 0)
	{
		prev_operation = operation;
		string number;
		cin >> operation >> number;
		operations.push({ operation, number });
		if (IsHigherPriority(prev_operation, operation))
		{
			++bracketsCounter;
		}

		--operationsCount;
	}

	for (int i = 0; i < bracketsCounter; ++i)
	{
		cout << "(";
	}

	cout << originalNumber;

	operation = ' ';
	while (!operations.empty())
	{
		prev_operation = operation;
		auto& op = operations.front();
		operation = op.first;
		if (IsHigherPriority(prev_operation, operation))
		{
			cout << ")";
		}
		cout << " " << operation << " " << op.second;
		operations.pop();
	}

	return 0;
}
