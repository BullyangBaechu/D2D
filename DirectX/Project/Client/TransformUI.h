#pragma once
#include "ComponentUI.h"


class TransformUI :
    public ComponentUI
{
private:

private:
    virtual void Tick_UI() override;
    virtual void  Render_UI() override;

public:
    TransformUI();
    virtual ~TransformUI();
};

