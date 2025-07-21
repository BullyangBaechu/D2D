#include "pch.h"
#include "Engine.h"

#include "Device.h"
#include "PathMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "AssetMgr.h"
#include "LevelMgr.h"
#include "RenderMgr.h"
#include "CollisionMgr.h"
#include "TaskMgr.h"

Engine::Engine()
	: m_hMainWnd(nullptr)
{

}

Engine::~Engine()
{

}

int Engine::Init(HWND _MainWnd, UINT _Width, UINT _Height)
{
	assert(m_hMainWnd = _MainWnd);

	ChangeWindowResolution(_Width, _Height);

	if (FAILED(Device::GetInst()->Init(_MainWnd, m_Resolution)))
	{		
		return E_FAIL;
	}
	
	// Manager 초기화
	PathMgr::GetInst()->Init();
	KeyMgr::GetInst()->Init();
	TimeMgr::GetInst()->Init();
	AssetMgr::GetInst()->Init();
	RenderMgr::GetInst()->Init();
	LevelMgr::GetInst()->Init();


	return S_OK;
}

void Engine::Progress()
{
	TimeMgr::GetInst()->Tick();
	KeyMgr::GetInst()->Tick();

	LevelMgr::GetInst()->Progress();
	CollisionMgr::GetInst()->Tick();

	RenderMgr::GetInst()->Progress();

	TaskMgr::GetInst()->Tick();
}

void Engine::ChangeWindowResolution(UINT _Width, UINT _Height)
{
	RECT rt = {0, 0, _Width, _Height};
	
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, !!GetMenu(m_hMainWnd));
	
	SetWindowPos(m_hMainWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);

	GetClientRect(m_hMainWnd, &rt);

	m_Resolution.x = (float)(rt.right - rt.left);
	m_Resolution.y = (float)(rt.bottom - rt.top);
}