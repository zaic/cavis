#include "gui.h"

CutGrayScaleGUI::CutGrayScaleGUI(CutGrayScale *_cut) : CutGUI(dynamic_cast<Cut*>(cut)), cut(_cut) {
	buildMainWidget();
}

CutGrayScaleGUI::~CutGrayScaleGUI() {
	delete main_widget;
}

void CutGrayScaleGUI::buildMainWidget() {
	QLabel *lbl_nothing = new QLabel("nothing");
	main_widget = lbl_nothing;
}
