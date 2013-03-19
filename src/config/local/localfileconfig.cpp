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

LocalFileConfig::~LocalFileConfig()
{

}

bool LocalFileConfig::resetDirectory(const char *path)
{
    current_iteration_id = -1;
    data.clear();
    iterations_list.clear();
    working_dir.setPath(path);
    if(!working_dir.isReadable())
        return false;
    iterations_list = working_dir.entryList();
    return true;
}

int LocalFileConfig::setIteration(int iteration_id)
{
    qDebug() << "[config/local] set iteration = " << iteration_id;
    if(iteration_id < 0 || iteration_id > getIterationsCount()) return current_iteration_id;
    current_iteration_id = iteration_id;
    data.clear();
    QFile f(working_dir.filePath(iterations_list.at(current_iteration_id)));
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
    return iteration_id;
}

int LocalFileConfig::getDimSize(int dim) const
{
    if(dim < 0 || dim > 2)
        return 1;
    return dim_size[dim];
}

void* LocalFileConfig::getData(void*)
{
    if(data.empty()) {
        // ну ой, такого быть не должно
        qDebug() << "There are no any loaded data :(";
    }
    qDebug() << "[config/local] data size = " << data.size();
    return reinterpret_cast<void*>(data.data());
}
