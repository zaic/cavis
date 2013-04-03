#pragma once

#include <QtCore>
#include "renderer.h"
#include "gui.h"
#include "renderer/grayscale/grayscale.h"
#include "renderer/grayscale/gui.h"
#include "renderer/hpp-loupe/hpploupe.h"
#include "renderer/hpp-loupe/gui.h"
#include "renderer/projection/projection.h"
#include "renderer/projection/gui.h"
#include "renderer/wave/wave.h"
#include "renderer/wave/gui.h"

class RendererFactory
{
    RendererFactory();
    RendererFactory(const RendererFactory& );
    RendererFactory& operator=(const RendererFactory& );
    ~RendererFactory();

    static QMap<QString, const QMetaObject*> renderer_factory;
    static QMap<QString, const QMetaObject*> renderer_gui_factory;

    static void initConfig();

public:
    static RendererGUI* createRenderer(const QString& name);
};
