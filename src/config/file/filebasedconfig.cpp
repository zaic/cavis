#include "filebasedconfig.h"

FileBasedConfig::FileBasedConfig(const char *filename, int x, int y) :
	logic_x(x),
	logic_y(y),
	current_frame(-1)
{
	ifstream config_stream;
	config_stream.exceptions(ifstream::failbit | ifstream::badbit);
	try {
		config_stream.open(filename);
		int dim;
		config_stream >> dim;
		assert(dim == 2);
		config_stream >> real_y >> real_x >> element_size;
		if(!(config_stream >> frames_count) || frames_count == 0)
			frames_count = -1;
		data = new char[real_x * real_y * element_size];
		config_stream.close();

		setFrame(0);
	} catch(ifstream::failure& e) {
		cerr << "some error :(" << endl;
		throw e;
	}
}

FileBasedConfig::~FileBasedConfig() {
	if(data) delete[] data;
}

inline int FileBasedConfig::getRealDimSize(int dim) const {
	switch(dim) {
	case 0: return real_x;
	case 1: return real_y;
	}
	return 1;
}

int FileBasedConfig::prev() {
	return setFrame(current_frame - 1);
}

int FileBasedConfig::next() {
	return setFrame(current_frame + 1);
}

int FileBasedConfig::setFrame(int frame) {
	if(frame < 0) return FRAME_NOT_CHANGED;
	if(frame >= frames_count) return FRAME_NOT_CHANGED;

	if(current_frame != frame) {
		current_frame = frame;

		stringstream filename;
		//filename << "data";
		filename << current_frame;
		string fn = filename.str();
		while(fn.length() < 4) fn = "0" + fn;
		fn = fn + ".bin";

		ifstream data_stream(fn.c_str(), ifstream::binary);
		if(!data_stream.is_open()) return false;
		size_t size = real_x * real_y * element_size;
		data_stream.read(data, size);
		data_stream.close();
	}

	return frame;
}
