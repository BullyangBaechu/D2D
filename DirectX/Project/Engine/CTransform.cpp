#include "pch.h"
#include "CTransform.h"

#include "Device.h"
#include "GameObject.h"

CTransform::CTransform()
	: Component(COMPONENT_TYPE::TRANSFORM)
	, m_RelativeScale(Vec3(1.f, 1.f, 1.f))
{
}

CTransform::~CTransform()
{
}

void CTransform::FinalTick()
{
	Matrix matScale = XMMatrixScaling(m_RelativeScale.x, m_RelativeScale.y, m_RelativeScale.z);
	Matrix matRotation = XMMatrixRotationX(m_RelativeRot.x) * XMMatrixRotationY(m_RelativeRot.y) * XMMatrixRotationZ(m_RelativeRot.z);
	Matrix matTranslation = XMMatrixTranslation(m_RelativePos.x, m_RelativePos.y, m_RelativePos.z);

	// 크 자 이 
	m_matWorld = matScale * matRotation * matTranslation;

	// 로컬 방향벡터
	static Vec3 BaseAxis[3] =
	{
		Vec3(1.f, 0.f, 0.f),
		Vec3(0.f, 1.f, 0.f),
		Vec3(0.f, 0.f, 1.f),
	};

	for (int i = 0; i < 3; ++i)
	{
		// 동차좌표 0
		m_WorldDir[i] = m_RelativeDir[i] = XMVector3TransformNormal(BaseAxis[i], matRotation);
	}

	// 부모 오브젝트가 있다면
	if (nullptr != GetOwner()->GetParent())
	{
		// 부모의 크기에 영향을 받지 않겠다.
		if (m_IndependentScale)
		{
			// 부모 오브젝트의 Transform 으로부터 월드행렬을 가져온다.
			// 부모 오브젝트의 월드스케일을 가져온다.
			Vec3 vParentWorldScale = GetOwner()->GetParent()->Transform()->GetWorldScale();
			Matrix matParentWorldScaleInv = XMMatrixInverse(nullptr, XMMatrixScaling(vParentWorldScale.x, vParentWorldScale.y, vParentWorldScale.z));

			// 최종 월드행렬 == 크 * 회 * 이 * (부모크기 Inverse) *  부모(크 * 회 * 이) ==> 최종 월드행렬(크 회 이)
			m_matWorld = m_matWorld * matParentWorldScaleInv * GetOwner()->GetParent()->Transform()->GetWorldMat();
		}
		
		// 부모의 크기에 영향을 받는다.
		else
		{
			// 부모 오브젝트의 Transform 으로부터 월드행렬을 가져온다.
			// 최종 월드행렬 == 크 * 회 * 이 * 부모(크 * 회 * 이) == 크 회 이
			m_matWorld *= GetOwner()->GetParent()->Transform()->GetWorldMat();
		}

		// 최종 월드행렬이 적용된, 물체의 월드상에서의 Right, Up, Front 방향벡터
		for (int i = 0; i < 3; ++i)
		{
			// 동차좌표 0
			m_WorldDir[i] = XMVector3TransformNormal(BaseAxis[i], m_matWorld);
			m_WorldDir[i].Normalize();
		}
	}
}

void CTransform::Binding()
{
	static Ptr<ConstBuffer> pCB = Device::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
		
	g_Trans.matWorld = m_matWorld;
	g_Trans.matWV = g_Trans.matWorld * g_Trans.matView;
	g_Trans.matWVP = g_Trans.matWV * g_Trans.matProj;
	
	pCB->SetData(&g_Trans, sizeof(tTransform));
	pCB->Binding();
}


Vec3 CTransform::GetWorldScale()
{
	Vec3 vWorldScale = Vec3(1.f, 1.f, 1.f);

	GameObject* pObject = GetOwner();

	while (pObject)
	{
		vWorldScale *= pObject->Transform()->GetRelativeScale();

		if (pObject->Transform()->GetIndependentScale())
			break;

		pObject = pObject->GetParent().Get();
	}

	return vWorldScale;
}
