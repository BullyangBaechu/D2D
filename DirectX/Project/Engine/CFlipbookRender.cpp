#include "pch.h"
#include "CFlipbookRender.h"

#include "AssetMgr.h"
#include "CTransform.h"
#include "TimeMgr.h"

CFlipbookRender::CFlipbookRender()
	: CRenderComponent(COMPONENT_TYPE::FLIPBOOK_RENDER)
	, m_SpriteIdx(0)
	, m_RepeatCount(0)
	, m_Finish(false)
	, m_FPS(0.f)
	, m_Time(0.f)
{
	SetMesh(AssetMgr::GetInst()->Find<AMesh>(L"RectMesh"));

	CreateMaterial();
}

CFlipbookRender::~CFlipbookRender()
{
}

void CFlipbookRender::FinalTick()
{
	// 1회 재생이 완료된 시점
	if (m_Finish)
	{
		// 남은 재생횟수가 없는 경우
		if (m_RepeatCount == 0)
			return;

		// 1회 재생이 끝났지만 아직 재생횟수가 더 남았거나 m_RepeatCount == -1 무한반복인 경우
		else if (0 < m_RepeatCount || m_RepeatCount == -1)
		{
			// 다시 Sprite 를 시작점으로 돌려서 다음 회차 재생을 이어간다.
			m_Finish = false;
			m_SpriteIdx = 0;
		}
	}


	


	// 현재 재생할 Sprite 를 가져온다.
	Ptr<ASprite> pCurSprite = m_CurFlipbook->GetSprite(m_SpriteIdx);

	// Flipbook 을 구성하고있는 Sprite 의 개수를 체크한다.
	UINT MaxSprite = m_CurFlipbook->GetSpriteCount();

	// Sprite 가 화면에 노출되는 시간
	float Duration = 1.f / m_FPS;

	// 제한시간을 넘기면, 다음 Sprite 를 화면에 출력할 수 있도록 SpriteIndex 를 증가시킨다.
	m_Time += DT;
	if (Duration <= m_Time)
	{
		++m_SpriteIdx;
		m_Time -= Duration;

		if(m_SpriteIdx == MaxSprite)
		{
			m_Finish = true;
			--m_SpriteIdx;

			if (0 < m_RepeatCount)
				--m_RepeatCount;
		}
	}
}

void CFlipbookRender::Render()
{
	if (nullptr == m_CurFlipbook)
		return;

	Transform()->Binding();


	Ptr<ASprite> pCurSprite = m_CurFlipbook->GetSprite(m_SpriteIdx);

	// Sprite 정보를 재질에 세팅한다.
	GetMaterial()->SetTexture(TEX_0, pCurSprite->GetAtlas());

	GetMaterial()->SetScalar(VEC2_0, pCurSprite->GetLeftTopUV());
	GetMaterial()->SetScalar(VEC2_1, pCurSprite->GetSliceUV());
	GetMaterial()->SetScalar(VEC2_2, pCurSprite->GetOffsetUV());
	GetMaterial()->SetScalar(VEC2_3, pCurSprite->GetBackgroundUV());

	GetMaterial()->Binding();

	GetMesh()->Render();
}

void CFlipbookRender::AddFlipbook(UINT _Idx, Ptr<AFlipbook> _Flipbook)
{
	if (m_vecFlipbook.size() <= _Idx)
	{
		m_vecFlipbook.resize(_Idx + 1);
	}

	m_vecFlipbook[_Idx] = _Flipbook;
}

void CFlipbookRender::Play(UINT _Idx, float _FPS, int _RepeatCount)
{
	m_CurFlipbook = m_vecFlipbook[_Idx];
	m_SpriteIdx = 0;
	m_FPS = _FPS;
	m_RepeatCount = _RepeatCount;
	m_Finish = false;
	m_Time = 0.f;
}

void CFlipbookRender::CreateMaterial()
{
	wstring strMtrlKey = L"FlipbookMtrl";
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