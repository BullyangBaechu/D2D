#pragma once
#include "Entity.h"

#include "GameObject.h"

class Layer :
    public Entity
{
private:
    vector<Ptr<GameObject>> m_vecParents;   // Layer �� ���� Object �߿��� �ֻ��� �θ�
    vector<Ptr<GameObject>> m_vecObjects;   // Layer �� ���� ��� Object ��(�ֻ��� �θ�, �ڽ� Ÿ��), �� �����Ӹ��� ���ŵ�
    int                     m_LayerIdx;     // Layer ������ Index ( 0 ~ 31 )

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

