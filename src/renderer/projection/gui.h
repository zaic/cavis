#pragma once

#include <QSpinBox>
//#include "projection.h"
#include "../renderer.h"
#include "../gui.h"

class ProjectionRenderer;

class ProjectionGUI : public RendererGUI
{
	Q_OBJECT

	ProjectionGUI();
	ProjectionGUI(const ProjectionGUI& );
	ProjectionGUI& operator=(const ProjectionGUI& );

	//ProjectionRenderer *renderer;
	QSpinBox *x_scale;
	QSpinBox *y_scale;

	void builMainWidget();

	friend class ProjectionRenderer;

public:
	ProjectionGUI(Renderer*);
	virtual ~ProjectionGUI();
	
	virtual QString getName() const { return tr("1D Projection"); }

signals:
	
public slots:

};
