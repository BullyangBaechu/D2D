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
        MessageBox(nullptr, L"�ý��� �޸� �ε� ����", L"�ؽ��� �ε� ����", MB_OK);
        return E_FAIL;
    }    

    // SystemMemory -> GPU (Texture2D)
    // Texture2D -> View ����
    CreateShaderResourceView(DEVICE.Get(), m_Image.GetImages()
        , m_Image.GetImageCount(), m_Image.GetMetadata(), m_SRV.GetAddressOf());

    // ������ ShaderResourceView �� ���ؼ� Texture2D �ּҰ��� �˾Ƴ���.
    m_SRV->GetResource((ID3D11Resource**)m_Tex2D.GetAddressOf());

    // ������ Texture2D �� ���������� �˾Ƴ���
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
