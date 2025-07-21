#include "pch.h"
#include "LevelMgr.h"


#include "PathMgr.h"
#include "Device.h"
#include "AssetMgr.h"
#include "ATexture.h"

#include "CPlayerScript.h"
#include "CCamMoveScript.h"
#include "CAtlasScript.h"

#include "CollisionMgr.h"

LevelMgr::LevelMgr()
{

}

LevelMgr::~LevelMgr()
{

}

void LevelMgr::Init()
{
	m_CurLevel = new ALevel;
	m_CurLevel->SetName(L"TempLevel");

	m_CurLevel->GetLayer(0)->SetName(L"Default");
	m_CurLevel->GetLayer(1)->SetName(L"Background");
	m_CurLevel->GetLayer(2)->SetName(L"Tile");
	m_CurLevel->GetLayer(3)->SetName(L"Player");
	m_CurLevel->GetLayer(4)->SetName(L"Enermy");
	m_CurLevel->GetLayer(5)->SetName(L"PlayerProjectile");
	m_CurLevel->GetLayer(6)->SetName(L"EnermyProjectile");



	Ptr<ATexture> pTex = AssetMgr::GetInst()->Load<ATexture>(L"Sonic", L"Texture\\Idle_Left.bmp");

	Ptr<GameObject> pObject = nullptr;

	// MainCamera ������Ʈ
	pObject = new GameObject;
	pObject->SetName(L"MainCamera");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CCamera);
	pObject->AddComponent(new CCamMoveScript);

	pObject->Camera()->SetProjType(ORTHOGRAPHIC);
	pObject->Camera()->SetPriority(0); // ���� ī�޶�� ���
	pObject->Camera()->LayerCheckAll(); // ��� ���̾ �ִ� ������Ʈ���� �������Ѵ�.

	m_CurLevel->AddObject(0, pObject.Get(), false);


	// ���� ����
	Ptr<AMaterial> pStd2DMtrl = AssetMgr::GetInst()->Find<AMaterial>(L"Std2DMtrl");
	pStd2DMtrl->SetTexture(TEX_0, AssetMgr::GetInst()->Load<ATexture>(L"Character", L"Texture\\Character.png"));

	// Player ������Ʈ
	pObject = new GameObject;
	pObject->SetName(L"Player");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CFlipbookRender);
	pObject->AddComponent(new CPlayerScript);
	pObject->AddComponent(new CCollider2D);

	pObject->Transform()->SetRelativePos(Vec3(0.f, 0.f, 100.f));
	pObject->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pObject->Collider2D()->SetScale(Vec2(0.5f, 0.6f));

	pObject->FlipbookRender()->AddFlipbook(0, AssetMgr::GetInst()->Find<AFlipbook>(L"LinkMD"));
	pObject->FlipbookRender()->Play(0, 15.f, PLAY_LOOP);

	m_CurLevel->AddObject(3, pObject.Get(), false);


	// Player ������Ʈ ����
	pObject = pObject->Clone();
	pObject->SetName(L"Player Clone");
	pObject->Transform()->SetRelativePos(Vec3(-200.f, 0.f, 100.f));
	m_CurLevel->AddObject(3, pObject.Get(), false);

	pObject = pObject->Clone();
	pObject->SetName(L"Player Clone");
	pObject->Transform()->SetRelativePos(Vec3(200.f, 0.f, 100.f));
	m_CurLevel->AddObject(3, pObject.Get(), false);

	// Monster
	pObject = new GameObject;
	pObject->SetName(L"Monster");
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CCollider2D);

	pObject->Transform()->SetRelativePos(Vec3(0.f, 300.f, 100.f));
	pObject->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	pObject->Collider2D()->SetScale(Vec2(1.f, 1.f));

	pObject->MeshRender()->SetMesh(FIND(AMesh, L"RectMesh"));
	pObject->MeshRender()->SetMaterial(FIND(AMaterial, L"Std2DMtrl"));

	m_CurLevel->AddObject(4, pObject.Get(), false);


	// ���̾� ���� �浹üũ 
	CollisionMgr::GetInst()->CollisionCheck(3, 4);
	CollisionMgr::GetInst()->CollisionCheck(4, 5);


	// ���� ����
	m_CurLevel->Begin();
}

void LevelMgr::Progress()
{
	// ���������ӿ� ��ϵ� ������Ʈ���� ����
	m_CurLevel->Deregister();

	// ���� ������Ʈ
	m_CurLevel->Tick();
	m_CurLevel->FinalTick();
}

GameObject* LevelMgr::FindObjectByName(const wstring& _Name)
{
	return m_CurLevel->FindObjectByName(_Name); 
}
