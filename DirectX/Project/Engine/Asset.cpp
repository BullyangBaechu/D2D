#include "pch.h"
#include "Asset.h"

Asset::Asset(ASSET_TYPE _Type)
	: m_Type(_Type)
{
}

Asset::Asset(const Asset& _Origin)
	: Entity(_Origin)
	, m_Type(_Origin.m_Type)
	, m_Key()
	, m_RelativePath()
{
}

Asset::~Asset()
{
}
