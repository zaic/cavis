#include "gui.h"

CutHPPLoupeGUI::CutHPPLoupeGUI(CutHPPLoupe *_cut) : CutGUI(dynamic_cast<Cut*>(cut)), cut(_cut) {
	buildMainWidget();
}

CutHPPLoupeGUI::~CutHPPLoupeGUI() {
	delete main_widget;
}

void CutHPPLoupeGUI::buildMainWidget() {
	chk_autoscale = new QCheckBox;
	chk_autoscale->setText("autoscale");

	QLabel *lbl_scale = new QLabel(tr("scale:"));
	spn_scale = new QSpinBox;
	spn_scale->setMinimum(3);

	connect(chk_autoscale, SIGNAL(toggled(bool)), spn_scale, SLOT(setDisabled(bool)));
	connect(chk_autoscale, SIGNAL(toggled(bool)), this, SLOT(autoscaleToggled(bool)));
	connect(spn_scale, SIGNAL(valueChanged(int)), this, SLOT(scaleChanged(int)));
	chk_autoscale->setChecked(true);

	QHBoxLayout *laytmpscale = new QHBoxLayout;
	laytmpscale->addWidget(lbl_scale);
	laytmpscale->addWidget(spn_scale);
	// TODO: пыщ пыщ пыщ, да ололо
	QVBoxLayout *laytmpall = new QVBoxLayout;
	laytmpall->addWidget(chk_autoscale);
	laytmpall->addLayout(laytmpscale);

	main_widget = new QWidget;
	main_widget->setLayout(laytmpall);
}

QWidget *CutHPPLoupeGUI::widget() const {
	return main_widget;
}

void CutHPPLoupeGUI::autoscaleToggled(bool value) {
	cut->setAutoscale(value);
	if(!value)
		scaleChanged(spn_scale->value());
}

void CutHPPLoupeGUI::scaleChanged(int value) {
	cut->setScale(value);
}
