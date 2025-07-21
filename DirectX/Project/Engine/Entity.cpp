#include "pch.h"
#include "Entity.h"


UINT Entity::m_GlobalID = 0;

Entity::Entity()
	: m_ID(m_GlobalID++)
	, m_RefCount(0)
{
}

Entity::Entity(const Entity& _Origin)
	: m_ID(m_GlobalID++)
	, m_Name(_Origin.m_Name)
	, m_RefCount(0)
{
}

Entity::~Entity()
{
}