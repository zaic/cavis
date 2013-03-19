#pragma once

#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <algorithm>
#include "../renderer.h"
#include "../gui.h"
#include "../../common.h"

using std::max;

class ProjectionRenderer;

class ProjectionGUI : public RendererGUI
{
    Q_OBJECT

    ProjectionGUI();
    ProjectionGUI(const ProjectionGUI& );
    ProjectionGUI& operator=(const ProjectionGUI& );

    QSpinBox *x_scale;
    QSpinBox *y_scale;
	QCheckBox *chk_interpolation, *chk_segments;

    void buildMainWidget();
    QHBoxLayout* buildScalePanel(QSpinBox*&, const char *);

    friend class ProjectionRenderer;

public:
    ProjectionGUI(Renderer*);
    virtual ~ProjectionGUI();

    virtual QString getName() const { return tr("1D Projection"); }

signals:

public slots:

};
