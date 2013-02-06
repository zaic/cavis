#include <iostream>
#include "common.h"
#include "visualizzzator.h"
#include "window.h"
#include "cut/life/lifecut.h"
#include "config/file/filebasedconfig.h"
#include "config/network-tcp/tcpconfig.h"
#include "config/stub/stubconfig.h"
#include "cut/hpp-loupe/cuthpploupe.h"
#include "cut/hpp-loupe/gui.h"

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

	//chdir("examples/current");
	chdir("/home/zaic/nsu/__ca/data/obmaz");
	//Config *config = new TcpConfig("localhost", 1807);
	Config *config = new StubConfig(30, 20);

	CutHPPLoupe *cut = new CutHPPLoupe();
	CutGUI *cutgui = new CutHPPLoupeGUI(cut);
	QVector<CutGUI*> supported_cuts;
	supported_cuts << cutgui;

	Visualizzzator *visualizator = new Visualizzzator(config, dynamic_cast<Cut*>(cut));
	Window w(visualizator, supported_cuts);
	w.show();
	return app.exec();
}
