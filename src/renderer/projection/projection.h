#pragma once

#include <QtGui>
#include <root/Math/Interpolator.h>
#include "renderer/renderer.h"
#include "common.h"
#include <algorithm>
#include <vector>
#include "gui.h"

using std::min;
using std::max;
using std::vector;
using ROOT::Math::Interpolator;

class ProjectionRenderer : public Renderer
{
    Q_OBJECT

    ProjectionRenderer(const ProjectionRenderer& );
    ProjectionRenderer& operator=(const ProjectionRenderer& );

    ProjectionGUI *parameters;

    static const int FRAME_SIZE = 50;       // размер рамки с линейкой
    const int XSCROLL_SIZE = 100;    // шаг скроллинга по x
    static const int XGRID_STEP = 100;      // шаг рисования делений на оси Х
    const int YSCROLL_SIZE = 100;
    // ?

public:
    ProjectionRenderer();
    virtual ~ProjectionRenderer();

    virtual void setParameters(RendererGUI *_parameters) { parameters = qobject_cast<ProjectionGUI*>(_parameters); }

    virtual void draw();
};
