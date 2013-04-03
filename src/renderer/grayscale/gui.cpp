#include "gui.h"

GrayScaleGUI::GrayScaleGUI(Renderer *_renderer) :
    RendererGUI(_renderer),
    renderer(qobject_cast<GrayScaleRenderer*>(_renderer))
{
    buildMainWidget();
}

GrayScaleGUI::~GrayScaleGUI()
{
    delete main_widget;
}

void GrayScaleGUI::buildMainWidget()
{
    QLabel *lbl_nothing = new QLabel("nothing");
    main_widget = lbl_nothing;
}
