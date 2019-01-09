//#pragma once
//#include "pch.h"
#include <sstream>
#include <string>
#include <algorithm>
#include "phone_number.h"

using namespace std;

//class PhoneNumber
//{
//public:
//	explicit PhoneNumber(const string& international_number);
//
//	string GetCountryCode() const;
//	string GetCityCode() const;
//	string GetLocalNumber() const;
//	string GetInternationalNumber() const;
//
//private:
//	string country_code_;
//	string city_code_;
//	string local_number_;
//};
//
PhoneNumber::PhoneNumber(const string& international_number)
{
	if (international_number.empty())
	{
		throw invalid_argument("Number cannot be empty");
	}

	if (international_number[0] != '+')
	{
		throw invalid_argument("Number must start with +");
	}

	string num = international_number.substr(1);

	// checking for the '-' sign between the country code and a full number
	const auto minusPos = find(begin(num), end(num), '-');
	if (minusPos == begin(num))
	{
		throw invalid_argument("Country code cannot be empty");
	}

	if (minusPos == end(num))
	{
		throw invalid_argument("County code must follow '-'");
	}

	country_code_.assign(begin(num), minusPos);
	stoi(country_code_);
	   
	const auto secondMinus = find(std::next(minusPos), end(num), '-');
	if (secondMinus == end(num))
	{
		throw invalid_argument("");
	}

	city_code_.assign(std::next(minusPos), secondMinus);
	stoi(city_code_);

	local_number_.assign(std::next(secondMinus), end(num));
}

string PhoneNumber::GetCountryCode() const
{
	return country_code_;
}

string PhoneNumber::GetCityCode() const
{
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const
{
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const
{
	stringstream result;
	result << "+" << country_code_ << "-" << city_code_ << "-" << local_number_;
	return result.str();
}

//int main()
//{
//	return 0;
//}