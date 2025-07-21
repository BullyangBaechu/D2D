#pragma once

#include "CScript.h"

class CCamMoveScript :
    public CScript
{
private:
    float   m_Speed;

public:
    virtual void Tick() override;

private:
    void Move_Orthographic();
    void Move_Perspective();

public:
    CLONE(CCamMoveScript);
    CCamMoveScript();
    virtual ~CCamMoveScript();
};

