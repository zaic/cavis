#pragma once

#include <QtWidgets>

class Renderer;

class RendererGUI : public QObject
{
    Q_OBJECT

    RendererGUI(const RendererGUI& );
    RendererGUI& operator=(const RendererGUI& );

    Renderer *p_renderer;

protected:
    QWidget *main_widget;

public:
    Q_INVOKABLE RendererGUI(Renderer *_rend);
    virtual ~RendererGUI();

    virtual Renderer* getRenderer() const { return p_renderer; }

    virtual QString getName() const { return "No Name"; }
    virtual QWidget* getWidget() const { return main_widget; }
};
