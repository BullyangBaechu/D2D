#pragma once
#include "CScript.h"

class CPlayerScript :
    public CScript
{
private:
    float           m_Speed;
    Ptr<APrefab>    m_MissilePref;


public:
    virtual void Begin() override;
    virtual void Tick() override;
    virtual void BeginOverlap(CCollider2D* _OwnCollider, CCollider2D* _Collider2D, GameObject* _OtherObj) override;

private:
    void Shoot();

public:
    CLONE(CPlayerScript);
    CPlayerScript();
    virtual ~CPlayerScript();
};

