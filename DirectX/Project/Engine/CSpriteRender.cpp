#include "pch.h"
#include "CSpriteRender.h"

#include "AssetMgr.h"
#include "CTransform.h"

CSpriteRender::CSpriteRender()
	: CRenderComponent(COMPONENT_TYPE::SPRITE_RENDER)
{
	SetMesh(AssetMgr::GetInst()->Find<AMesh>(L"RectMesh"));

	CreateMaterial();
}

CSpriteRender::~CSpriteRender()
{
}


void CSpriteRender::FinalTick()
{
}

void CSpriteRender::Render()
{
	if (nullptr == m_Sprite)
		return;

	Transform()->Binding();

	// Sprite 정보를 재질에 세팅한다.
	GetMaterial()->SetTexture(TEX_0, m_Sprite->GetAtlas());

	GetMaterial()->SetScalar(VEC2_0, m_Sprite->GetLeftTopUV());
	GetMaterial()->SetScalar(VEC2_1, m_Sprite->GetSliceUV());
	GetMaterial()->SetScalar(VEC2_2, m_Sprite->GetOffsetUV());
	GetMaterial()->SetScalar(VEC2_3, m_Sprite->GetBackgroundUV());

	GetMaterial()->Binding();

	GetMesh()->Render();
}

void CSpriteRender::CreateMaterial()
{
	wstring strMtrlKey = L"SpriteMtrl";
	wstring strShaderKey = L"SpriteShader";

	Ptr<AMaterial> pMtrl = AssetMgr::GetInst()->Find<AMaterial>(strMtrlKey);

	if (nullptr == pMtrl)
	{
		Ptr<AGraphicShader> pShader = AssetMgr::GetInst()->Find<AGraphicShader>(strShaderKey);

		if (nullptr == pShader)
		{
			pShader = new AGraphicShader;
			pShader->CreateVertexShader(L"HLSL\\sprite.fx", "VS_Sprite");
			pShader->CreatePixelShader(L"HLSL\\sprite.fx", "PS_Sprite");
			pShader->SetRSType(RS_TYPE::CULL_NONE);
			pShader->SetDSType(DS_TYPE::LESS);
			pShader->SetBSType(BS_TYPE::DEFAULT);
			AssetMgr::GetInst()->AddAsset(strShaderKey, pShader.Get());
		}

		pMtrl = new AMaterial;
		pMtrl->SetShader(pShader);
		pMtrl->SetDomain(RENDER_DOMAIN::DOMAIN_MASKED);
		AssetMgr::GetInst()->AddAsset(strMtrlKey, pMtrl.Get());
	}

	SetMaterial(pMtrl);
}