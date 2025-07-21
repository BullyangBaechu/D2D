#pragma once
#include "ComponentUI.h"

class CameraUI :
    public ComponentUI
{
private:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

public:
    CameraUI();
    virtual ~CameraUI();
};

