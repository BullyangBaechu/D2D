#pragma once
#include "Component.h"

#include "AMesh.h"
#include "AMaterial.h"

class CRenderComponent :
    public Component
{
private:
    Ptr<AMesh>          m_Mesh;
    Ptr<AMaterial>      m_Mtrl;

public:
    GET_SET(Ptr<AMesh>, Mesh);

    Ptr<AMaterial> GetMaterial() { return m_Mtrl; }
    void SetMaterial(Ptr<AMaterial> _Mtrl) { m_Mtrl = _Mtrl; }

public:
    virtual void Render() = 0;
    virtual CRenderComponent* Clone() = 0;

public:
    CRenderComponent(COMPONENT_TYPE _Type);
    virtual ~CRenderComponent();
};

