#include "pch.h"
#include "CCamMoveScript.h"

#include "CTransform.h"
#include "CCamera.h"


CCamMoveScript::CCamMoveScript()
	: m_Speed(500.f)
{
}

CCamMoveScript::~CCamMoveScript()
{
}

void CCamMoveScript::Tick()
{
	if (PROJ_TYPE::ORTHOGRAPHIC == Camera()->GetProjType())
	{
		Move_Orthographic();
	}
	else
	{
		Move_Perspective();
	}


	
}

void CCamMoveScript::Move_Orthographic()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
		vPos.y += m_Speed * DT;
	if (KEY_PRESSED(KEY::S))
		vPos.y -= m_Speed * DT;
	if (KEY_PRESSED(KEY::A))
		vPos.x -= m_Speed * DT;
	if (KEY_PRESSED(KEY::D))
		vPos.x += m_Speed * DT;

	Transform()->SetRelativePos(vPos);

	// 투영 범위 배율
	float Scale = Camera()->GetScale();
	if (KEY_PRESSED(KEY::NUM1))
		Scale += DT;
	else if (KEY_PRESSED(KEY::NUM2))
		Scale -= DT;

	if (Scale < 0.1f)
		Scale = 0.1f;

	Camera()->SetScale(Scale);
}

void CCamMoveScript::Move_Perspective()
{

	Vec3 vFront = Transform()->GetRelativeDir(DIR::FRONT);
	Vec3 vRight = Transform()->GetRelativeDir(DIR::RIGHT);
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
		vPos += vFront * m_Speed * DT;
	if (KEY_PRESSED(KEY::S))
		vPos += -vFront * m_Speed * DT;
	if (KEY_PRESSED(KEY::A))
		vPos += -vRight * m_Speed * DT;
	if (KEY_PRESSED(KEY::D))
		vPos += vRight * m_Speed * DT;

	Transform()->SetRelativePos(vPos);


	// 마우스의 이동방향을 카메라의 회전에 반영
	if (KEY_PRESSED(KEY::RBTN))
	{
		Vec2 vMouseDir = KeyMgr::GetInst()->GetMouseDir();

		Vec3 vRotDegree = Transform()->GetRoationDegree();

		vRotDegree.x += vMouseDir.y * DT * 720.f;
		vRotDegree.y += vMouseDir.x * DT * 720.f;

		Transform()->SetRotationDegree(vRotDegree);
	}
}
