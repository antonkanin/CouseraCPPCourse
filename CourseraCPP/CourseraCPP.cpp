//#include "pch.h"
#include <algorithm>
#include <map>
#include <vector>
#include <ostream>
#include <iostream>
#include <string>

using namespace std;

//struct Image {
//	double quality;
//	double freshness;
//	double rating;
//};
//
//struct Params {
//	double a;
//	double b;
//	double c;
//};

struct FunctionParts
{
	char operation;
	double value;
};

class Function
{
public:
	void AddPart(char new_operator, double value)
	{
		parts.push_back({ new_operator, value });
	}

	void Invert()
	{
		for (auto& part : parts)
		{
			switch (part.operation)
			{
			case '+':
				part.operation = '-';
				break;
			case '-':
				part.operation = '+';
				break;
			case '*':
				part.operation = '/';
				break;
			case '/':
				part.operation = '*';
				break;
			default:
				cout << "Case not supported" << endl;
				break;
			}
		}

		reverse(begin(parts), end(parts));
	}

	double Apply(double source_value) const
	{
		for (const auto& part : parts)
		{
			if (part.operation == '+')
			{
				source_value += part.value;
			}
			else if (part.operation == '-')
			{
				source_value -= part.value;
			} 
			else if (part.operation == '*')
			{
				source_value *= part.value;
			}
			else if (part.operation == '/')
			{
				source_value /= part.value;
			}
		}

		return  source_value;
	}

private:
	vector<FunctionParts> parts;
};

Function MakeWeightFunction(const Params& params,
	const Image& image) {
	Function function;
	function.AddPart('*', params.a);
	function.AddPart('-', image.freshness * params.b);
	function.AddPart('+', image.rating * params.c);
	return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
	Function function = MakeWeightFunction(params, image);
	return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
	const Image& image,
	double weight) {
	Function function = MakeWeightFunction(params, image);
	function.Invert();
	return function.Apply(weight);
}

int main() {
	Image image = { 10, 2, 6 };
	Params params = { 4, 2, 6 };
	cout << ComputeImageWeight(params, image) << endl;
	cout << ComputeQualityByWeight(params, image, 52) << endl;
	return 0;
}
