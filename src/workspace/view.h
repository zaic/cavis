#pragma once

#include <QtWidgets>
#include "renderer/factory.h"
#include "buffer/buffer.h"

class View : public QObject
{
    Q_OBJECT

    QMap<QString, RendererGUI*> gui_by_caption;
    RendererGUI *current_gui;

    QComboBox *cmb_settings;
    QWidget *gui_settings;

    void loadRenderers(const QStringList &supported_renderers);
    void createGUI();

public:
    explicit View(const QStringList& sup_rens, QObject *_parent = 0);
    ~View();

    QWidget* getGUI() const { return gui_settings; }
    Renderer* getCurrentRenderer() const { return ( current_gui ? current_gui->getRenderer() : NULL); }
    
    GraphicBuffer* buffer;

signals:
    
public slots:
    void updateCurrentRenderer(const QString& new_renderer_caption);
    
};
