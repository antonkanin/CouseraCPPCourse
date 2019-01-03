//#include "pch.h"

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <set>
#include <vector>

using namespace std;

struct Student
{
	string firstName;
	string lastName;
	int day;
	int month;
	int year;
};

void DoWork(istream& inputStream)
{
	int studentsCount;
	inputStream >> studentsCount;

	vector<Student> students;

	for (int i = 0; i < studentsCount; ++i)
	{
		Student student;
		inputStream >> student.firstName >> student.lastName >> student.day >> student.month >> student.year;

		const int MAX_VAL = 1000000000;
		if (student.day > MAX_VAL || student.month > MAX_VAL || student.year > MAX_VAL)
		{
			cout << "bad request" << endl;
		}
		else
		{
			students.push_back(student);
		}
	}

	int outputCount;
	inputStream >> outputCount;

	for (int i = 0; i < outputCount; ++i)
	{
		string operation;
		string studentPositionStr;
		inputStream >> operation >> studentPositionStr;

		int studentPosition = 0;

		try
		{
			studentPosition = stoi(studentPositionStr);
		}
		catch (std::invalid_argument)
		{
			cout << "bad request" << endl;
			continue;
		}
		

		if (studentPosition < 1 || studentPosition > students.size())
		{
			cout << "bad request" << endl;
			continue;
		}

		if (operation == "name")
		{
			cout << students[studentPosition - 1].firstName << " " << students[studentPosition - 1].lastName << endl;
		}
		else if (operation == "date")
		{
			cout << students[studentPosition - 1].day << "." << students[studentPosition - 1].month << "." << students[studentPosition - 1].year << endl;
		}
		else
		{
			cout << "bad request" << endl;
		}
	}
}

int main() 
{
	//ifstream file("input.txt");
	//DoWork(file);

	DoWork(cin);
}