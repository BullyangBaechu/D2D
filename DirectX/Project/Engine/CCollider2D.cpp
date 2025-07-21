#include "pch.h"
#include "CCollider2D.h"

#include "RenderMgr.h"
#include "GameObject.h"
#include "CTransform.h"

CCollider2D::CCollider2D()
	: Component(COMPONENT_TYPE::COLLIDER2D)
	, m_Scale(Vec3(1.f, 1.f, 1.f))
	, m_IndependentScale(false)
	, m_OverlapCount(0)
{
}

CCollider2D::CCollider2D(const CCollider2D& _Origin)
	: Component(_Origin)
	, m_Offset(_Origin.m_Offset)
	, m_Scale(_Origin.m_Scale)        
	, m_IndependentScale(_Origin.m_IndependentScale)
	, m_OverlapCount(0)
	, m_matColWorld(_Origin.m_matColWorld)  
{
}

CCollider2D::~CCollider2D()
{
}

void CCollider2D::FinalTick()
{
	// 월드행렬 계산
	Matrix matScale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	Matrix matTrans = XMMatrixTranslation(m_Offset.x, m_Offset.y, m_Offset.z);

	// 오브젝트의 크기에 영향을 받지 않는다.
	if (m_IndependentScale)
	{
		Vec3 ObjectWorldScale = Transform()->GetWorldScale();
		Matrix matParentWorldScaleInv = XMMatrixInverse(nullptr, XMMatrixScaling(ObjectWorldScale.x, ObjectWorldScale.y, ObjectWorldScale.z));
		m_matColWorld = matScale * matTrans * matParentWorldScaleInv * Transform()->GetWorldMat();
	}

	// 오브젝트의 크기에 영향을 받는다.
	else
	{
		m_matColWorld = matScale * matTrans * Transform()->GetWorldMat();
	}
	
	// DebugRender 요청
	if (0 == m_OverlapCount)
		DrawDebugRect(m_matColWorld, Vec4(0.f, 1.f, 0.f, 0.f), false);
	else if (0 < m_OverlapCount)
		DrawDebugRect(m_matColWorld, Vec4(1.f, 0.f, 0.f, 0.f), false);
	else
		assert(nullptr);
}

void CCollider2D::BeginOverlap(CCollider2D* _Other)
{
	++m_OverlapCount;

	const vector<Ptr<CScript>>& vecScripts = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		vecScripts[i]->BeginOverlap(this, _Other, _Other->GetOwner());
	}
}

void CCollider2D::Overlap(CCollider2D* _Other)
{
	const vector<Ptr<CScript>>& vecScripts = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		vecScripts[i]->Overlap(this, _Other, _Other->GetOwner());
	}
}

void CCollider2D::EndOverlap(CCollider2D* _Other)
{
	--m_OverlapCount;

	const vector<Ptr<CScript>>& vecScripts = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		vecScripts[i]->EndOverlap(this, _Other, _Other->GetOwner());
	}
}