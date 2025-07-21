#pragma once
// 에디터 용 UI
#include "ImGui/imgui.h"

class EUI
{
private:
	const string	m_Name;
	bool			m_Active;

	ImVec2			m_AsChildSize; // 자식 UI 타입인경우, 부모의 영역을 얼만큼 차지하는지 크기

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

	// 자식 UI들이 무조건 오버라이딩해서 직접 고유성을 갖게 하기 위해 순수 가상 함수로 tick, render를 만들기
	virtual void Tick_UI() = 0;
	virtual void Render_UI() = 0;

public:
	EUI(const string& _Name);
	virtual ~EUI();
};

