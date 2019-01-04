//#include "pch.h"
#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer()
{
	throw exception();
}

class TimeServer
{
public:
	string GetCurrentTime()
	{
		try
		{
			const string result = AskTimeServer();
			LastFetchedTime = result;
			return LastFetchedTime;
		}
		catch (system_error ex)
		{
			return LastFetchedTime;
		}
	}

private:
	string LastFetchedTime = "00:00:00";
};

int main()
{
	TimeServer ts;
	try
	{
		cout << ts.GetCurrentTime() << endl;
	}
	catch (exception& e)
	{
		cout << "Exception got: " << e.what() << endl;
	}
	return 0;
}
