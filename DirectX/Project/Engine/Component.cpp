#include "pch.h"
#include "Component.h"

#include "GameObject.h"

Component::Component(COMPONENT_TYPE _Type)
	: m_Type(_Type)
	, m_Owner(nullptr)
{
}

Component::Component(const Component& _Origin)
	: Entity(_Origin)
	, m_Type(_Origin.m_Type)
	, m_Owner(nullptr)
{
}

Component::~Component()
{
}

CTransform* Component::Transform()
{
	return m_Owner->Transform().Get();
}

CCamera* Component::Camera()
{
	return m_Owner->Camera().Get();
}

CMeshRender* Component::MeshRender()
{
	return  m_Owner->MeshRender().Get();
}

CCollider2D* Component::Collider2D()
{
	return  m_Owner->Collider2D().Get();
}

CSpriteRender* Component::SpriteRender()
{
	return m_Owner->SpriteRender().Get();
}

CFlipbookRender* Component::FlipbookRender()
{
	return m_Owner->FlipbookRender().Get();
}

bool Component::IsDead()
{
	return GetOwner()->IsDead();
}
