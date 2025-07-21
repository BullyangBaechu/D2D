#include "pch.h"
#include "KeyMgr.h"

#include "Engine.h"
#include "TimeMgr.h"

int g_KeyValue[(int)KEY::KEY_END] =
{
	'Q', 'W', 'E',  'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 
	'Z', 'X', 'C', 'V', 'B', 'N', 'M', 
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

	VK_LBUTTON, VK_RBUTTON, 
	VK_MENU, VK_CONTROL, VK_SPACE, VK_ESCAPE,
	VK_RETURN, VK_LSHIFT, 
	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, 
	VK_F1, VK_F2, VK_F3, VK_F4,
	VK_F5, VK_F6, VK_F7, VK_F8,
	VK_F9, VK_F10, VK_F11, VK_F12,

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,
};

KeyMgr::KeyMgr()
	: m_LockTime(0.f)
	, m_CurTime(0.f)
	, m_bLocked(false)
{
}

KeyMgr::~KeyMgr()
{
}

void KeyMgr::SetLock(float _LockFrame)
{
	m_LockTime = _LockFrame;
	m_CurTime = 0.f;
	m_bLocked = true;

	for (int i = 0; i < (int)KEY::KEY_END; ++i)
	{
		if (KEY_STATE::TAP == m_vecKey[i].State || KEY_STATE::PRESSED == m_vecKey[i].State)
			m_vecKey[i].State = KEY_STATE::PRESSED;
		else if (KEY_STATE::RELEASED == m_vecKey[i].State)
			m_vecKey[i].State = KEY_STATE::NONE;
	}
}

void KeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::KEY_END; ++i)
	{
		m_vecKey.push_back(tKeyState{ KEY_STATE::NONE, false });
	}
}

void KeyMgr::Tick()
{
	// �������� ���α׷��� ��Ŀ���� �Ǿ��ִٸ�
	// Lock �� �ɷ����� �ʾƾ��Ѵ�.
	if (nullptr != GetFocus() && !m_bLocked)
	{
		for (size_t i = 0; i < m_vecKey.size(); ++i)
		{
			// �ش� Ű�� �������� �ִٸ�
			if (GetAsyncKeyState(g_KeyValue[i]))
			{
				// �ش� Ű�� ���Ȱ�, ���� �����ӿ��� ���Ⱦ���.
				if (m_vecKey[i].PrevPressed)
				{
					m_vecKey[i].State = KEY_STATE::PRESSED;
				}

				// �ش� Ű�� ���Ȱ�, �������� �������� ����
				else
				{
					// �� ���� ������
					m_vecKey[i].State = KEY_STATE::TAP;
				}

				m_vecKey[i].PrevPressed = true;
			}

			// �ش� Ű�� ������ �ʾҴ�.
			else
			{
				// �ش�Ű�� ������ �ȴ����ְ�, ���� �����ӱ����� �����־���.
				if (m_vecKey[i].PrevPressed)
				{
					m_vecKey[i].State = KEY_STATE::RELEASED;
				}

				// �������� ������ �ʾҰ�, ���ݵ� �������� �ʴ�.
				else
				{
					m_vecKey[i].State = KEY_STATE::NONE;
				}

				m_vecKey[i].PrevPressed = false;
			}
		}

		// ���� ���������� ����
		m_PrevMousePos = m_MousePos;

		// �̹� ������ ���콺������ ���
		POINT ptMouse = {};
		GetCursorPos(&ptMouse);		
		ScreenToClient(Engine::GetInst()->GetMainWnd(), &ptMouse);		
		m_MousePos = Vec2((float)ptMouse.x, (float)ptMouse.y);

		// ���콺 ���� ��������
		m_MouseDir = m_MousePos - m_PrevMousePos;
	}

	// ���α׷��� ��Ŀ���� �ƴ� ���
	else
	{
		for (size_t i = 0; i < m_vecKey.size(); ++i)
		{
			// ��Ŀ���� �ƴϰų�, Lock �����϶� ���� ������, �ٽ� ����ȭ������ �ݿ����� �ʰ�
			// ���������� ���� ���� ���׿����� ������ �Ҹ��Ű�� �ִ´�.
			GetAsyncKeyState(g_KeyValue[i]);

			m_vecKey[i].PrevPressed = false;
			if (KEY_STATE::NONE == m_vecKey[i].State)			
				continue;

			if (KEY_STATE::TAP == m_vecKey[i].State || KEY_STATE::PRESSED == m_vecKey[i].State)
				m_vecKey[i].State = KEY_STATE::RELEASED;
			else if(KEY_STATE::RELEASED == m_vecKey[i].State)
				m_vecKey[i].State = KEY_STATE::NONE;
		}
	}

	m_CurTime += DT;
	if (m_LockTime <= m_CurTime)
	{
		m_bLocked = false;
	}
}