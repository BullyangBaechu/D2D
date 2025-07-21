#pragma once
#include "Entity.h"

class ConstBuffer :
    public Entity
{
private:
    D3D11_BUFFER_DESC       m_CBDesc;
    ComPtr<ID3D11Buffer>    m_CB;
    const CB_TYPE           m_Type;

public:
    int Create(UINT _BufferSize);
    void SetData(void* _SysMem, UINT _DataSize);
    void Binding();

public:
    CLONE_DISABLE(ConstBuffer);
    ConstBuffer(CB_TYPE _Type);
    virtual ~ConstBuffer();
};