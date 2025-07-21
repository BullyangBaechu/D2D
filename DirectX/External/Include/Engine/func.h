#pragma once

void DrawDebugRect(Vec3 _WorldPos, Vec3 _WorldScale, Vec4 _Color, bool _DepthTest, float _Duration = 0.f);
void DrawDebugRect(const Matrix& _matWorld, Vec4 _Color, bool _DepthTest, float _Duration = 0.f);

void SaveWString(const wstring& _Str, FILE* _File);
void LoadWString(wstring& _Str, FILE* _File);

void SaveAssetRef(class Asset* _Asset, FILE* _File);

void SpawnObject(UINT _LayerIdx, class GameObject* _Object);
void DestroyObject(class GameObject* _Object);

const char* GetString(ASSET_TYPE _Type);
const wchar_t* GetWString(ASSET_TYPE _Type);

const char* GetString(COMPONENT_TYPE _Type);
const wchar_t* GetWString(COMPONENT_TYPE _Type);



#include "AssetMgr.h"
template<typename T>
T* LoadAssetRef(FILE* _File)
{
	bool Exist = false;
	fread(&Exist, sizeof(bool), 1, _File);

	if (Exist)
	{
		wstring Key, Path;

		LoadWString(Key, _File);
		LoadWString(Path, _File);

		return AssetMgr::GetInst()->Load<T>(Key, Path).Get();
	}
	else
	{
		return nullptr;
	}
}