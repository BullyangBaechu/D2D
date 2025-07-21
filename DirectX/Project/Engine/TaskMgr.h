#pragma once

#include "GameObject.h"

class TaskMgr
	: public singleton<TaskMgr>
{
	SINGLE(TaskMgr);
private:
	vector<tTaskInfo>		m_vecTask;
	vector<Ptr<GameObject>> m_vecGarbage;

public:
	void AddTask(const tTaskInfo& _Task) { m_vecTask.push_back(_Task); }

public:
	void Tick();
};

