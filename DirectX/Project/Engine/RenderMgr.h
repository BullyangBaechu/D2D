#pragma once

class CCamera;

#include "GameObject.h"

class RenderMgr
	: public singleton<RenderMgr>
{
	SINGLE(RenderMgr);
private:
	vector<CCamera*>		m_vecCam;		// 레벨에 있는 카메라를 등록받음

	Ptr<GameObject>			m_DebugObj;		// 디버그 렌더링을 하기위한 샘플 오브젝트
	list<tDebugShapeInfo>	m_DebugList;	// 디버그 요청정보들

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

