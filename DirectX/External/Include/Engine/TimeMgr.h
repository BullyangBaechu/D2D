#pragma once



class TimeMgr
	: public singleton<TimeMgr>
{
	SINGLE(TimeMgr);
private:
	LARGE_INTEGER	m_Frequency;	// �ʴ� ī���� Ƚ��
	LARGE_INTEGER	m_Prev;			// ���� ������ ī����
	LARGE_INTEGER	m_Current;		// �̹� ������ ī����

	float			m_DeltaTime;	// 1������ �����ϴµ� �ɸ��� �ð�
	float			m_Time;			// ���α׷��� ������ �ð�
	float			m_LimitDT;

	UINT			m_CallCount;

public:
	void Init();
	void Tick();

public:
	float GetDeltaTime() { return m_DeltaTime; }
	float GetTime() { return m_Time; }
};

