#include "pch.h"
#include "CPlayerScript.h"

#include "GameObject.h"
#include "components.h"

#include "CMissileScript.h"

#include "TaskMgr.h"

CPlayerScript::CPlayerScript()
	: m_Speed(200.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Begin()
{
	m_MissilePref = FIND(APrefab, L"MissilePref");
}

void CPlayerScript::Tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	Vec3 vRight = Transform()->GetRelativeDir(DIR::RIGHT);
	Vec3 vUp = Transform()->GetRelativeDir(DIR::UP);

	if (KEY_PRESSED(KEY::LEFT))
		vPos += -vRight * m_Speed * DT;
	if (KEY_PRESSED(KEY::RIGHT))
		vPos += vRight * m_Speed * DT;
	if (KEY_PRESSED(KEY::UP))
		vPos += vUp * m_Speed * DT;
	if (KEY_PRESSED(KEY::DOWN))
		vPos += -vUp * m_Speed * DT;

	if (KEY_PRESSED(KEY::Z))
	{
		Vec3 vRot = Transform()->GetRoationDegree();
		vRot.z += 360.f * DT;
		Transform()->SetRotationDegree(vRot);
	
	}
	if (KEY_PRESSED(KEY::X))
		vPos.z -= m_Speed * DT;

	if (KEY_TAP(KEY::SPACE))
		Shoot();


	Transform()->SetRelativePos(vPos);
}

void CPlayerScript::BeginOverlap(CCollider2D* _OwnCollider, CCollider2D* _Collider2D, GameObject* _OtherObj)
{
	int a = 0;
}

void CPlayerScript::Shoot()
{
	if (nullptr == m_MissilePref)
		return;

	Instantiate(m_MissilePref.Get(), Transform()->GetRelativePos(), 5);
}