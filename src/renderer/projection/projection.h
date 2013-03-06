#pragma once

#include <QDebug>
#include <root/Math/Interpolator.h>
#include "../renderer.h"
#include "../../common.h"
#include <algorithm>
#include <vector>
#include "gui.h"

using std::min;
using std::max;
using std::vector;
using ROOT::Math::Interpolator;

class ProjectionRenderer : public Renderer
{
	ProjectionRenderer(const ProjectionRenderer& );
	ProjectionRenderer& operator=(const ProjectionRenderer& );

	ProjectionGUI *parameters;

public:
	ProjectionRenderer();
	virtual ~ProjectionRenderer();

	virtual void setParameters(RendererGUI *_parameters) { parameters = qobject_cast<ProjectionGUI*>(_parameters); }

	virtual void draw();
};
