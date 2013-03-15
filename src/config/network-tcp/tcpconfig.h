#pragma once

#include "../config.h"
#include <algorithm>
#include <boost/asio.hpp>
#include <QDebug>

using std::max;
using namespace boost;
using  boost::asio::ip::tcp;

class TcpConfig : public Config {
	int real_x, real_y;
	int logic_x, logic_y;

	char *real_data;

	tcp::socket *my_socket;

public:
	TcpConfig(const char *hostname, int port);
	virtual ~TcpConfig();

	virtual int setFrame(int frame);
	virtual int getFramesCount();

	virtual void* getData(void* = NULL) { return real_data; }
	virtual int getDimSize(int dim) const;
	virtual int getDimSizeX() const { return getDimSize(0); }
	virtual int getDimSizeY() const { return getDimSize(1); }
	virtual int getDimSizeZ() const { return getDimSize(2); }

	//virtual void setLogicSize(int x, int y);
};
