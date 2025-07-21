#include "pch.h"
#include "AssetMgr.h"

#include "AMesh.h"
#include "AGraphicShader.h"
#include "AMaterial.h"

AssetMgr::AssetMgr()
{

}

AssetMgr::~AssetMgr()
{

}

void AssetMgr::AddAsset(const wstring& _Key, Ptr<Asset> _Asset)
{
	ASSET_TYPE Type = _Asset->GetType();

	if (nullptr == FindAsset(Type, _Key))
	{
		_Asset->SetKey(_Key);
		m_mapAsset[Type].insert(make_pair(_Key, _Asset));
	}	
}

const Ptr<Asset>& AssetMgr::FindAsset(ASSET_TYPE _Type, const wstring& _Key)
{
	map<wstring, Ptr<Asset>>::iterator iter = m_mapAsset[_Type].find(_Key);

	if (iter == m_mapAsset[_Type].end())
		return nullptr;

	return iter->second;
}

