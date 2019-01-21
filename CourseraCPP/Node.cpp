#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event)
{
	return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event)
{
	switch (comparison_)
	{
	case Comparison::Less:
		return date < date_;

	case Comparison::LessOrEqual:
		return date <= date_;

	case Comparison::Greater:
		return date > date_;

	case Comparison::GreaterOrEqual:
		return date >= date_;

	case Comparison::Equal:
		return date == date_;

	case Comparison::NotEqual:
		return date != date_;
	}

	return false;
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event)
{
	if (operation_ == LogicalOperation::And)
	{
		return left_->Evaluate(date, event) && right_->Evaluate(date, event);
	}

	return left_->Evaluate(date, event) || right_->Evaluate(date, event);
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event)
{
	switch (comparison_)
	{
	case Comparison::Less:
		return event < event_name_;

	case Comparison::LessOrEqual:
		return event <= event_name_;

	case Comparison::Greater:
		return event > event_name_;

	case Comparison::GreaterOrEqual:
		return event >= event_name_;

	case Comparison::Equal:
		return event == event_name_;;

	case Comparison::NotEqual:
		return event != event_name_;
	}

	return false;
}
