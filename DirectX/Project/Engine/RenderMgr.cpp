#include "pch.h"
#include "RenderMgr.h"

#include "Device.h"
#include "Component.h"

#include "AssetMgr.h"
#include "assets.h"

RenderMgr::RenderMgr()
{

}

RenderMgr::~RenderMgr()
{

}

void RenderMgr::Init()
{
	// DebugObject ���� ���̴� 
	Ptr<AGraphicShader> pShader = new AGraphicShader;
	pShader->CreateVertexShader(L"HLSL\\debug.fx", "VS_Debug");
	pShader->CreatePixelShader(L"HLSL\\debug.fx", "PS_Debug");
	pShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	pShader->SetDSType(DS_TYPE::LESS);
	AssetMgr::GetInst()->AddAsset(L"DebugShader", pShader.Get());

	// DebugObject ���� ����
	Ptr<AMaterial> pMtrl = new AMaterial;
	pMtrl->SetShader(pShader);
	AssetMgr::GetInst()->AddAsset(L"DebugMtrl", pMtrl.Get());

	// DebugRendering �� ����� GameObject ����
	m_DebugObj = new GameObject;
	m_DebugObj->SetName(L"DebugRenderObject");
	m_DebugObj->AddComponent(new CTransform);
	m_DebugObj->AddComponent(new CMeshRender);

	m_DebugObj->MeshRender()->SetMesh(AssetMgr::GetInst()->Find<AMesh>(L"RectMesh"));
	m_DebugObj->MeshRender()->SetMaterial(pMtrl);
}

void RenderMgr::Progress()
{	
	Device::GetInst()->TargetBinding(); // OM(Output Merge) Ÿ�� ���ε�
	Device::GetInst()->ClearTarget(Vec4(0.4f, 0.4f, 0.4f, 1.f)); // Clear Target
	
	// Render
	if (!m_vecCam.empty())
	{
		// Main ī�޶�� ������
		if (nullptr != m_vecCam[0])
			m_vecCam[0]->Render();

		// ���� ī�޶�� ������
		for (int i = 1; i < m_vecCam.size(); ++i)
		{
			if (nullptr == m_vecCam[i])
				continue;

			m_vecCam[i]->Render();
		}
	}
	
	// DebugRender
	render_debug();
}

void RenderMgr::render_debug()
{
	if (m_DebugList.empty())
		return;

	list<tDebugShapeInfo>::iterator iter = m_DebugList.begin();
	for (; iter != m_DebugList.end(); )
	{
		// ����� ������ ��û ������ ������, �˸°� ���������ش�.
		switch (iter->Shape)
		{
		case DEBUG_SHAPE::RECT:
			m_DebugObj->MeshRender()->SetMesh(AssetMgr::GetInst()->Find<AMesh>(L"RectMesh_Debug"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_DebugObj->MeshRender()->SetMesh(AssetMgr::GetInst()->Find<AMesh>(L"CircleMesh_Debug"));
			break;
		case DEBUG_SHAPE::LINE:
			break;
		case DEBUG_SHAPE::CUBE:
			break;
		case DEBUG_SHAPE::SPHERE:
			break;
		}

		if (iter->DepthTest)
			m_DebugObj->MeshRender()->GetMaterial()->GetShader()->SetDSType(DS_TYPE::LESS);
		else
			m_DebugObj->MeshRender()->GetMaterial()->GetShader()->SetDSType(DS_TYPE::NO_TEST_NO_WRITE);

		if (iter->matWorld == XMMatrixIdentity())
		{
			m_DebugObj->Transform()->SetRelativePos(iter->Pos);
			m_DebugObj->Transform()->SetRelativeScale(iter->Scale);
			m_DebugObj->Transform()->SetRelativeRot(iter->Rot);
			m_DebugObj->Transform()->FinalTick();
		}

		else
		{
			m_DebugObj->Transform()->SetWorldMat(iter->matWorld);
		}

		m_DebugObj->MeshRender()->GetMaterial()->SetScalar(VEC4_0, iter->Color);

		m_DebugObj->Render();

		// �ð��� �����Ѵ�.
		iter->CurTime += DT;

		// ����� ����ð��� �Ѿ��, �� ������ �����Ѵ�.
		if (iter->Duration < iter->CurTime)
		{
			iter = m_DebugList.erase(iter);
		}
		else
			++iter;
	}
}

void RenderMgr::RegisterCamera(CCamera* _Cam, int _Priority)
{
	// ���� �켱����
	int iPriority = _Cam->GetPriority();

	// ī�޶��� ���� ���� �ڸ��� ����ش�.
	if(iPriority != -1)
		m_vecCam[iPriority] = nullptr;

	// ���ο� �ڸ��� ��Ͻ�Ų��.
	_Cam->m_Priority = _Priority;
	if (m_vecCam.size() <= _Priority)
	{
		m_vecCam.resize(_Priority + 1);
	}

	// ���� �켱������ ���� ��ϵ� ī�޶� ������, ��������.
	if (nullptr != m_vecCam[_Priority])
		m_vecCam[_Priority]->m_Priority = -1;

	m_vecCam[_Priority] = _Cam;
}