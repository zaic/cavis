#include "dllconfig.h"

DLLConfig::DLLConfig() :
    obj_model(NULL),
    lib_handle(NULL),
    dll_path(""),
    obj_data(NULL)
{

}

DLLConfig::DLLConfig(const QString &path) :
    dll_path(path)
{
    loadMeFromLibrary();
}

DLLConfig::~DLLConfig()
{
    void (*fn_quit)(model_t*);
    fn_quit = (void(*)(model_t*))dlsym(lib_handle, "destroy");
    if (fn_quit == NULL) {
        qDebug() << "[config/dll] quit()" << dlerror();
        return ;
    } else
        fn_quit(obj_model);
}

bool DLLConfig::loadMeFromLibrary()
{
    size_y = 0;
    size_x = 0;

    lib_handle = dlopen(dll_path.toStdString().c_str(), RTLD_LAZY);
    if(!lib_handle) {
        qDebug() << "[config/dll] ooops" << dlerror();
        return false;
    }

    model_t* (*fn_init)(const char*);
    fn_init = (model_t*(*)(const char*))dlsym(lib_handle, "create");
    if (fn_init == NULL) {
        qDebug() << "[config/dll] create()" << dlerror();
        return false;
    } else {
        if(cfg_path.isEmpty()) {
            cfg_path = QFileDialog::getOpenFileName(NULL, tr("Select model configuration file"));
            if(cfg_path.isNull()) return false;
        }
        //obj_model = fn_init("/home/zaic/nsu/cavis/src/examples/hpp.txt");
        obj_model = fn_init(cfg_path.toStdString().c_str());
    }

    // TODO: check errors
    lib_makestep = (void(*)(model_t*))dlsym(lib_handle, "make_step");
    lib_get_lattice = (arr2_u8_t*(*)(model_t*))dlsym(lib_handle, "get_lattice");
    obj_data = lib_get_lattice(obj_model);
    size_y = obj_data->height;
    size_x = obj_data->width;

    return true;
}

int DLLConfig::getDimSize(int dim) const
{
    if(dim == 0) return size_x;
    if(dim == 1) return size_y;
    return 1;
}

int DLLConfig::setIteration(int iteration)
{
    if(iteration < current_iteration_id && iteration != Config::FORCED_UPDATE)
        return current_iteration_id;
    if(iteration > current_iteration_id + 1)
        return current_iteration_id;

    if(iteration == Config::FORCED_UPDATE) {
        obj_data = lib_get_lattice(obj_model);
    } else if(iteration == current_iteration_id + 1) {
        lib_makestep(obj_model);
        obj_data = lib_get_lattice(obj_model);
        current_iteration_id = iteration;
    }

    return current_iteration_id;
}

void DLLConfig::serialize(QDataStream &stream)
{
#if 0
    preSerialize(stream);
    stream << dll_path;
    stream << qint32(size_x) << qint32(size_y);
    for(int i = 0; i < size_x * size_y; i++)
        stream << qint8(reinterpret_cast<qint8*>(data)[i]);
#endif
}

void DLLConfig::deserialize(QDataStream &stream)
{
#if 0
    preDeserialize(stream);
    stream >> dll_path;
    loadMeFromLibrary();
    qint32 tx, ty;
    stream >> tx >> ty;
    size_x = tx;
    size_y = ty;
    for(int i = 0; i < size_x * size_y; i++) {
        stream >> reinterpret_cast<qint8*>(data)[i];
    }
#endif
}
