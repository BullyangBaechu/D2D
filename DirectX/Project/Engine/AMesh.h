#pragma once
#include "Asset.h"

class AMesh :
    public Asset
{
private:
    ComPtr<ID3D11Buffer>    m_VB;
    D3D11_BUFFER_DESC       m_VBDesc;
    UINT                    m_VtxCount;
    Vtx*                    m_VtxSysMem;

    ComPtr<ID3D11Buffer>    m_IB;
    D3D11_BUFFER_DESC       m_IBDesc;
    UINT                    m_IdxCount;
    UINT*                   m_IdxSysMem;

public:
    int Create(Vtx* _VtxMem, UINT _VtxCount, UINT* _IdxMem, UINT _IdxCount);
    void Binding();
    void Render();

    const Vtx* GetVtxSysyMem() const { return m_VtxSysMem; }
    const UINT* GetIdxSysMem() const { return m_IdxSysMem; }

public:
    virtual int Save(const wstring& _FilePath) override { return S_OK; };
    virtual int Load(const wstring& _FilePath) override { return S_OK; };

public:
    CLONE(AMesh);
    AMesh();
    AMesh(const AMesh& _Origin);
    virtual ~AMesh();
};

