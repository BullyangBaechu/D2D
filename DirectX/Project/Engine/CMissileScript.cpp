#include "pch.h"
#include "CMissileScript.h"

#include "GameObject.h"
#include "CTransform.h"
#include "TaskMgr.h"

CMissileScript::CMissileScript()
	: m_Speed(500.f)
{
}

CMissileScript::~CMissileScript()
{
}

void CMissileScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	vPos.y += DT * m_Speed;

	Transform()->SetRelativePos(vPos);
}

void CMissileScript::BeginOverlap(CCollider2D* _OwnCollider, CCollider2D* _Collider2D, GameObject* _OtherObj)
{
	if (L"Monster" == _OtherObj->GetName())
	{
		//DestroyObject(GetOwner());
		//GetOwner()->Destroy();
		Destroy();
	}
}