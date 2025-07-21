#include "pch.h"
#include "APrefab.h"

APrefab::APrefab()
	: Asset(ASSET_TYPE::PREFAB)
	, m_ProtoObj(nullptr)
{
}

APrefab::APrefab(const APrefab& _Origin)
	: Asset(_Origin)
	, m_ProtoObj(nullptr)
{
	if (nullptr != _Origin.m_ProtoObj)
		m_ProtoObj = _Origin.m_ProtoObj->Clone();
}

APrefab::~APrefab()
{
}
