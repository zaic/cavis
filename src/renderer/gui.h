#pragma once

#include "renderer.h"
#include <QLabel>

class RendererGUI : public QObject {
	Q_OBJECT

	RendererGUI();
	RendererGUI(const RendererGUI& );
	RendererGUI& operator=(const RendererGUI& );

	Renderer *_renderer;

protected:
	QWidget *main_widget;

public:
	RendererGUI(Renderer *);
	virtual ~RendererGUI();

	virtual Renderer* getRenderer() const { return _renderer; }

	virtual QString name() const = 0;
	virtual QWidget* widget() const { return main_widget; }
};
