#include <iostream>
#include "common.h"
#include "visualizzzator.h"
#include "buffer/qt_buffer/window.h"
#include "cut/life/lifecut.h"
#include "config/file/filebasedconfig.h"
#include "config/network-tcp/tcpconfig.h"
#include "cut/hpp-loupe/cuthpploupe.h"

using namespace std;

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	//chdir("examples/current");
	chdir("/home/zaic/nsu/__ca/data/obmaz");
	Config *config = new TcpConfig("localhost", 1807);
	Cut2D *cut = new CutHPPLoupe();
	Visualizzzator *visualizator = new Visualizzzator(config, cut);

	Window w(visualizator);
	w.resetConfig(config);
	w.show();
	return app.exec();
}
