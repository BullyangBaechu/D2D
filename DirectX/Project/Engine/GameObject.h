#pragma once
#include "Entity.h"
#include "components.h"

#define GET_COMOPNENT(Type, ComponentType) Ptr<C##Type> Type() { return (C##Type*)GetComponent(COMPONENT_TYPE::ComponentType).Get();}

class GameObject :
    public Entity
{
private:
    Ptr<Component>              m_arrCom[(UINT)COMPONENT_TYPE::END];
    Ptr<CRenderComponent>       m_RenderCom;
    vector<Ptr<CScript>>        m_vecScripts;
    int                         m_LayerIdx; // ������Ʈ�� ���� Layer (-1 �� ���, �����ȿ� �ִ� ������Ʈ�� �ƴϴ�)

    GameObject*                 m_Parent;   // �θ� ������Ʈ(nullptr �� ���, ������ �ֻ��� �θ� ������Ʈ)
    vector<Ptr<GameObject>>     m_vecChild; // �ڽ� ������Ʈ��

    bool                        m_Dead;     // ���� �������� üũ

public:
    void Begin();
    void Tick();
    void FinalTick();
    void Render();

public:
    void AddComponent(Ptr<Component> _Com);
    Ptr<Component> GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }
    Ptr<CRenderComponent> GetRenderComponent() { return m_RenderCom; }

    void AddChild(Ptr<GameObject> _Object)
    {
        m_vecChild.push_back(_Object);
        _Object->m_Parent = this;
    }

    Ptr<GameObject> GetParent() { return m_Parent; }
    const vector<Ptr<CScript>>& GetScripts() { return m_vecScripts; }

    bool IsDead() { return m_Dead; }
    void Destroy();


    GET(int, LayerIdx);
    GET_COMOPNENT(Transform, TRANSFORM);
    GET_COMOPNENT(Camera, CAMERA);
    GET_COMOPNENT(MeshRender, MESHRENDER);
    GET_COMOPNENT(Collider2D, COLLIDER2D);
    GET_COMOPNENT(SpriteRender, SPRITE_RENDER);
    GET_COMOPNENT(FlipbookRender, FLIPBOOK_RENDER);


public:
    CLONE(GameObject);
public:
    GameObject();
    GameObject(const GameObject& _Origin);
    virtual ~GameObject();

    friend class Layer;
    friend class TaskMgr;
};

