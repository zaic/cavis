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
#include "renderer/projection/gui.h"

#include <boost/asio.hpp>

void test() {
	using boost::asio::ip::tcp;
	boost::asio::io_service my_io_service;

	tcp::resolver resolver(my_io_service);
	tcp::resolver::query query("192.168.1.101", "1807");
	tcp::resolver::iterator my_endpoint_iterator = resolver.resolve(query);

	tcp::socket my_socket(my_io_service);
	boost::asio::connect(my_socket, my_endpoint_iterator);

	qint64 x;
	boost::asio::read(my_socket, boost::asio::buffer(&x, sizeof(x)));
	Eo(x);
}

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	/*
	 *	CONFIG
	 */
	//Config *config = new TcpConfig("localhost", 1807);
	Config *config = new StubConfig(30, 20);
    Config *local_config = new LocalFileConfig("/home/zaic/tmp/ca_dumps/density");

	/*
	 *	RENDERER
	 */
	HPPLoupeRenderer *cut = new HPPLoupeRenderer();
	RendererGUI *cutgui = new HPPLoupeGUI(cut);

	GrayScaleRenderer *cut_scale = new GrayScaleRenderer();
	RendererGUI *cut_scale_gui = new GrayScaleGUI(cut_scale);

	ProjectionRenderer *cut_proj = new ProjectionRenderer();
	ProjectionGUI *cut_proj_gui = new ProjectionGUI(cut_proj);

	QVector<RendererGUI*> supported_cuts;
	// fill supported cuts list
	supported_cuts << cut_proj_gui;
	supported_cuts << cutgui;
	supported_cuts << cut_scale_gui;

	/*
	 *	APPLICATION
	 */
	Visualizzzator *visualizator = new Visualizzzator(local_config, dynamic_cast<Renderer*>(cut_proj));
	Window w(visualizator, supported_cuts);
	w.show();
	return app.exec();
}
