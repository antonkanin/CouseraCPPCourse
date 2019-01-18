#pragma once

#include <string>
#include <memory>
#include "Date.h"

using namespace std;

class Date;
enum class Comparison;

enum class LogicalOperation
{
	Or, And
};

class Node
{
public:
	Node();
	~Node();

	void Evaluate(const Date& date, const string& event);
};

typedef shared_ptr<Node> NodePtr;

class EmptyNode : public Node
{

};

class DateComparisonNode : public Node
{
public:
	DateComparisonNode(const Comparison& comparison, const Date& date) 
		: comparison_(comparison), date_(date) {}

private:
	Comparison comparison_;
	Date date_;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(const LogicalOperation& operation, const NodePtr& lhs, const NodePtr& rhs)
		: operation_(operation), left_(lhs), right_(rhs) {}

private:
	LogicalOperation operation_;
	NodePtr left_;
	NodePtr right_;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(const Comparison& comparison, const string& event_name)
		: comparison_(comparison), event_name_(event_name) {}

private:
	Comparison comparison_;
	string event_name_;
};

