#pragma once

#include <QtWidgets>
#include "view.h"
#include "buffer/qt_buffer/qtsimplebuffer.h"
#include "config/config.h"
#include "renderer/renderer.h"

class Model
{
    Model(const Model& );
    Model& operator=(const Model& );

    QStringList supported_renderers;
    QMap<QMdiSubWindow*, View*> windows;

    View *current_view;
    View* setCurrentView(QMdiSubWindow *win);

    QMdiSubWindow* addWindow(QtSimpleBuffer* buf);
    void removeWindow(QMdiSubWindow *win);
    QWidget* getRenderersGUI(QMdiSubWindow *win);

    void drawOne(GraphicBuffer *buffer, Renderer *renderer);

    friend class Project;

public:
    Model(const QStringList& sup_renderers, Config *_config);
    ~Model();

    void draw(QMdiSubWindow *win);
    void drawAll();

    bool save(QDataStream& stream);
    bool load(QDataStream& stream);

    Config *config;
};
