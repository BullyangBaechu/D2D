#pragma once
#include "EUI.h"

#include <Engine/GameObject.h>

class ComponentUI;

class Inspector :
    public EUI
{
private:
    Ptr<GameObject>     m_TargetObject;
    ComponentUI*        m_arrComUI[(UINT)COMPONENT_TYPE::END];


public:
    void SetTargetObject(GameObject* _Object);
   

private:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

public:
    Inspector();
    virtual ~Inspector();
};

