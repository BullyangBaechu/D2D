#include "pch.h"
#include "EUI.h"



EUI::EUI(const string& _Name)
	: m_Name(_Name)
	, m_Active(true)
	, m_ParentUI(nullptr)
{
}

EUI::~EUI()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		delete m_vecChildUI[i];
	}
}


void EUI::Tick()
{
	Tick_UI();

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Tick();
	}
}

void EUI::Render()
{
	// 최상위 부모 UI
	if (nullptr == m_ParentUI)
	{
		ImGui::Begin(m_Name.c_str(), &m_Active);

		Render_UI();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			if (m_vecChildUI[i]->IsActive())
			{
				m_vecChildUI[i]->Render();
			}
		}

		ImGui::End();
	}

	// 자식 UI 라면
	else
	{
		ImGui::BeginChild(m_Name.c_str(), m_AsChildSize);

		Render_UI();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			if (m_vecChildUI[i]->IsActive())
			{
				m_vecChildUI[i]->Render();
			}
		}

		ImGui::EndChild();
	}
}

void EUI::AddChildUI(EUI* _ChildUI)
{
	_ChildUI->m_ParentUI = this;
	m_vecChildUI.push_back(_ChildUI);
}