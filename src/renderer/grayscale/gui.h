#pragma once

#include <QtWidgets>
#include "grayscale.h"
#include "renderer/gui.h"

class GrayScaleGUI : public RendererGUI
{
    Q_OBJECT

    GrayScaleGUI();
    GrayScaleGUI(const GrayScaleGUI& );
    GrayScaleGUI& operator=(const GrayScaleGUI& );

    GrayScaleRenderer *renderer;
    QWidget *main_widget;

    void buildMainWidget();

public:
    Q_INVOKABLE GrayScaleGUI(Renderer*);
    virtual ~GrayScaleGUI();

    virtual QString getName() const { return QString("Gray scale"); }

public slots:

};
