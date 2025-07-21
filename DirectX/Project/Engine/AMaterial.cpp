#include "pch.h"
#include "AMaterial.h"

#include "Device.h"
#include "ConstBuffer.h"

AMaterial::AMaterial()
	: Asset(ASSET_TYPE::MATERIAL)
	, m_Const{}
	, m_Domain(RENDER_DOMAIN::DOMAIN_MASKED)
{
}

AMaterial::~AMaterial()
{
}

void AMaterial::Binding()
{
	m_Shader->Binding();

	for (UINT i = 0; i < TEX_END; ++i)
	{
		if (nullptr == m_arrTex[i])
		{
			ATexture::Clear(i);
		}
		else
		{
			m_arrTex[i]->Binding(i);
		}
	}	

	Ptr<ConstBuffer> pCB = Device::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pCB->SetData(&m_Const, sizeof(tMtrlConst));
	pCB->Binding();
}
