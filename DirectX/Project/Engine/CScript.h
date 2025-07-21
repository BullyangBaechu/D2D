#pragma once
#include "Component.h"

#include "KeyMgr.h"
#include "TimeMgr.h"
#include "AssetMgr.h"

#include "CCollider2D.h"

class CScript :
    public Component
{
private:
    Ptr<ATexture>   m_Tex;

public:
    void Destroy();

protected:
    void Instantiate(class APrefab* _Prefab, Vec3 _WorldPos, int _LayerIdx);

public:
    virtual void Tick() = 0;
    virtual void FinalTick() final {};

    virtual void BeginOverlap(CCollider2D* _OwnCollider, CCollider2D* _Collider2D, GameObject* _OtherObj) {}
    virtual void Overlap(CCollider2D* _OwnCollider, CCollider2D* _Collider2D, GameObject* _OtherObj) {}
    virtual void EndOverlap(CCollider2D* _OwnCollider, CCollider2D* _Collider2D, GameObject* _OtherObj) {}

public:
    virtual CScript* Clone() = 0;
    CScript();
    virtual ~CScript();
};

