#pragma once

#include <string>
#include <memory>
#include "date.h"
#include "comparison.h"

using namespace std;

enum class LogicalOperation
{
	Or, And
};

class Node
{
public:
	virtual bool Evaluate(const Date& date, const string& event) = 0;
};

typedef shared_ptr<Node> NodePtr;

class EmptyNode : public Node
{
public:
	bool Evaluate(const Date& date, const string& event) override;
};

class DateComparisonNode : public Node
{
public:
	DateComparisonNode(const Comparison& comparison, const Date& date) 
		: comparison_(comparison), date_(date) {}

	bool Evaluate(const Date& date, const string& event) override;

private:
	Comparison comparison_;
	Date date_;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(const LogicalOperation& operation, const NodePtr& lhs, const NodePtr& rhs)
		: operation_(operation), left_(lhs), right_(rhs) {}

	bool Evaluate(const Date& date, const string& event) override;

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

	bool Evaluate(const Date& date, const string& event) override;

private:
	Comparison comparison_;
	string event_name_;
};

