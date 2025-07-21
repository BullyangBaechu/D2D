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

	// ũ �� �� 
	m_matWorld = matScale * matRotation * matTranslation;

	// ���� ���⺤��
	static Vec3 BaseAxis[3] =
	{
		Vec3(1.f, 0.f, 0.f),
		Vec3(0.f, 1.f, 0.f),
		Vec3(0.f, 0.f, 1.f),
	};

	for (int i = 0; i < 3; ++i)
	{
		// ������ǥ 0
		m_WorldDir[i] = m_RelativeDir[i] = XMVector3TransformNormal(BaseAxis[i], matRotation);
	}

	// �θ� ������Ʈ�� �ִٸ�
	if (nullptr != GetOwner()->GetParent())
	{
		// �θ��� ũ�⿡ ������ ���� �ʰڴ�.
		if (m_IndependentScale)
		{
			// �θ� ������Ʈ�� Transform ���κ��� ��������� �����´�.
			// �θ� ������Ʈ�� ���彺������ �����´�.
			Vec3 vParentWorldScale = GetOwner()->GetParent()->Transform()->GetWorldScale();
			Matrix matParentWorldScaleInv = XMMatrixInverse(nullptr, XMMatrixScaling(vParentWorldScale.x, vParentWorldScale.y, vParentWorldScale.z));

			// ���� ������� == ũ * ȸ * �� * (�θ�ũ�� Inverse) *  �θ�(ũ * ȸ * ��) ==> ���� �������(ũ ȸ ��)
			m_matWorld = m_matWorld * matParentWorldScaleInv * GetOwner()->GetParent()->Transform()->GetWorldMat();
		}
		
		// �θ��� ũ�⿡ ������ �޴´�.
		else
		{
			// �θ� ������Ʈ�� Transform ���κ��� ��������� �����´�.
			// ���� ������� == ũ * ȸ * �� * �θ�(ũ * ȸ * ��) == ũ ȸ ��
			m_matWorld *= GetOwner()->GetParent()->Transform()->GetWorldMat();
		}

		// ���� ��������� �����, ��ü�� ����󿡼��� Right, Up, Front ���⺤��
		for (int i = 0; i < 3; ++i)
		{
			// ������ǥ 0
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
