#include <iostream>
#include "common.h"
#include "visualizzzator.h"
#include "buffer/qt_buffer/window.h"
#include "cut/life/lifecut.h"
#include "config/file/filebasedconfig.h"

using namespace std;

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	//chdir("examples/current");
	chdir("/home/zaic/nsu/__ca/data/obmaz");
	Config *config = new FileBasedConfig("config");
	Cut2D *cut = new LifeCut();
	Visualizzzator *visualizator = new Visualizzzator(config, cut);

	Window w(visualizator);
	w.resetConfig(config);
	w.show();
	return app.exec();
}
