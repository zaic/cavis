#include "tcpconfig.h"

TcpConfig::TcpConfig(const char *, int) : real_x(30), real_y(20), logic_x(30), logic_y(20), current_frame_id(-1) {
	real_data = new char[600];
	memset(real_data, 0, 600);
}

TcpConfig::~TcpConfig() {
	if(real_data) delete[] real_data;
}

bool TcpConfig::prevFrame() {
	return setFrame(current_frame_id - 1);
}

bool TcpConfig::nextFrame() {
	return setFrame(current_frame_id + 1);
}

bool TcpConfig::setFrame(int frame) {
	memset(real_data, 0, 600);
	switch(frame) {
	case 0:
		real_data[5] = 6;
		break;
	case 1:
		real_data[6] = 2;
		real_data[35] = 4;
		break;
	case 2:
		real_data[7] = 2;
		real_data[65] = 4;
	}

	if(frame < current_frame_id) return false;
	if(frame > current_frame_id + 1) return false;
	if(frame == current_frame_id + 1) {
		current_frame_id = frame;
	}
	// TODO some stub fill

	return true;
}

int TcpConfig::getFramesCount() {
	int res = max(1, current_frame_id + 1);
	qDebug() << "frames = " << res;
	return res;
}

int TcpConfig::getRealDimSize(int dim) const {
	switch(dim) {
	case 0: return real_x;
	case 1: return real_y;
	}
	return 1;
}