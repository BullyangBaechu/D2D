#pragma once
#include "CScript.h"


class CMissileScript :
    public CScript
{
private:
    float   m_Speed;

public:
    virtual void Tick() override;
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CCollider2D* _Collider2D, GameObject* _OtherObj) override;

public:
    CLONE(CMissileScript);
    CMissileScript();
    virtual ~CMissileScript();
};

