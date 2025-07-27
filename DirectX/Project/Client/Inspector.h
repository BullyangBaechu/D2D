#pragma once
#include "EUI.h"

#include <Engine/GameObject.h>

class ComponentUI;

class Inspector :
    public EUI
{
private:
    Ptr<GameObject>     m_TargetObject;
    ComponentUI*        m_arrComUI[(UINT)COMPONENT_TYPE::END];          // 인스펙터가 대응할 Component들의 집합(추후 새로 생길 Component에도 능동적으로 대응 가능한 다형성 구조)


public:
    void SetTargetObject(GameObject* _Object);
   

private:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

public:
    Inspector();
    virtual ~Inspector();
};

