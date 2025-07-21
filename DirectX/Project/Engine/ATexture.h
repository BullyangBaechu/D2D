#pragma once
#include "Asset.h"

class ATexture :
    public Asset
{
private:
    ScratchImage                        m_Image; // 텍스쳐를 SystemMemory 로 로딩
    ComPtr<ID3D11Texture2D>             m_Tex2D; // 텍스쳐를 GPU 메모리에 로딩
    D3D11_TEXTURE2D_DESC                m_Desc;  // Texture2D 설정 정보

    // View
    ComPtr<ID3D11RenderTargetView>      m_RTV;
    ComPtr<ID3D11DepthStencilView>      m_DSV;
    ComPtr<ID3D11ShaderResourceView>    m_SRV;
    ComPtr<ID3D11UnorderedAccessView>   m_UAV;

private:
    virtual int Save(const wstring& _FilePath) override { return S_OK; };
    virtual int Load(const wstring& _FilePath) override;

public:
    UINT GetWidth() { return m_Desc.Width; }
    UINT GetHeight() { return m_Desc.Height; }

    void Binding(UINT _RegisterNum);
    static void Clear(UINT _RegisterNum);


public:
    CLONE_DISABLE(ATexture);
    ATexture();
    virtual ~ATexture();

    friend class AssetMgr;
};

