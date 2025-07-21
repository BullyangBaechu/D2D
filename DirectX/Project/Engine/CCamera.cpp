#include "pch.h"
#include "CCamera.h"

#include "CTransform.h"
#include "Device.h"
#include "RenderMgr.h"

CCamera::CCamera()
	: Component(COMPONENT_TYPE::CAMERA)
	, m_Far(10000.f)
	, m_FOV(XM_PI / 2.f)
	, m_AspectRatio(1.f)
	, m_Scale(1.f)
	, m_Priority(-1)
	, m_LayerCheck(0)
{
	Vec2 vResol = Device::GetInst()->GetRenderResolution();
	m_Width = vResol.x;
	m_AspectRatio = vResol.x / vResol.y;
}

CCamera::CCamera(const CCamera& _Origin)
	: Component(_Origin)
	, m_Far(_Origin.m_Far)
	, m_FOV(_Origin.m_FOV)
	, m_Width(_Origin.m_Width)
	, m_AspectRatio(_Origin.m_AspectRatio)
	, m_Scale(_Origin.m_Scale)
	, m_ProjType(_Origin.m_ProjType)
	, m_Priority(-1) // 복사생성된 카메라는 별도의 우선순위 등록을 따로 해주어야 한다.
	, m_LayerCheck(_Origin.m_LayerCheck)
{
}

CCamera::~CCamera()
{
}


void CCamera::FinalTick()
{
	// 뷰스페이스
	// 1. 카메라가 원점
	// 2. 카메라가 바라보는 방향과 Z 축이 평행해야 한다.

	// 카메라를 원점으로 이동시키는 이동행렬
	Vec3 vCamPos = Transform()->GetRelativePos();
	Matrix matTranslation = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);

	// 카메라가 바라보는 방향을 Z 축을 바라보도록 하는 회전행렬
	Matrix matRoation = XMMatrixIdentity();

	Vec3 vR = Transform()->GetWorldDir(DIR::RIGHT);
	Vec3 vU = Transform()->GetWorldDir(DIR::UP);
	Vec3 vF = Transform()->GetWorldDir(DIR::FRONT);

	matRoation._11 = vR.x;  matRoation._12 = vU.x; matRoation._13 = vF.x;
	matRoation._21 = vR.y; 	matRoation._22 = vU.y; matRoation._23 = vF.y;
	matRoation._31 = vR.z; 	matRoation._32 = vU.z; matRoation._33 = vF.z;

	// 이동 x 회전(공전)
	m_matView = matTranslation * matRoation;

	// 투영행렬 만들기
	m_matProj = XMMatrixIdentity();

	// 직교투영행렬
	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType)
	{
		m_matProj = XMMatrixOrthographicLH(m_Width * m_Scale, m_Scale * (m_Width / m_AspectRatio), 1.f, m_Far);
	}

	// 원근투영
	else
	{
		m_matProj = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, 1.f, m_Far);
	}

	g_Trans.matView = m_matView;
	g_Trans.matProj = m_matProj;
}

void CCamera::SetPriority(int _Priority)
{
	RenderMgr::GetInst()->RegisterCamera(this, _Priority);
}

void CCamera::LayerCheck(UINT _LayerIdx)
{
	m_LayerCheck ^= (1 << _LayerIdx);
}



#include "LevelMgr.h"
#include "ALevel.h"
#include "Layer.h"
#include "GameObject.h"
#include "components.h"

void CCamera::Render()
{
	// RENDER_DOMINA 따른 분류
	SortObject();

	// Domain 순서대로 렌더링
	for (size_t i = 0; i < m_Opaque.size(); ++i)
	{
		m_Opaque[i]->Render();
	}

	for (size_t i = 0; i < m_Masked.size(); ++i)
	{
		m_Masked[i]->Render();
	}

	for (size_t i = 0; i < m_Transparent.size(); ++i)
	{
		m_Transparent[i]->Render();
	}
}

void CCamera::SortObject()
{
	m_Opaque.clear();
	m_Masked.clear();
	m_Transparent.clear();

	Ptr<ALevel> pLevel = LevelMgr::GetInst()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		// 카메라가 찍지 않는 Layer 는 건너뛴다.
		if (!(m_LayerCheck & (1 << i)))
			continue;

		Ptr<Layer> pLayer = pLevel->GetLayer(i);
		const vector<Ptr<GameObject>>& vecObjects = pLayer->GetObjects();

		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			// 렌더링이 불가능한 GameObject 는 건너뛴다.
			if (nullptr == vecObjects[j]->GetRenderComponent()
				|| nullptr == vecObjects[j]->GetRenderComponent()->GetMesh()
				|| nullptr == vecObjects[j]->GetRenderComponent()->GetMaterial()
				|| nullptr == vecObjects[j]->GetRenderComponent()->GetMaterial()->GetShader())
				continue;

			RENDER_DOMAIN domain = vecObjects[j]->GetRenderComponent()->GetMaterial()->GetDomain();

			switch (domain)
			{
			case DOMAIN_OPAQUE:
				m_Opaque.push_back(vecObjects[j].Get());
				break;
			case DOMAIN_MASKED:
				m_Masked.push_back(vecObjects[j].Get());
				break;
			case DOMAIN_TRANSPARENT:
				m_Transparent.push_back(vecObjects[j].Get());
				break;
			}
		}
	}
}
