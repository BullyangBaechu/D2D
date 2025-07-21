#include "pch.h"
#include "Layer.h"

Layer::Layer(int _Idx)
	: m_LayerIdx(_Idx)
{
}

Layer::Layer(const Layer& _Origin)
	: Entity(_Origin)
	, m_LayerIdx(_Origin.m_LayerIdx)
{
	for (size_t i = 0; i < _Origin.m_vecParents.size(); ++i)
	{
		AddObject(_Origin.m_vecParents[i]->Clone(), false);
	}
}

Layer::~Layer()
{
}

void Layer::AddObject(GameObject* _Object, bool _MoveWithChild)
{
	m_vecParents.push_back(_Object);

	static list<GameObject*> queue;
	queue.clear();
	queue.push_back(_Object);

	// Level ¼øÈ¸
	while (!queue.empty())
	{
		GameObject* pObject = queue.front();
		queue.pop_front();

		if (_MoveWithChild || pObject->m_LayerIdx == -1)
		{
			pObject->m_LayerIdx = m_LayerIdx;
		}

		for (size_t i = 0; i < pObject->m_vecChild.size(); ++i)
		{
			queue.push_back(pObject->m_vecChild[i].Get());
		}
	}
}

void Layer::Begin()
{
	for (size_t i = 0; i < m_vecParents.size(); ++i)
	{
		m_vecParents[i]->Begin();
	}
}

void Layer::Tick()
{
	for (size_t i = 0; i < m_vecParents.size(); ++i)
	{
		m_vecParents[i]->Tick();
	}
}

void Layer::FinalTick()
{
	vector<Ptr<GameObject>>::iterator iter = m_vecParents.begin();
	for (; iter != m_vecParents.end();)
	{
		(*iter)->FinalTick();

		if ((*iter)->IsDead())
		{
			iter = m_vecParents.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}