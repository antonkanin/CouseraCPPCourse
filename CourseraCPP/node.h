#pragma once

#include <string>

enum class Comparison;

using namespace std;

class Date;

class Node
{
public:
	Node(Comparison comparison, );
	~Node();

	void Evaluate(const Date& date, const string& event);
};

class EmptyNode : public Node
{
	
};

class DateComparisonNode : public Node
{
	
};

class LogicalOperatorNode : public Node
{
	
};

class EventComparisonNode : public Node
{ 

};

