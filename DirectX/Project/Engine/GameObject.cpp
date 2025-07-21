#include "pch.h"
#include "GameObject.h"

#include "LevelMgr.h"
#include "ALevel.h"
#include "Layer.h"

#include "KeyMgr.h"
#include "TimeMgr.h"


GameObject::GameObject()
	: m_LayerIdx(-1)
	, m_Parent(nullptr)
	, m_Dead(false)
{

}

GameObject::GameObject(const GameObject& _Origin)
	: Entity(_Origin)
	, m_arrCom{}
	, m_Parent(nullptr)
	, m_LayerIdx(-1)
	, m_Dead(false)
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == _Origin.m_arrCom[i])
			continue;

		AddComponent(_Origin.m_arrCom[i]->Clone());
	}

	for (size_t i = 0; i < _Origin.m_vecScripts.size(); ++i)
	{
		AddComponent(_Origin.m_vecScripts[i]->Clone());
	}

	for (size_t i = 0; _Origin.m_vecChild.size(); ++i)
	{
		AddChild(_Origin.m_vecChild[i]->Clone());
	}
}

GameObject::~GameObject()
{

}

void GameObject::Begin()
{
	for (size_t i = 0; i < m_vecScripts.size(); ++i)
	{
		if(nullptr != m_arrCom[i])
			m_arrCom[i]->Begin();
	}

	for (size_t i = 0; i < m_vecScripts.size(); ++i)
	{
		m_vecScripts[i]->Begin();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Begin();
	}
}

void GameObject::Tick()
{
	for (size_t i = 0; i < m_vecScripts.size(); ++i)
	{
		m_vecScripts[i]->Tick();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Tick();
	}
}

void GameObject::FinalTick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrCom[i])
			continue;

		m_arrCom[i]->FinalTick();
	}

	ALevel* pLevel = LevelMgr::GetInst()->GetCurrentLevel().Get();
	Layer* pLayer = pLevel->GetLayer(m_LayerIdx).Get();
	pLayer->RegisterObject(this);


	// 자식 오브젝트 FinalTick
	vector<Ptr<GameObject>>::iterator iter = m_vecChild.begin();
	for (; iter != m_vecChild.end();)
	{
		(*iter)->FinalTick();

		if ((*iter)->IsDead())
		{
			iter = m_vecChild.erase(iter);
		}
		else
		{
			++iter;			
		}
	}
}

void GameObject::Render()
{
	if(nullptr != m_RenderCom)
		m_RenderCom->Render();
}

void GameObject::AddComponent(Ptr<Component> _Com)
{
	COMPONENT_TYPE Type = _Com->GetType();

	if (Type == COMPONENT_TYPE::SCRIPT)
	{
		_Com->m_Owner = this;
		m_vecScripts.push_back((CScript*)_Com.Get());		
	}
	else
	{
		assert(nullptr == m_arrCom[(UINT)Type]);

		m_arrCom[(UINT)Type] = _Com;
		m_arrCom[(UINT)Type]->m_Owner = this;

		// 입력된 컴포넌트가 RenderComponent 종류라면
		CRenderComponent* pRenderCom = dynamic_cast<CRenderComponent*>(_Com.Get());
		if (pRenderCom)
		{
			// GameObject가 1개이상의 RenderComponent 를 가질 수 없다.
			assert(!m_RenderCom.Get());

			m_RenderCom = pRenderCom;
		}
	}
}

void GameObject::Destroy()
{
	DestroyObject(this);
}
