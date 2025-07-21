#pragma once
#include "Asset.h"

#include "Layer.h"

class GameObject;

class ALevel :
    public Asset
{
private:
    Ptr<Layer>  m_Layer[MAX_LAYER];

public:
    void Begin();
    void Tick();
    void FinalTick();

public:
    // _MoveWithChild: GameObject 가 보유한 자식 오브젝트도 같이 레이어에 추가될 것인지
    void AddObject(int _LayerIdx, GameObject* _Object, bool _MoveWithChild);
    Ptr<Layer> GetLayer(int _LayerIdx) { return m_Layer[_LayerIdx]; }

private:
    // 등록된것을 취소, Unregister 등록을 취소(등록된적 없음)
    void Deregister();
    GameObject* FindObjectByName(const wstring& _Name);

public:
    virtual int Save(const wstring& _FilePath) override { return S_OK; }
    virtual int Load(const wstring& _FilePath) override { return S_OK; }

    virtual ALevel* Clone() override
    {
        // Default 복사생성자
        // 맴버간의 단순복사, 얕은 복사(Swallow Copy)
        // ==> 직접 복사생성자를 구현(Deep Copy)
        return new ALevel(*this);
    }
public:
    ALevel();
    ALevel(const ALevel& _Origin);
    virtual ~ALevel();

    friend class LevelMgr;
};

