#pragma once

#include "projection.h"
#include "../gui.h"

class ProjectionGUI : public RendererGUI
{
	ProjectionGUI();
	ProjectionGUI(const ProjectionGUI& );
	ProjectionGUI& operator=(const ProjectionGUI& );

	ProjectionRenderer *renderer;

public:
	ProjectionGUI(ProjectionRenderer*);
	virtual ~ProjectionGUI();
	
	virtual QString name() const { return "1D Projection"; }

signals:
	
public slots:
	
};
