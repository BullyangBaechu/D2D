#pragma once



class Engine
	: public singleton<Engine>
{
	SINGLE(Engine);
private:
	HWND	m_hMainWnd;
	Vec2	m_Resolution;


public:
	void ChangeWindowResolution(UINT _Width, UINT _Height);
	HWND GetMainWnd() { return m_hMainWnd; }

public:
	int Init(HWND _MainWnd, UINT _Width, UINT _Height);
	void Progress();
};

