#include "gui.h"

WaveGUI::WaveGUI(Renderer *_renderer) :
    RendererGUI(dynamic_cast<Renderer*>(_renderer))
{
    _renderer->setParameters(this);
    buildMainWidget();
}

WaveGUI::~WaveGUI()
{
    delete main_widget;
}

void WaveGUI::buildMainWidget()
{
    QLabel *lbl_nothing = new QLabel("nothing");
    main_widget = lbl_nothing;
}
