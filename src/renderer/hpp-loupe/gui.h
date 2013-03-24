#pragma once

#include <QtWidgets>
#include "hpploupe.h"
#include "renderer/gui.h"
#include "windowevent.h"

class HPPLoupeGUI : public RendererGUI {
    Q_OBJECT

    HPPLoupeGUI();
    HPPLoupeGUI(const HPPLoupeGUI& );
    HPPLoupeGUI& operator=(const HPPLoupeGUI& );

    HPPLoupeRenderer *renderer;
    QCheckBox *chk_autoscale;
    QSpinBox *spn_scale;

    void buildMainWidget();

public:
    HPPLoupeGUI(HPPLoupeRenderer*);
    virtual ~HPPLoupeGUI();

    virtual QString getName() const { return QString("HPP Loupe"); }

public slots:
    void autoscaleToggled(bool value);
    void scaleChanged(int value);
};
