#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QBoxLayout>

#include "cuthpploupe.h"
#include "../gui.h"

class CutHPPLoupeGUI : public CutGUI {
	Q_OBJECT

	CutHPPLoupeGUI();
	CutHPPLoupeGUI(const CutHPPLoupeGUI& );
	CutHPPLoupeGUI& operator=(const CutHPPLoupeGUI& );

	CutHPPLoupe *cut;
	QWidget *main_widget;
	QCheckBox *chk_autoscale;
	QSpinBox *spn_scale;

	void buildMainWidget();

public:
	CutHPPLoupeGUI(CutHPPLoupe*);
	virtual ~CutHPPLoupeGUI();

	virtual Cut* getCut() const { return cut; }

	virtual QString name() const { return QString("HPP Loupe"); }
	virtual QWidget* widget() const;

public slots:
	void autoscaleToggled(bool value);
	void scaleChanged(int value);
};
