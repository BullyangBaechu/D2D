#include "pch.h"
#include "TimeMgr.h"

#include "Engine.h"
#include "PathMgr.h"

TimeMgr::TimeMgr()
	: m_Frequency{}
	, m_Prev{}
	, m_Current{}
	, m_DeltaTime(0.f)
	, m_Time(0.f)
	, m_LimitDT(1.f/ 60.f)
	, m_CallCount(0)
{
}

TimeMgr::~TimeMgr()
{
}

void TimeMgr::Init()
{
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_Prev);
}

void TimeMgr::Tick()
{
	QueryPerformanceCounter(&m_Current);

	// ������ ���� �ð�
	m_DeltaTime = (float)(m_Current.QuadPart - m_Prev.QuadPart) / (float)m_Frequency.QuadPart;

	// �ð��� ����
	m_Time += m_DeltaTime;

	if (m_DeltaTime > m_LimitDT)
	{
		m_DeltaTime = m_LimitDT;
	}

	// 1�ʿ� ȣ��Ǵ� Ƚ��(FPS)
	++m_CallCount;
	if (1.f < m_Time)
	{
		m_Time -= 1.f;

		wchar_t szBuff[100] = {};
		swprintf_s(szBuff, 100, L"FSP : %d, DT : %f, %s", m_CallCount, m_DeltaTime, PathMgr::GetInst()->GetBinPath());
		SetWindowText(Engine::GetInst()->GetMainWnd(), szBuff);

		m_CallCount = 0;
	}
		 
	m_Prev = m_Current;
}
