#pragma once
#include "CRenderComponent.h"

#include "ASprite.h"

class CSpriteRender :
    public CRenderComponent
{
private:
    Ptr<ASprite>    m_Sprite;

public:
    GET_SET(Ptr<ASprite>, Sprite);


private:
    void CreateMaterial();

public:
    virtual void FinalTick() override;
    virtual void Render() override;

public:
    CLONE(CSpriteRender);
    CSpriteRender();
    virtual ~CSpriteRender();
};

