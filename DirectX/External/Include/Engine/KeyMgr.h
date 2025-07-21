#pragma once


enum class KEY
{
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M, 

	_0, _1, _2, _3, _4, _5, _6, _7, _8, _9,

	LBTN, RBTN,
	ALT, CTRL, SPACE, ESC, ENTER, LSHFT,
	LEFT, RIGHT, UP, DOWN,

	F1, F2, F3, F4, 
	F5, F6, F7, F8,	
	F9, F10, F11, F12,

	NUM0,
	NUM1,
	NUM2,
	NUM3,
	NUM4,
	NUM5,
	NUM6,
	NUM7,
	NUM8,
	NUM9,

	KEY_END,
};

enum class KEY_STATE
{
	NONE,		// ������ ���� ����
	TAP,		// �� ���� ����
	PRESSED,	// �����ִ� ����
	RELEASED,	// Ű�� ������ ����
};

struct tKeyState
{
	KEY_STATE	State;		 // ���� Ű�� ����
	bool		PrevPressed; // ������ ���ȴ��� Ȯ��
};


class KeyMgr
	: public singleton<KeyMgr>
{
	SINGLE(KeyMgr)
private:
	vector<tKeyState>	m_vecKey;
	Vec2				m_MousePos;
	Vec2				m_PrevMousePos;
	Vec2				m_MouseDir;
		
	float				m_LockTime;
	float				m_CurTime;
	bool				m_bLocked;

public:
	KEY_STATE GetKeyState(KEY _Key) { return m_vecKey[(int)_Key].State; }
	Vec2 GetMousePos() { return m_MousePos; }
	Vec2 GetMouseDir() { return m_MouseDir; }

	void SetLock(float _LockFrame);


public:
	void Init();
	void Tick();
};

