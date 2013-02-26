#include "gui.h"

GrayScaleGUI::GrayScaleGUI(GrayScaleRenderer *_renderer) : RendererGUI(dynamic_cast<Renderer*>(_renderer)), renderer(_renderer) {
	buildMainWidget();
}

GrayScaleGUI::~GrayScaleGUI() {
	delete main_widget;
}

void GrayScaleGUI::buildMainWidget() {
	QLabel *lbl_nothing = new QLabel("nothing");
	main_widget = lbl_nothing;
}
