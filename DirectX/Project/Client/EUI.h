#pragma once

#include "ImGui/imgui.h"

class EUI
{
private:
	const string	m_Name;
	bool			m_Active;

	ImVec2			m_AsChildSize; // �ڽ� UI Ÿ���ΰ��, �θ��� ������ ��ŭ �����ϴ��� ũ��

	EUI*			m_ParentUI;
	vector<EUI*>	m_vecChildUI;

public:
	GET(string, Name);

	GET_SET(ImVec2, AsChildSize);
	void AddChildUI(EUI* _ChildUI);


	bool IsActive() { return m_Active; }
	void SetActive(bool _Active)
	{
		m_Active = _Active;
	}



public:
	virtual void Tick();
	virtual void Render();

	virtual void Tick_UI() = 0;
	virtual void Render_UI() = 0;

public:
	EUI(const string& _Name);
	virtual ~EUI();
};

