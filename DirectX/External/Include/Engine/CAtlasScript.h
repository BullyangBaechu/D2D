#pragma once
#include "CScript.h"
class CAtlasScript :
    public CScript
{
private:
    Vec2    m_PixelPos;

public:
    virtual void Tick() override;

public:
    CLONE(CAtlasScript);
    CAtlasScript();
    virtual ~CAtlasScript();
};

