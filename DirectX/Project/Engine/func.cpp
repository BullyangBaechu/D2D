#include "pch.h"
#include "func.h"

#include "RenderMgr.h"

void DrawDebugRect(Vec3 _WorldPos, Vec3 _WorldScale, Vec4 _Color, bool _DepthTest, float _Duration)
{
	tDebugShapeInfo info = {};
	info.Shape = DEBUG_SHAPE::RECT;

	info.Pos = _WorldPos;
	info.Scale = _WorldScale;
	info.Rot = Vec3(0.f, 0.f, 0.f);

	info.matWorld = XMMatrixIdentity();

	info.Color = _Color;

	info.DepthTest = _DepthTest;
	info.CurTime = 0.f;
	info.Duration = _Duration;

	RenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void DrawDebugRect(const Matrix& _matWorld, Vec4 _Color, bool _DepthTest, float _Duration)
{
	tDebugShapeInfo info = {};
	info.Shape = DEBUG_SHAPE::RECT;

	info.Pos = Vec3(0.f, 0.f, 0.f);
	info.Scale = Vec3(1.f, 1.f, 1.f);
	info.Rot = Vec3(0.f, 0.f, 0.f);

	info.matWorld = _matWorld;

	info.Color = _Color;

	info.DepthTest = _DepthTest;
	info.CurTime = 0.f;
	info.Duration = _Duration;

	RenderMgr::GetInst()->AddDebugShapeInfo(info);
}

void SaveWString(const wstring& _Str, FILE* _File)
{
	UINT Len = (UINT)_Str.length();

	fwrite(&Len, sizeof(UINT), 1, _File);

	fwrite(_Str.c_str(), sizeof(wchar_t), Len, _File);
}

void LoadWString(wstring& _Str, FILE* _File)
{
	UINT Len = 0;

	fread(&Len, sizeof(UINT), 1, _File);

	wchar_t szBuff[255] = {};

	fread(szBuff, sizeof(wchar_t), Len, _File);

	_Str = szBuff;
}

#include "Asset.h"
void SaveAssetRef(Asset* _Asset, FILE* _File)
{
	bool Exist = !!_Asset;
	fwrite(&Exist, sizeof(bool), 1, _File);

	if (Exist)
	{
		wstring Key = _Asset->GetKey();
		wstring Path = _Asset->GetRelativePath();

		SaveWString(Key, _File);
		SaveWString(Path, _File);
	}
}

#include "TaskMgr.h"
void SpawnObject(UINT _LayerIdx, GameObject* _Object)
{
	tTaskInfo info = {};

	info.Type = TASK_TYPE::CREATE_OBJECT;
	info.Param_0 = (DWORD_PTR)_Object;
	info.Param_1 = _LayerIdx;

	TaskMgr::GetInst()->AddTask(info);
}

void DestroyObject(GameObject* _Object)
{
	tTaskInfo info = {};

	info.Type = TASK_TYPE::DELETE_OBJECT;
	info.Param_0 = (DWORD_PTR)_Object;

	TaskMgr::GetInst()->AddTask(info);
}

const char* GetString(ASSET_TYPE _Type)
{
	return ASSET_TYPE_STR[_Type];
}

const wchar_t* GetWString(ASSET_TYPE _Type)
{
	return ASSET_TYPE_WSTR[_Type];
}

const char* GetString(COMPONENT_TYPE _Type)
{
	return COMPONENT_TYPE_STR[(UINT)_Type];
}

const wchar_t* GetWString(COMPONENT_TYPE _Type)
{
	return COMPONENT_TYPE_WSTR[(UINT)_Type];
}



