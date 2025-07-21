#include "pch.h"
#include "CAtlasScript.h"

#include "RenderMgr.h"

#include "CTransform.h"
#include "CCamera.h"


CAtlasScript::CAtlasScript()
{
}

CAtlasScript::~CAtlasScript()
{
}

void CAtlasScript::Tick()
{
	if (KEY_TAP(KEY::LBTN))
	{
		CCamera* pMainCam = RenderMgr::GetInst()->GetPOVCamera();

		Vec2 vMousePressedPos = KeyMgr::GetInst()->GetMousePos();

		Vec2 vCamPos = Vec2(pMainCam->Transform()->GetRelativePos().x, pMainCam->Transform()->GetRelativePos().y);
		Vec2 ProjRange = Vec2(pMainCam->GetWidth(), pMainCam->GetWidth() / pMainCam->GetAspectRatio());
		Vec2 vGamePos = Vec2(vMousePressedPos.x - ProjRange.x / 2.f, -(vMousePressedPos.y - ProjRange.y / 2.f)) 
			          + vCamPos;

		Vec3 vPos = Transform()->GetRelativePos();
		Vec3 vScale = Transform()->GetWorldScale();
		Vec3 vLeftTop = vPos + (vScale / Vec3(-2.f, 2.f, 1.f));


		m_PixelPos = vGamePos - Vec2(vLeftTop.x, vLeftTop.y);
		m_PixelPos.y *= -1.f;
	}

	
}
