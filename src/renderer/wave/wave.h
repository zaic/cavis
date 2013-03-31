#pragma once

#include "renderer/renderer.h"
#include "gui.h"

class WaveRenderer : public Renderer
{
    WaveRenderer(const WaveRenderer& );
    WaveRenderer& operator=(const WaveRenderer& );

    WaveGUI *parameters;

public:
    WaveRenderer();
    virtual ~WaveRenderer();

    virtual void setParameters(RendererGUI *_parameters) override { parameters = qobject_cast<WaveGUI*>(_parameters); }

    virtual void draw() override;
    virtual QString getBufferFormat() const override { return "opengl"; }
};