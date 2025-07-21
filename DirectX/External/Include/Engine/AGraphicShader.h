#pragma once
#include "Asset.h"

// ������ ����������(��ü�ϳ��� �׸��� ����)

class AGraphicShader :
    public Asset
{
private:
    ComPtr<ID3DBlob>		    m_VSBlob;
    ComPtr<ID3DBlob>		    m_PSBlob;
    ComPtr<ID3DBlob>		    m_ErrBlob;

    ComPtr<ID3D11VertexShader>  m_VS;
    ComPtr<ID3D11PixelShader>   m_PS;
        
    ComPtr<ID3D11InputLayout>   m_Layout; // ������ �����ϴ� ������ ���� ����
    D3D11_PRIMITIVE_TOPOLOGY    m_Topology;

    RS_TYPE                     m_RSType;
    DS_TYPE                     m_DSType;
    BS_TYPE                     m_BSType;


public:
    void CreateVertexShader(const wstring& _HLSFilePath, const string& _FuncName);
    void CreatePixelShader(const wstring& _HLSFilePath, const string& _FuncName);
    GET_SET(D3D11_PRIMITIVE_TOPOLOGY, Topology);
    GET_SET(RS_TYPE, RSType);
    GET_SET(DS_TYPE, DSType);
    GET_SET(BS_TYPE, BSType);


    void Binding();

private:
    void CreateLayout();

    virtual int Save(const wstring& _FilePath) override { return S_OK; };
    virtual int Load(const wstring& _FilePath) override { return S_OK; }

public:
    CLONE_DISABLE(AGraphicShader);
    AGraphicShader();
    virtual ~AGraphicShader();
};

