#include "localfileconfig.h"

LocalFileConfig::LocalFileConfig(const char *init_path) : Config()
{
	dim_size[0] = 0;
	dim_size[1] = dim_size[2] = 1;

	working_dir.setFilter(QDir::Files);
	working_dir.setSorting(QDir::Name);

	if(init_path)
		resetDirectory(init_path);
}

LocalFileConfig::~LocalFileConfig() {

}

bool LocalFileConfig::resetDirectory(const char *path) {
	current_frame_id = -1;
	data.clear();
	frames_list.clear();
	working_dir.setPath(path);
	if(!working_dir.isReadable())
		return false;
	frames_list = working_dir.entryList();
	for(auto i : frames_list)
		qDebug() << i << endl;
	return true;
}

int LocalFileConfig::setFrame(int frame_id) {
	qDebug() << "[config/local] set frame id = " << frame_id;
	if(frame_id < 0 || frame_id > getFramesCount()) return Config::FRAME_NOT_CHANGED;
	current_frame_id = frame_id;
	data.clear();
	QFile f(working_dir.filePath(frames_list.at(current_frame_id)));
	if(f.open(QFile::ReadOnly)) {
		char buf[128];
		while(f.canReadLine() || true) {
			f.readLine(buf, 128);
			double tmp;
			if(sscanf(buf, "%lf", &tmp) != 1) break;
			data << tmp;
		}
	}
	dim_size[0] = data.size();
	qDebug() << "[config/local] Ok, elements in data = " << data.size();
	return frame_id;
}

int LocalFileConfig::getRealDimSize(int dim) const {
	if(dim < 0 || dim > 2)
		return 1;
	return dim_size[dim];
}

const char* LocalFileConfig::getRealData() const {
	if(data.empty()) {
		// ну ой, такого быть не должно
		qDebug() << "There are no any loaded data :(";
	}
	qDebug() << "[config/local] data size = " << data.size();
	return reinterpret_cast<const char*>(data.data());
}
