#pragma once

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

	virtual QLayout* layout() const = 0;
};
