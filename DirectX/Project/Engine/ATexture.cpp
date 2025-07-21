#include "pch.h"
#include "ATexture.h"

#include "Device.h"

ATexture::ATexture()
    : Asset(ASSET_TYPE::TEXTURE)
    , m_Desc{}
{
}

ATexture::~ATexture()
{
}

int ATexture::Load(const wstring& _FilePath)
{
    path Ext = path(_FilePath).extension();

    HRESULT hr = S_OK;

    // .dds .DDS
    if (Ext == L".dds" || Ext == L".DDS")
    {
        hr = LoadFromDDSFile(_FilePath.c_str(), DDS_FLAGS_NONE, nullptr, m_Image);
    }

    // .tga, .TGA
    else if (Ext == L".tga" || Ext == L".TGA")
    {
        hr = LoadFromTGAFile(_FilePath.c_str(), nullptr, m_Image);
    }

    // Window Image Component(jpg, jpeg, bmp, png)
    else
    {
        hr = LoadFromWICFile(_FilePath.c_str(), WIC_FLAGS_NONE, nullptr, m_Image);
    }

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"시스템 메모리 로딩 실패", L"텍스쳐 로딩 실패", MB_OK);
        return E_FAIL;
    }    

    // SystemMemory -> GPU (Texture2D)
    // Texture2D -> View 생성
    CreateShaderResourceView(DEVICE.Get(), m_Image.GetImages()
        , m_Image.GetImageCount(), m_Image.GetMetadata(), m_SRV.GetAddressOf());

    // 생성된 ShaderResourceView 를 통해서 Texture2D 주소값을 알아낸다.
    m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());

    // 생성된 Texture2D 의 생성정보를 알아낸다
    m_Tex2D->GetDesc(&m_Desc);

    return S_OK;
}

void ATexture::Binding(UINT _RegisterNum)
{
    CONTEXT->VSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
    CONTEXT->HSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
    CONTEXT->DSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
    CONTEXT->GSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
    CONTEXT->PSSetShaderResources(_RegisterNum, 1, m_SRV.GetAddressOf());
}

void ATexture::Clear(UINT _RegisterNum)
{
    ID3D11ShaderResourceView* pSRV = nullptr;

    CONTEXT->VSSetShaderResources(_RegisterNum, 1, &pSRV);
    CONTEXT->HSSetShaderResources(_RegisterNum, 1, &pSRV);
    CONTEXT->DSSetShaderResources(_RegisterNum, 1, &pSRV);
    CONTEXT->GSSetShaderResources(_RegisterNum, 1, &pSRV);
    CONTEXT->PSSetShaderResources(_RegisterNum, 1, &pSRV);
}
