#pragma once

#include <QDebug>
#include "../renderer.h"
#include "../gui.h"
#include <algorithm>

using std::min;

class ProjectionRenderer : public Renderer
{
	ProjectionRenderer(const ProjectionRenderer& );
	ProjectionRenderer& operator=(const ProjectionRenderer& );

	double last_value;
	int buffer_using_width;

public:
	ProjectionRenderer();
	virtual ~ProjectionRenderer();

	virtual void init(Config *_config = NULL, GraphicBuffer *_buffer = NULL);
	virtual void draw(int x, int y);
	virtual void finalize();
};
