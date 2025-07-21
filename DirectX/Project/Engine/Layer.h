#pragma once
#include "Entity.h"

#include "GameObject.h"

class Layer :
    public Entity
{
private:
    vector<Ptr<GameObject>> m_vecParents;   // Layer 에 속한 Object 중에서 최상위 부모만
    vector<Ptr<GameObject>> m_vecObjects;   // Layer 에 속한 모든 Object 들(최상위 부모, 자식 타입), 매 프레임마다 갱신됨
    int                     m_LayerIdx;     // Layer 본인의 Index ( 0 ~ 31 )

public:
    const vector<Ptr<GameObject>>& GetParentObjects() { return  m_vecParents; }
    const vector<Ptr<GameObject>>& GetObjects() { return  m_vecObjects; }

    
    void AddObject(GameObject* _Object, bool _MoveWithChild);
    void RegisterObject(GameObject* _Object) { m_vecObjects.push_back(_Object); }

public:
    void Begin();
    void Tick();
    void FinalTick();

public:
    CLONE(Layer);
public:
    Layer(int _Idx);
    Layer(const Layer& _Origin);
    virtual ~Layer();

    friend class ALevel;
};

