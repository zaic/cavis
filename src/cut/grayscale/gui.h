#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QBoxLayout>

#include "cutgrayscale.h"
#include "../gui.h"

class CutGrayScaleGUI : public CutGUI {
	Q_OBJECT

	CutGrayScaleGUI();
	CutGrayScaleGUI(const CutGrayScaleGUI& );
	CutGrayScaleGUI& operator=(const CutGrayScaleGUI& );

	CutGrayScale *cut;
	QWidget *main_widget;

	void buildMainWidget();

public:
	CutGrayScaleGUI(CutGrayScale*);
	virtual ~CutGrayScaleGUI();

	virtual Cut* getCut() const { return cut; }

	virtual QString name() const { return QString("Gray scale"); }
	virtual QWidget* widget() const { return main_widget; }

public slots:

};
