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
	, m_Priority(-1) // ��������� ī�޶�� ������ �켱���� ����� ���� ���־�� �Ѵ�.
	, m_LayerCheck(_Origin.m_LayerCheck)
{
}

CCamera::~CCamera()
{
}


void CCamera::FinalTick()
{
	// �佺���̽�
	// 1. ī�޶� ����
	// 2. ī�޶� �ٶ󺸴� ����� Z ���� �����ؾ� �Ѵ�.

	// ī�޶� �������� �̵���Ű�� �̵����
	Vec3 vCamPos = Transform()->GetRelativePos();
	Matrix matTranslation = XMMatrixTranslation(-vCamPos.x, -vCamPos.y, -vCamPos.z);

	// ī�޶� �ٶ󺸴� ������ Z ���� �ٶ󺸵��� �ϴ� ȸ�����
	Matrix matRoation = XMMatrixIdentity();

	Vec3 vR = Transform()->GetWorldDir(DIR::RIGHT);
	Vec3 vU = Transform()->GetWorldDir(DIR::UP);
	Vec3 vF = Transform()->GetWorldDir(DIR::FRONT);

	matRoation._11 = vR.x;  matRoation._12 = vU.x; matRoation._13 = vF.x;
	matRoation._21 = vR.y; 	matRoation._22 = vU.y; matRoation._23 = vF.y;
	matRoation._31 = vR.z; 	matRoation._32 = vU.z; matRoation._33 = vF.z;

	// �̵� x ȸ��(����)
	m_matView = matTranslation * matRoation;

	// ������� �����
	m_matProj = XMMatrixIdentity();

	// �����������
	if (PROJ_TYPE::ORTHOGRAPHIC == m_ProjType)
	{
		m_matProj = XMMatrixOrthographicLH(m_Width * m_Scale, m_Scale * (m_Width / m_AspectRatio), 1.f, m_Far);
	}

	// ��������
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
	// RENDER_DOMINA ���� �з�
	SortObject();

	// Domain ������� ������
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
		// ī�޶� ���� �ʴ� Layer �� �ǳʶڴ�.
		if (!(m_LayerCheck & (1 << i)))
			continue;

		Ptr<Layer> pLayer = pLevel->GetLayer(i);
		const vector<Ptr<GameObject>>& vecObjects = pLayer->GetObjects();

		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			// �������� �Ұ����� GameObject �� �ǳʶڴ�.
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
