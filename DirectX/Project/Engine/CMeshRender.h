#pragma once
#include "CRenderComponent.h"

class CMeshRender :
    public CRenderComponent
{
private:

public:
    virtual void FinalTick() override;
    virtual void Render() override;    

public:
    CLONE(CMeshRender);
    CMeshRender();
    virtual ~CMeshRender();
};

