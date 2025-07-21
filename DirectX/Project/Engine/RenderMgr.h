#pragma once

class CCamera;

#include "GameObject.h"

class RenderMgr
	: public singleton<RenderMgr>
{
	SINGLE(RenderMgr);
private:
	vector<CCamera*>		m_vecCam;		// ������ �ִ� ī�޶� ��Ϲ���

	Ptr<GameObject>			m_DebugObj;		// ����� �������� �ϱ����� ���� ������Ʈ
	list<tDebugShapeInfo>	m_DebugList;	// ����� ��û������

public:
	void RegisterCamera(CCamera* _Cam, int _Priority);
	void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_DebugList.push_back(_info); }

	CCamera* GetPOVCamera() { if (m_vecCam.empty()) return nullptr; return m_vecCam[0];}
	

public:
	void Init();
	void Progress();

private:
	void render_debug();
};

