#include <iostream>
#include "common.h"
#include "visualizzzator.h"
#include "window.h"
#include "config/file/filebasedconfig.h"
#include "config/network-tcp/tcpconfig.h"
#include "config/stub/stubconfig.h"
#include "config/local/localfileconfig.h"
#include "renderer/hpp-loupe/gui.h"
#include "renderer/grayscale/gui.h"
#include "renderer/projection/projection.h"
#include "renderer/projection/gui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*
     *	CONFIG
     */
    Config *config = NULL;
    Config *stub_config = new StubConfig(30, 20);
    Config *local_config = new LocalFileConfig("/home/zaic/tmp/ca_dumps/density");

    /*
     *	RENDERER
     */
    Renderer *renderer = NULL;

    HPPLoupeRenderer *cut = new HPPLoupeRenderer();
    RendererGUI *cutgui = new HPPLoupeGUI(cut);

    GrayScaleRenderer *cut_scale = new GrayScaleRenderer();
    RendererGUI *cut_scale_gui = new GrayScaleGUI(cut_scale);

    ProjectionRenderer *cut_proj = new ProjectionRenderer();
    ProjectionGUI *cut_proj_gui = new ProjectionGUI(cut_proj);

    QVector<RendererGUI*> supported_cuts;

#if 1 /* PROJECTION */
    config = local_config;
    renderer = cut_proj;
    supported_cuts << cut_proj_gui;

#elif 1 /* HPP */
    config = stub_config;
    renderer = cut_scale;
    supported_cuts << cut_scale_gui;
    supported_cuts << cutgui;
#endif

    /*
     *	APPLICATION
     */
    // TODO: remove renderer
    Visualizzzator *visualizator = new Visualizzzator(config, renderer);
    Window w(config, supported_cuts);
    w.show();
    w.resize(1280, 800);
    return app.exec();
}
