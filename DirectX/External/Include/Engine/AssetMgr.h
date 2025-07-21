#pragma once

#include "assets.h"
#include "PathMgr.h"

class AssetMgr
	: public singleton<AssetMgr>
{
	SINGLE(AssetMgr)
private:
	map<wstring, Ptr<Asset>> m_mapAsset[ASSET_TYPE::ASSET_END];


public:
	void AddAsset(const wstring& _Key, Ptr<Asset> _Asset);
	const Ptr<Asset>& FindAsset(ASSET_TYPE _Type, const wstring& _Key);

	template<typename T>
	const Ptr<T>& Find(const wstring& _Key);

	template<typename T>
	const Ptr<T>& Load(const wstring& _Key, const wstring& _RelativePath);


public:
	void Init();

private:
	void CreateEngineMesh();
	void CreateEngineTexture();
	void CreateEngineGraphicShader();
	void CreateEngineMaterial();
	void CreateEngineSprite();
	void CreateEngineFlipbook();
	void CreateEnginePrefab();
};


template<typename T>
ASSET_TYPE GetAssetType()
{	
	if constexpr (std::is_same_v<T, AMesh>)
		return ASSET_TYPE::MESH;
	if constexpr (std::is_same_v<T, AGraphicShader>)
		return ASSET_TYPE::GRAPHICSHADER;
	if constexpr (std::is_same_v<T, ATexture>)
		return ASSET_TYPE::TEXTURE;
	if constexpr (std::is_same_v<T, AMaterial>)
		return ASSET_TYPE::MATERIAL;
	if constexpr (std::is_same_v<T, ASprite>)
		return ASSET_TYPE::SPRITE;
	if constexpr (std::is_same_v<T, AFlipbook>)
		return ASSET_TYPE::FLIPBOOK;
	if constexpr (std::is_same_v<T, APrefab>)
		return ASSET_TYPE::PREFAB;


	assert(nullptr);
}


template<typename T>
const Ptr<T>& AssetMgr::Find(const wstring& _Key)
{
	ASSET_TYPE Type = GetAssetType<T>();

	map<wstring, Ptr<Asset>>::iterator iter = m_mapAsset[Type].find(_Key);

	if (iter == m_mapAsset[Type].end())
		return nullptr;

	return (T*)iter->second.Get();
}

template<typename T>
const Ptr<T>& AssetMgr::Load(const wstring& _Key, const wstring& _RelativePath)
{
	T* pAsset = (T*)Find<T>(_Key).Get();

	if (pAsset)
		return pAsset;

	pAsset = new T;

	wstring ContentPath = PathMgr::GetInst()->GetContentPath();

	if (FAILED(pAsset->Load(ContentPath + _RelativePath)))
	{
		return nullptr;
	}

	pAsset->SetRelativePath(_RelativePath);
	AddAsset(_Key, pAsset);
	
	return pAsset;
}
