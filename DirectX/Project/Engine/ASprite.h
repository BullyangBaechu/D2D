#pragma once
#include "Asset.h"


#include "ATexture.h"


class ASprite :
    public Asset
{
private:
    Ptr<ATexture>   m_Atlas;
    Vec2            m_BackgroundUV;
    Vec2            m_LeftTopUV;
    Vec2            m_SliceUV;
    Vec2            m_OffsetUV;

public:
    GET_SET(Ptr<ATexture>, Atlas);

    Vec2 GetBackgroundUV() { return m_BackgroundUV; }
    void SetBackgroundUV(Vec2 _PixelPos);
    Vec2 GetBackgroundPixel();


    Vec2 GetLeftTopUV() { return m_LeftTopUV; }
    void SetLeftTopUV(Vec2 _PixelPos);
    Vec2 GetLeftTopPixel();

    Vec2 GetSliceUV() { return m_SliceUV; }
    void SetSliceUV(Vec2 _PixelPos);
    Vec2 GetSlicePixel();

    Vec2 GetOffsetUV() { return m_OffsetUV; }
    void SetOffsetUV(Vec2 _PixelPos);
    Vec2 GetOffsetPixel();


public:
    virtual int Save(const wstring& _FilePath) override ;
    virtual int Load(const wstring& _FilePath) override ;

public:
    CLONE(ASprite)
    ASprite();
    virtual ~ASprite();
};

