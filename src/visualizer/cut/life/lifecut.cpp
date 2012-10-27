#include "lifecut.h"

LifeCut::LifeCut() {

}

LifeCut::~LifeCut() {

}

void LifeCut::operator()(int x, int y, Config *config, void *result) {
	uchar* data = (uchar*)config->getRealData();
	const int rx = config->getRealDimSize(1);
	int id = (y * rx + x) * 3;
	uint r = data[id];
	uint g = data[id + 1];
	uint b = data[id + 2];
	uint color = r  | (g << 8) | (b << 16) | 0xff000000;
	*((uint*)result) = color;
}
