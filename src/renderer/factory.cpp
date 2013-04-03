#include "factory.h"

QMap<QString, const QMetaObject*> RendererFactory::renderer_factory;
QMap<QString, const QMetaObject*> RendererFactory::renderer_gui_factory;

void RendererFactory::initConfig()
{
    // TODO check for unique captions

    // GrayScale
    GrayScaleRenderer *grayscale_renderer = new GrayScaleRenderer();
    GrayScaleGUI *grayscale_gui = new GrayScaleGUI(grayscale_renderer);
    const QString gs_name = grayscale_renderer->metaObject()->className();
    renderer_factory[gs_name] = grayscale_renderer->metaObject();
    renderer_gui_factory[gs_name] = grayscale_gui->metaObject();

    // Loupe
    HPPLoupeRenderer *loupe_renderer = new HPPLoupeRenderer();
    HPPLoupeGUI *loupe_gui = new HPPLoupeGUI(loupe_renderer);
    const QString loupe_name = loupe_renderer->metaObject()->className();
    renderer_factory[loupe_name] = loupe_renderer->metaObject();
    renderer_gui_factory[loupe_name] = loupe_gui->metaObject();
}

RendererGUI* RendererFactory::createRenderer(const QString &name)
{
    if(renderer_factory.empty())
        initConfig();
    if(!renderer_factory.contains(name))
        return NULL;

    Renderer    *renderer_obj = qobject_cast<Renderer*>   (renderer_factory[name]->newInstance());
    RendererGUI *renderer_gui = qobject_cast<RendererGUI*>(renderer_gui_factory[name]->newInstance(Q_ARG(Renderer*, renderer_obj)));

    return renderer_gui;
}
