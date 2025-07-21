#pragma once
#include "Asset.h"

#include "ASprite.h"

class AFlipbook :
    public Asset
{
private:
    vector<Ptr<ASprite>>    m_vecSprites;

public:
    void AddSprite(Ptr<ASprite> _Sprite) { m_vecSprites.push_back(_Sprite); }
    Ptr<ASprite> GetSprite(UINT _Idx) { return m_vecSprites[_Idx]; }
    UINT GetSpriteCount() { return m_vecSprites.size(); }


public:
    virtual int Save(const wstring& _FilePath) override;
    virtual int Load(const wstring& _FilePath) override;

public:
    CLONE(AFlipbook);
    AFlipbook();
    virtual ~AFlipbook();
};

