#include "pch.h"
#include "ALevel.h"


ALevel::ALevel()
	: Asset(ASSET_TYPE::LEVEL)
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i] = new Layer(i);
	}
}

// ���� '������'
ALevel::ALevel(const ALevel& _Origin)
	: Asset(_Origin)
	, m_Layer{}
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i] = _Origin.m_Layer[i]->Clone();
	}
}

ALevel::~ALevel()
{
}

void ALevel::Begin()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Begin();
	}
}

void ALevel::Tick()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->Tick();
	}
}

void ALevel::FinalTick()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->FinalTick();
	}
}

void ALevel::AddObject(int _LayerIdx, GameObject* _Object, bool _MoveWithChild)
{
	m_Layer[_LayerIdx]->AddObject(_Object, _MoveWithChild);
}


void ALevel::Deregister()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_Layer[i]->m_vecObjects.clear();
	}
}

GameObject* ALevel::FindObjectByName(const wstring& _Name)
{
	// �̸� �˻��� ���� ���� Ž��
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		// ���� ������ ���� const & (�б� ����)
		const vector<Ptr<GameObject>>& vecObjects = m_Layer[i]->GetObjects();

		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			if (_Name == vecObjects[j]->GetName())
				return vecObjects[j].Get();
		}
	}

	return nullptr;
}
