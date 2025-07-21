#pragma once
#include "Asset.h"

#include "GameObject.h"

// 미리 제작이 완료된 하나의 게임 오브젝트를 에셋으로 취급
// 프로토타입 패턴
class APrefab :
    public Asset
{
private:
    Ptr<GameObject>     m_ProtoObj;
    
public:
    void RegitserObject(GameObject* _Object) { m_ProtoObj = _Object; }
    GameObject* Instantiate() { return m_ProtoObj->Clone(); }


public:
    virtual int Save(const wstring& _FilePath) override { return S_OK; };
    virtual int Load(const wstring& _FilePath) override { return S_OK; };

public:
    CLONE(APrefab);
    APrefab();
    APrefab(const APrefab& _Origin);
    virtual ~APrefab();
};

