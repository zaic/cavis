#include "stubconfig.h"

StubConfig::StubConfig(int x, int y) : real_x(x), real_y(y) {
	real_data = new char[x * y];
}

StubConfig::~StubConfig() {
	delete[] real_data;
}

int StubConfig::getRealDimSize(int dim) const {
	switch(dim) {
	case 0: return real_x;
	case 1: return real_y;
	default: return 1;
	}
	return 100500;
}

int StubConfig::setFrame(int frame) {
	if(frame < 0) return FRAME_NOT_CHANGED;
	if(frame > getFramesCount()) return FRAME_NOT_CHANGED;
	qDebug() << "config set frame to " << frame;
	current_frame_id = frame;
	memset(real_data, 0, real_x * real_y);
	switch(frame) {
	case 0:
		real_data[real_x + 5] = 6;
		break;
	default:
		real_data[real_x + 5 + frame] = 2;
		real_data[real_x * (frame + 1) + 5] = 4;
	break;
	}
	return frame;
}
