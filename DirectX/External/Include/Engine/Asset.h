#pragma once
#include "Entity.h"

class Asset :
    public Entity
{
private:
    const ASSET_TYPE    m_Type;
    wstring             m_RelativePath;
    wstring             m_Key;

public:
    GET(wstring, RelativePath);
    GET(wstring, Key);
    GET(ASSET_TYPE, Type);

protected:
    SET(wstring, RelativePath);
    SET(wstring, Key);

public:
    virtual int Save(const wstring& _FilePath) = 0;
    virtual int Load(const wstring& _FilePath) = 0;

public:
    virtual Asset* Clone() = 0;
    Asset(ASSET_TYPE _Type);
    Asset(const Asset& _Origin);
    virtual ~Asset();

    friend class AssetMgr;
};

