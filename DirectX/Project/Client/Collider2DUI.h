#pragma once
#include "ComponentUI.h"
class Collider2DUI :
    public ComponentUI
{
private:

public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

public:
    Collider2DUI();
    virtual ~Collider2DUI();
};

