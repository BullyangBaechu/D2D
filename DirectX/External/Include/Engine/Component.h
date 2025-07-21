#pragma once
#include "Entity.h"

class Component :
    public Entity
{
private:
    const COMPONENT_TYPE    m_Type;
    class GameObject*       m_Owner;

public:
    GET(COMPONENT_TYPE, Type);
    GET(GameObject*, Owner);

    class CTransform* Transform();
    class CCamera* Camera();
    class CMeshRender* MeshRender();    
    class CCollider2D* Collider2D();
    class CSpriteRender* SpriteRender();
    class CFlipbookRender* FlipbookRender();

    bool IsDead();
public:
    virtual void Begin() {}
    virtual void FinalTick() = 0;
    virtual Component* Clone() = 0;

public:
    Component(COMPONENT_TYPE _Type);
    Component(const Component& _Origin);
    virtual ~Component();

    friend class GameObject;
};


