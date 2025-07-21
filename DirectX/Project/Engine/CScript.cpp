#include "pch.h"
#include "CScript.h"


CScript::CScript()
	: Component(COMPONENT_TYPE::SCRIPT)
{
}

CScript::~CScript()
{
}

void CScript::Destroy()
{
	DestroyObject(GetOwner());
}

void CScript::Instantiate(APrefab* _Prefab, Vec3 _WorldPos, int _LayerIdx)
{
	GameObject* pObject = _Prefab->Instantiate();
	pObject->Transform()->SetRelativePos(_WorldPos);
	SpawnObject(_LayerIdx, pObject);
}
