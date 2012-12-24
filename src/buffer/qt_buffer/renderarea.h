#pragma once

#include <QWidget>
#include <QPainter>
#include "qtsimplebuffer.h"
#include "../../visualizzzator.h"

class RenderArea : public QWidget {
	Q_OBJECT

	Visualizzzator *visualizator;

protected:
	void paintEvent(QPaintEvent *event);

public:
	explicit RenderArea(Visualizzzator *vis, QWidget *parent = 0);
	
signals:
	
public slots:
	void setPrevFrame() { visualizator->config->prevFrame(); }
	void setNextFrame() { visualizator->config->nextFrame(); }
	void setFrame(int frame) { visualizator->config->setFrame(frame); }
	
};
