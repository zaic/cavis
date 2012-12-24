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
	int current_frame_id;

	char *real_data;

	tcp::socket *my_socket;

public:
	TcpConfig(const char *hostname, int port);
	virtual ~TcpConfig();

	virtual bool prevFrame();
	virtual bool nextFrame();
	virtual bool setFrame(int frame);
	virtual int getFramesCount();

	virtual char* getRealData() const { return real_data; }
	virtual int getRealDimSize(int dim) const;
	virtual int getRealDimSizeX() const { return getRealDimSize(0); }
	virtual int getRealDimSizeY() const { return getRealDimSize(1); }
	virtual int getRealDimSizeZ() const { return getRealDimSize(2); }

	//virtual void setLogicSize(int x, int y);
};
