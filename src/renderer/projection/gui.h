#pragma once

#include <QtWidgets>
#include <algorithm>
#include "../renderer.h"
#include "../gui.h"
#include "../../common.h"
#include "windowevent.h"

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

    void updateScale(QSpinBox *spn_scale, float multiplier);

    friend class ProjectionRenderer;

public:
    ProjectionGUI(Renderer*);
    virtual ~ProjectionGUI();

    virtual QString getName() const { return tr("1D Projection"); }

signals:

public slots:

};
