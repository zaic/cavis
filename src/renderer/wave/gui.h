#pragma once

#include "renderer/renderer.h"
#include "renderer/gui.h"
#include "windowevent.h"

class WaveRenderer;

class WaveGUI : public RendererGUI
{
    Q_OBJECT

    WaveGUI();
    WaveGUI(const WaveGUI& );
    WaveGUI& operator=(const WaveGUI& );

    void buildMainWidget();

    friend class WaveRenderer;

public:
    WaveGUI(Renderer *_renderer);
    virtual ~WaveGUI();

    virtual QString getName() const override { return tr("Wave 3D"); }
};
