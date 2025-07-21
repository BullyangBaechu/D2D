#pragma once
#include "EUI.h"
class ComponentUI :
    public EUI
{
private:
    class GameObject*       m_TargetObject;
    const COMPONENT_TYPE    m_Type;

public:
    void SetTarget(GameObject* _Target);
    GameObject* GetTarget() { return m_TargetObject; }

protected:
    void OutputTitle();

public:
    ComponentUI(COMPONENT_TYPE _Type);
    virtual ~ComponentUI();
};

