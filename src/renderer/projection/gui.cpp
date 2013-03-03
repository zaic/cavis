#include "gui.h"

ProjectionGUI::ProjectionGUI(Renderer *_renderer) : RendererGUI(dynamic_cast<Renderer*>(_renderer))
{
	// тили-тили
	_renderer->setParameters(this);
	builMainWidget();
}

ProjectionGUI::~ProjectionGUI()
{
	// трали-вали
}

void ProjectionGUI::builMainWidget() {
	// Scale
	QLabel *lbl_scale = new QLabel(tr("X-scale:"));
	scale = new QSpinBox;
	scale->setMinimum(1);
	scale->setMaximum(100500);
	scale->setValue(100);

	QLabel *lbl_factor = new QLabel(tr("Y-factor:"));
	factor = new QSpinBox;
	factor->setMinimum(1);
	factor->setMaximum(100500);
	factor->setValue(100);

	// Interpolation
	// TODO

	// Layouts
	QHBoxLayout *laytmpscale = new QHBoxLayout;
	laytmpscale->addWidget(lbl_scale);
	laytmpscale->addWidget(scale);

	QHBoxLayout *laytmpfactor = new QHBoxLayout;
	laytmpfactor->addWidget(lbl_factor);
	laytmpfactor->addWidget(factor);

	QVBoxLayout *laytmpall = new QVBoxLayout;
	laytmpall->addLayout(laytmpscale);
	laytmpall->addLayout(laytmpfactor);

	main_widget = new QWidget;
	main_widget->setLayout(laytmpall);
}
