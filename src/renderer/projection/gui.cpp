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
	x_scale = new QSpinBox;
	x_scale->setMinimum(1);
	x_scale->setMaximum(100500);
	x_scale->setValue(100);

	QLabel *lbl_factor = new QLabel(tr("Y-factor:"));
	y_scale = new QSpinBox;
	y_scale->setMinimum(1);
	y_scale->setMaximum(100500);
	y_scale->setValue(100);

	// Interpolation
	// TODO

	// Layouts
	QHBoxLayout *laytmpscale = new QHBoxLayout;
	laytmpscale->addWidget(lbl_scale);
	laytmpscale->addWidget(x_scale);

	QHBoxLayout *laytmpfactor = new QHBoxLayout;
	laytmpfactor->addWidget(lbl_factor);
	laytmpfactor->addWidget(y_scale);

	QVBoxLayout *laytmpall = new QVBoxLayout;
	laytmpall->addLayout(laytmpscale);
	laytmpall->addLayout(laytmpfactor);

	main_widget = new QWidget;
	main_widget->setLayout(laytmpall);
}
