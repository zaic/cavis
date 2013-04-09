#include "factory.h"

QMap<QString, const QMetaObject*> RendererFactory::renderer_factory;
QMap<QString, const QMetaObject*> RendererFactory::renderer_gui_factory;

QString RendererFactory::toCoolFormat(const QString &s)
{
    QString res = s.toLower();
    int pos = res.indexOf("renderer");
    if(pos != -1)
        res.remove(pos, 8); // remove "renderer"
    return res;
}

void RendererFactory::initConfig()
{
    // TODO check for unique captions

    // GrayScale
    GrayScaleRenderer *grayscale_renderer = new GrayScaleRenderer();
    GrayScaleGUI *grayscale_gui = new GrayScaleGUI(grayscale_renderer);
    const QString gs_name = toCoolFormat(grayscale_renderer->metaObject()->className());
    renderer_factory[gs_name] = grayscale_renderer->metaObject();
    renderer_gui_factory[gs_name] = grayscale_gui->metaObject();

    // Loupe
    HPPLoupeRenderer *loupe_renderer = new HPPLoupeRenderer();
    HPPLoupeGUI *loupe_gui = new HPPLoupeGUI(loupe_renderer);
    const QString loupe_name = toCoolFormat(loupe_renderer->metaObject()->className());
    renderer_factory[loupe_name] = loupe_renderer->metaObject();
    renderer_gui_factory[loupe_name] = loupe_gui->metaObject();

    // Wave
    WaveRenderer *wave_renderer = new WaveRenderer();
    WaveGUI *wave_gui = new WaveGUI(wave_renderer);
    const QString wave_name = toCoolFormat(wave_renderer->metaObject()->className());
    qDebug() << wave_name;
    renderer_factory[wave_name] = wave_renderer->metaObject();
    renderer_gui_factory[wave_name] = wave_gui->metaObject();
}

RendererGUI* RendererFactory::createRenderer(const QString &pname)
{
    const QString name = toCoolFormat(pname);

    if(renderer_factory.empty())
        initConfig();
    if(!renderer_factory.contains(name))
        return NULL;

    Renderer    *renderer_obj = qobject_cast<Renderer*>   (renderer_factory[name]->newInstance());
    RendererGUI *renderer_gui = qobject_cast<RendererGUI*>(renderer_gui_factory[name]->newInstance(Q_ARG(Renderer*, renderer_obj)));

    return renderer_gui;
}
