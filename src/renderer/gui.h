#pragma once

#include <QLabel>

class Renderer;

class RendererGUI : public QObject
{
    Q_OBJECT

    RendererGUI();
    RendererGUI(const RendererGUI& );
    RendererGUI& operator=(const RendererGUI& );

    Renderer *p_renderer;

protected:
    QWidget *main_widget;

public:
    RendererGUI(Renderer *);
    virtual ~RendererGUI();

    virtual Renderer* getRenderer() const { return p_renderer; }

    virtual QString getName() const = 0;
    virtual QWidget* getWidget() const { return main_widget; }
};
