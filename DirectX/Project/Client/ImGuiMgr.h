#pragma once


class EUI;

class ImGuiMgr
	: public singleton<ImGuiMgr>
{
	SINGLE(ImGuiMgr);
private:
	map<string, EUI*>	m_mapUI;		// 최상위 부모 UI
	bool				m_ShowDemo;

public:
	void Init();
	void Progress();

private:
	void Tick();
	void Render();
	void CreateEditorUI();
};

