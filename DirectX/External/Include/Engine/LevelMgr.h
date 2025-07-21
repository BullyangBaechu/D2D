#pragma once


#include "ALevel.h"

class LevelMgr
	: public singleton<LevelMgr>
{
	SINGLE(LevelMgr);
private:
	Ptr<ALevel>		m_CurLevel;

public:
	void Init();
	void Progress();



public:
	class GameObject* FindObjectByName(const wstring& _Name);

public:
	Ptr<ALevel> GetCurrentLevel() { return m_CurLevel; }
};

