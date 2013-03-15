#include "tcpconfig.h"

TcpConfig::TcpConfig(const char *, int) : real_x(30), real_y(20), logic_x(30), logic_y(20) {
	asio::io_service my_io_service;

	tcp::resolver resolver(my_io_service);
	tcp::resolver::query query("192.168.1.101", "1807");
	tcp::resolver::iterator my_endpoint_iterator = resolver.resolve(query);

	my_socket = new tcp::socket(my_io_service);
	boost::asio::connect(*my_socket, my_endpoint_iterator);

	uint64_t tmp;
	boost::asio::read(*my_socket, boost::asio::buffer(&tmp, sizeof(tmp)));
	assert(tmp == 1);
	boost::asio::read(*my_socket, boost::asio::buffer(&tmp, sizeof(tmp)));
	real_x = tmp;
	boost::asio::read(*my_socket, boost::asio::buffer(&tmp, sizeof(tmp)));
	real_y = tmp;

	real_data = new char[real_x * real_y];
	memset(real_data, 0, real_x * real_y);
}

TcpConfig::~TcpConfig() {
	if(real_data) delete[] real_data;
}

int TcpConfig::setFrame(int frame) {
	if(frame < current_frame_id) return FRAME_NOT_CHANGED;
	if(frame > current_frame_id + 1) return FRAME_NOT_CHANGED;
	if(frame == current_frame_id + 1) {
        current_frame_id = frame;
	}

	memset(real_data, 0, real_x * real_y);
	int64_t remain = real_x * real_y;
	int64_t shift = 0;
	qDebug() << "---";
	while(remain) {
		size_t readed = boost::asio::read(*my_socket, boost::asio::buffer(real_data + shift, remain));
		shift += readed;
		remain -= readed;
		qDebug() << readed;
		for(int i = 0; i < shift; i++) if(real_data[i]) {
			qDebug() << i << ":" << int(real_data[i]);
		}
	}
	qDebug() << "---";

	return frame;
}

int TcpConfig::getFramesCount() {
    int res = max(1, current_frame_id + 1);
	qDebug() << "frames = " << res;
	return res;
}

int TcpConfig::getDimSize(int dim) const {
	switch(dim) {
	case 0: return real_x;
	case 1: return real_y;
	}
	return 1;
}
