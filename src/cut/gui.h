#pragma once

// TODO: do it less virtual

#include "cut.h"
#include <QLayout>

class CutGUI : public QObject {
	Q_OBJECT

	CutGUI();
	CutGUI(const CutGUI& );
	CutGUI& operator=(const CutGUI& );

public:
	CutGUI(const Cut*);
	virtual ~CutGUI();

	virtual Cut* getCut() const = 0;

	virtual QString name() const = 0;
	virtual QWidget* widget() const = 0;
};
