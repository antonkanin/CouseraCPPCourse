//#include "pch.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

//enum class TaskStatus
//{
//	NEW,
//	IN_PROGRESS,
//	TESTING,
//	DONE
//};
//
//using TasksInfo = map<TaskStatus, int>;

TaskStatus GetNextStatus(const TaskStatus& status)
{
	switch (status)
	{
		case TaskStatus::NEW:
			return TaskStatus::IN_PROGRESS;
			break;
		case TaskStatus::IN_PROGRESS:
			return TaskStatus::TESTING;
			break;
		case TaskStatus::TESTING:
			return TaskStatus::DONE;
			break;
		default:
			return status;
	}
}

class TeamTasks
{
public:
	const TasksInfo& GetPersonTasksInfo(const string& person) const
	{
		return personsTasks.at(person);
	}

	void AddNewTask(const string& person)
	{
		if (person.empty())
		{
			return;
		}

		personsTasks[person][TaskStatus::NEW]++;
	}

	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const string& person, int task_count)
	{
		if (personsTasks.count(person) == 0)
		{
			return { {}, {} };
		}

		TasksInfo allTasks = personsTasks.at(person);
		TasksInfo updatedTasks;
		TasksInfo oldTasks;

		for (const auto& status : personsTasks.at(person))
		{
			if (status.first == TaskStatus::DONE)
			{
				break;
			}

			if (task_count > status.second)
			{
				allTasks[status.first] -= status.second;
				allTasks[GetNextStatus(status.first)] += status.second;

				updatedTasks[GetNextStatus(status.first)] += status.second;

				task_count -= status.second;
			}
			else
			{
				allTasks[status.first] -= task_count;
				allTasks[GetNextStatus(status.first)] += task_count;

				updatedTasks[GetNextStatus(status.first)] += task_count;

				if (task_count < status.second)
				{
					oldTasks[status.first] = status.second - task_count;
				}

				auto remainingStatus = GetNextStatus(status.first);

				while (remainingStatus != TaskStatus::DONE && personsTasks.at(person).count(remainingStatus) > 0)
				{
					oldTasks[remainingStatus] = personsTasks.at(person).at(remainingStatus);
					remainingStatus = GetNextStatus(remainingStatus);
				}

				break;
			}
		}

		personsTasks[person] = allTasks;

		return make_tuple(updatedTasks, oldTasks);
	}

private:
	map<string, TasksInfo> personsTasks;
};

void PrintTasksInfo(TasksInfo tasks_info)
{
	//cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
	//	", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
	//	", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
	//	", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;

	cout << tasks_info[TaskStatus::NEW] << " " <<
	tasks_info[TaskStatus::IN_PROGRESS] << " " <<
	tasks_info[TaskStatus::TESTING] << " " <<
	tasks_info[TaskStatus::DONE] << endl;
}

int main()
{
	TeamTasks tasks;

	for (int i = 0; i < 3; ++i)
	{
		tasks.AddNewTask("Ivan");
	}

	TasksInfo updated_tasks, untouched_tasks;

	for (int i = 0; i < 10; i++)
	{
		tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);

		PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
		PrintTasksInfo(updated_tasks);
		PrintTasksInfo(untouched_tasks);

		cout << endl;
	}

	return 0;
}
