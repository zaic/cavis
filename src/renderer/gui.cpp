#include "gui.h"

RendererGUI::RendererGUI(Renderer* _rend) : _renderer(_rend), main_widget(new QLabel(tr("There are no any available settings."))) {

}

RendererGUI::~RendererGUI() {

}

