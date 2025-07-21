#include "pch.h"
#include "AssetMgr.h"

void AssetMgr::Init()
{
	CreateEngineMesh();

	CreateEngineTexture();

	CreateEngineGraphicShader();

	CreateEngineMaterial();

	CreateEngineSprite();

	CreateEngineFlipbook();

	CreateEnginePrefab();
}

void AssetMgr::CreateEngineMesh()
{
	// ========
	// RectMesh
	// ========
	// 정점정보 입력
	//  0 -- 1
	//  | \  |
	//  3 -- 2
	Vtx arrVtx[4] = {};

	arrVtx[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[0].vUV = Vec2(0.f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	arrVtx[1].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[1].vUV = Vec2(1.f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	arrVtx[2].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[2].vUV = Vec2(1.f, 1.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	arrVtx[3].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[3].vUV = Vec2(0.f, 1.f);
	arrVtx[3].vColor = Vec4(0.33f, 0.33f, 0.33f, 1.f);

	UINT arrIdx[6] = { 0, 1, 2, 0, 2, 3 };

	Ptr<AMesh> pMesh = new AMesh;
	pMesh->Create(arrVtx, 4, arrIdx, 6);
	AddAsset(L"RectMesh", pMesh.Get());

	// ==============
	// RectMesh_Debug
	// ==============
	UINT arrIdx_DBG[5] = { 0, 1, 2, 3, 0 };

	pMesh = new AMesh;
	pMesh->Create(arrVtx, 4, arrIdx_DBG, 5);
	AddAsset(L"RectMesh_Debug", pMesh.Get());

	// ==========
	// CircleMesh
	// ==========
	vector<Vtx> vecVtx;
	vector<UINT> vecIdx;

	// 원의 중심점
	Vtx v;
	v.vPos = Vec3(0.f, 0.f, 0.f);
	v.vUV = Vec2(0.5f, 0.5f);
	v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);

	UINT PolyCount = 40;
	float Radius = 0.5f;
	float Theta = 0.f;
	float Step = XM_2PI / PolyCount;

	for (UINT i = 0; i < PolyCount + 1; ++i)
	{
		v.vPos = Vec3(Radius * cosf(Theta), Radius * sinf(Theta), 0.f);

		float fLen = Radius - -Radius;
		v.vUV = Vec2(v.vPos.x / fLen + 0.5f, 1.f - (v.vPos.y / fLen + 0.5f));

		v.vColor = Vec4(1.f, 1.f, 1.f, 1.f);
		vecVtx.push_back(v);

		Theta += Step;
	}

	for (UINT i = 0; i < PolyCount; ++i)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	pMesh = new AMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh", pMesh.Get());

	// ================
	// CircleMesh_Debug
	// ================
	vecIdx.clear();
	for (int i = 0; i < PolyCount + 1; ++i)
	{
		vecIdx.push_back(i + 1);
	}

	pMesh = new AMesh;
	pMesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset(L"CircleMesh_Debug", pMesh.Get());
}


void AssetMgr::CreateEngineGraphicShader()
{
	Ptr<AGraphicShader> pShader = nullptr;

	// ===========
	// Std2DShader
	// ===========
	pShader = new AGraphicShader;
	pShader->CreateVertexShader(L"HLSL\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"HLSL\\std2d.fx", "PS_Std2D");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::LESS);
	pShader->SetBSType(BS_TYPE::DEFAULT);
	AddAsset(L"Std2DShader", pShader.Get());

	// ======================
	// Std2DShader_AlphaBlend
	// ======================
	pShader = new AGraphicShader;
	pShader->CreateVertexShader(L"HLSL\\std2d.fx", "VS_Std2D");
	pShader->CreatePixelShader(L"HLSL\\std2d.fx", "PS_Std2D");
	pShader->SetRSType(RS_TYPE::CULL_NONE);
	pShader->SetDSType(DS_TYPE::NO_WRITE);
	pShader->SetBSType(BS_TYPE::ALPHABLEND);
	AddAsset(L"Std2DShader_AlphaBlend", pShader.Get());
}

void AssetMgr::CreateEngineMaterial()
{
	Ptr<AMaterial> pMtrl = nullptr;

	// =========
	// Std2DMtrl
	// =========
	pMtrl = new AMaterial;
	pMtrl->SetShader(Find<AGraphicShader>(L"Std2DShader"));
	pMtrl->SetDomain(RENDER_DOMAIN::DOMAIN_MASKED);
	AddAsset(L"Std2DMtrl", pMtrl.Get());

	// ===================
	// Std2DAlphaBlendMtrl
	// ===================
	pMtrl = new AMaterial;
	pMtrl->SetShader(Find<AGraphicShader>(L"Std2DShader_AlphaBlend"));
	pMtrl->SetDomain(RENDER_DOMAIN::DOMAIN_TRANSPARENT);
	AddAsset(L"Std2DAlphaBlendMtrl", pMtrl.Get());
}

void AssetMgr::CreateEngineTexture()
{
	Load<ATexture>(L"MarioAtlas", L"Texture\\MarioAtlas.png");
	Load<ATexture>(L"LinkAtlas", L"Texture\\Link.png");

}

void AssetMgr::CreateEngineSprite()
{
	/*Load<ASprite>(L"Tile_00", L"Sprite\\Tile_00.sprite");
	Load<ASprite>(L"Tile_01", L"Sprite\\Tile_01.sprite");

	for (int i = 0; i < 10; ++i)
	{
		wchar_t szKey[255] = {};
		swprintf_s(szKey, 255, L"LinkMD_%d", i);

		wstring Path = L"Sprite\\";
		Load<ASprite>(szKey, Path + szKey + L".sprite");
	}*/
	
	
	//wstring ContentPath = PathMgr::GetInst()->GetContentPath();
	//
	//Ptr<ATexture> pAtlas = Find<ATexture>(L"MarioAtlas");

	//// Sprite 생성
	//Ptr<ASprite> pSprite = new ASprite;
	//pSprite->SetAtlas(pAtlas);
	//pSprite->SetBackgroundUV(Vec2(100.f, 100.f));
	//pSprite->SetLeftTopUV(Vec2(10.f, 10.f));
	//pSprite->SetSliceUV(Vec2(17.f, 20.f));
	//pSprite->SetOffsetUV(Vec2(30.f, 0.f));
	//AddAsset(L"Tile_00", pSprite.Get());
	//pSprite->Save(ContentPath + L"Sprite\\Tile_00.sprite");

	//pSprite = new ASprite;
	//pSprite->SetAtlas(pAtlas);
	//pSprite->SetBackgroundUV(Vec2(100.f, 100.f));
	//pSprite->SetLeftTopUV(Vec2(250.f, 60.f));
	//pSprite->SetSliceUV(Vec2(30.f, 30.f));
	//pSprite->SetOffsetUV(Vec2(30.f, 0.f));
	//AddAsset(L"Tile_01", pSprite.Get());
	//pSprite->Save(ContentPath + L"Sprite\\Tile_01.sprite");


	//// Link Sprite
	//pAtlas = Find<ATexture>(L"LinkAtlas");

	//for (int i = 0; i < 10; ++i)
	//{
	//	pSprite = new ASprite;
	//	pSprite->SetAtlas(pAtlas);
	//	pSprite->SetBackgroundUV(Vec2(200.f, 200.f));
	//	pSprite->SetLeftTopUV(Vec2(i * 120.f, 520.f));
	//	pSprite->SetSliceUV(Vec2(120.f, 130.f));
	//	pSprite->SetOffsetUV(Vec2(0.f, 0.f));

	//	wchar_t szKey[255] = {};
	//	swprintf_s(szKey, 255, L"LinkMD_%d", i);

	//	AddAsset(szKey, pSprite.Get());
	//	
	//	pSprite->Save(ContentPath + L"Sprite\\" + pSprite->GetKey() + L".sprite");
	//}
}

void AssetMgr::CreateEngineFlipbook()
{
	Load<AFlipbook>(L"LinkMD", L"Flipbook\\LinkMD.flip");

	//Ptr<AFlipbook> pFlipbook = new AFlipbook;

	//for (int i = 0; i < 10; ++i)
	//{
	//	wchar_t szKey[255] = {};
	//	swprintf_s(szKey, 255, L"LinkMD_%d", i);

	//	pFlipbook->AddSprite(Find<ASprite>(szKey));
	//}

	//AddAsset(L"LinkMD", pFlipbook.Get());

	//wstring ContentPath = CONTENT_PATH;
	//pFlipbook->Save(CONTENT_PATH + L"Flipbook\\" + pFlipbook->GetKey() + L".flip");
}

#include "GameObject.h"
#include "components.h"
#include "CMissileScript.h"
void AssetMgr::CreateEnginePrefab()
{
	GameObject* pObject = new GameObject;
	pObject->SetName(L"Missile");

	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CMeshRender);
	pObject->AddComponent(new CCollider2D);
	pObject->AddComponent(new CMissileScript);

	pObject->Transform()->SetRelativeScale(Vec3(50.f, 65.f, 1.f));
	pObject->Collider2D()->SetScale(Vec2(0.4f, 0.85f));
	pObject->MeshRender()->SetMesh(FIND(AMesh, L"RectMesh"));

	Ptr<AMaterial> pMtrl = FIND(AMaterial, L"MissileMtrl");
	if (nullptr == pMtrl)
	{
		pMtrl = new AMaterial;
		pMtrl->SetDomain(RENDER_DOMAIN::DOMAIN_MASKED);
		pMtrl->SetShader(FIND(AGraphicShader, L"Std2DShader"));
		pMtrl->SetTexture(TEX_0, LOAD(ATexture, L"Missile", L"Texture\\missile.png"));
		AssetMgr::GetInst()->AddAsset(L"MissileMtrl", pMtrl.Get());
	}

	pObject->MeshRender()->SetMaterial(pMtrl);

	Ptr<APrefab> pMissilePrefab = new APrefab;
	pMissilePrefab->RegitserObject(pObject);
	AddAsset(L"MissilePref", pMissilePrefab.Get());
}