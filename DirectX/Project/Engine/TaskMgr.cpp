#include "pch.h"
#include "TaskMgr.h"

#include "LevelMgr.h"
#include "ALevel.h"

TaskMgr::TaskMgr()
{}

TaskMgr::~TaskMgr()
{}

void TaskMgr::Tick()
{
	// 삭제 예정상태 오브젝트를 실제로 삭제한다.
	m_vecGarbage.clear();

	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			GameObject* Object = (GameObject*)m_vecTask[i].Param_0;
			UINT LayerIdx = m_vecTask[i].Param_1;

			Ptr<ALevel> pLevel = LevelMgr::GetInst()->GetCurrentLevel();
			pLevel->AddObject(LayerIdx, Object, false);
		}
			break;
		case TASK_TYPE::DELETE_OBJECT:
		{
			GameObject* Object = (GameObject*)m_vecTask[i].Param_0;

			if (false == Object->m_Dead)
			{
				Object->m_Dead = true;
				m_vecGarbage.push_back(Object);
			}
		}
			break;
		case TASK_TYPE::CHANGE_LEVEL:

			break;
		case TASK_TYPE::CHANGE_LEVEL_STATE:

			break;
		}
	}

	m_vecTask.clear();
}