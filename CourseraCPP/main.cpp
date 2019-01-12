//#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <memory>

using namespace std;

class Figure
{
public:
	virtual ~Figure() = default;

	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
};

class Triangle : public Figure
{
public:
	Triangle(float a, float b, float c) : a(a), b(b), c(c)
	{}

	string Name() const override
	{
		return "TRIANGLE";
	}

	double Perimeter() const override
	{
		return a + b + c;
	}

	double Area() const override
	{
		double p = (a + b + c) / 2;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}

private:
	double a, b, c;
};

class Rect : public Figure
{
public:
	Rect(const float& a, const float& b) : a(a), b(b) {}

	string Name() const override
	{
		return "RECT";
	}

	double Perimeter() const override 
	{
		return 2 * (a + b);
	}

	double Area() const override
	{
		return a * b;
	}

private:
	float a, b;
};

class Circle : public Figure
{
public:
	Circle(double r) : r(r) {}

	string Name() const override
	{
		return "CIRCLE";
	}

	double Perimeter() const override
	{
		return 2 * PI * r;
	}

	double Area() const override
	{
		return PI * r * r;
	}

private:
	float r;

	const double PI = 3.14;
};

shared_ptr<Figure> CreateFigure(istream& inputStream)
{
	string type;
	inputStream >> type;

	if (type == "RECT")
	{
		float a, b;
		inputStream >> a >> b;
		return make_shared<Rect>(a, b);
	} 
	
	if (type == "TRIANGLE")
	{
		float a, b, c;
		inputStream >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	}

	if (type == "CIRCLE")
	{
		float r;
		inputStream >> r;
		return make_shared<Circle>(r);
	}
}

int main()
{
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); )
	{
		istringstream is(line);

		string command;
		is >> command;

		if (command == "ADD")
		{
			figures.push_back(CreateFigure(is));
		}

		else if (command == "PRINT")
		{
			for (const auto& current_figure : figures)
			{
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}
	return 0;
}