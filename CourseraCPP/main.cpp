#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human
{
public:
	explicit Human(const string& name, const string& type) : name_(name), type_(type)
	{}
	virtual ~Human() = default;

	virtual void Walk(const string& destination) const
	{
		cout << Type() << ": " << Name() << " walks to: " << destination << endl;
	}

	string Name() const
	{
		return name_;
	}

	string Type() const
	{
		return type_;
	}

private:
	string name_;
	string type_;
};

class Student : public Human
{
public:
	Student(const string& name, const string& favourite_song) :
		Human(name, "Student"), favourite_song_(favourite_song)
	{}

	void Learn() const
	{
		cout << Type() << " " << Name() << " learns" << endl;
	}

	void Walk(const string& destination) const override
	{
		Human::Walk(destination);
		SingSong();
	}

	void SingSong() const
	{
		cout << Type() << ": " << Name() << " sings a song: " << favourite_song_ << endl;
	}

private:
	string favourite_song_;
};

class Teacher : public Human
{
public:
	Teacher(const string& name, const string& subject) : Human(name, "Teacher"), subject_(subject)
	{}

	void Teach() const
	{
		cout << "Teacher: " << Name() << " teaches: " << subject_ << endl;
	}

private:
	string subject_;
};

class Policeman : public Human
{
public:
	Policeman(const string& name) : Human(name, "Policeman")
	{}

	void Check(const Human& human) const
	{
		cout << "Policeman: " << Name() << " checks " << human.Type() << ". "
			<< human.Type() << "'s name is: " << human.Name() << endl;
	}
};

void VisitPlaces(const Human& human, const vector<string>& places)
{
	for (const auto& place : places)
	{
		human.Walk(place);
	}
}

int main()
{
	const Teacher t("Jim", "Math");
	const Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}