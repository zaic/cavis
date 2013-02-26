#pragma once

#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QBoxLayout>

#include "hpploupe.h"
#include "../gui.h"

class HPPLoupeGUI : public RendererGUI {
	Q_OBJECT

	HPPLoupeGUI();
	HPPLoupeGUI(const HPPLoupeGUI& );
	HPPLoupeGUI& operator=(const HPPLoupeGUI& );

	HPPLoupeRenderer *renderer;
	QCheckBox *chk_autoscale;
	QSpinBox *spn_scale;

	void buildMainWidget();

public:
	HPPLoupeGUI(HPPLoupeRenderer*);
	virtual ~HPPLoupeGUI();

	virtual QString name() const { return QString("HPP Loupe"); }

public slots:
	void autoscaleToggled(bool value);
	void scaleChanged(int value);
};
