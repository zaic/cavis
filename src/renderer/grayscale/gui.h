#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QBoxLayout>

#include "grayscale.h"
#include "../gui.h"

class GrayScaleGUI : public RendererGUI {
	Q_OBJECT

	GrayScaleGUI();
	GrayScaleGUI(const GrayScaleGUI& );
	GrayScaleGUI& operator=(const GrayScaleGUI& );

	GrayScaleRenderer *renderer;
	QWidget *main_widget;

	void buildMainWidget();

public:
	GrayScaleGUI(GrayScaleRenderer*);
	virtual ~GrayScaleGUI();

	virtual QString name() const { return QString("Gray scale"); }

public slots:

};
