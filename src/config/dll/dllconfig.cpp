#include "dllconfig.h"

DLLConfig::DLLConfig() :
    lib_handle(NULL),
    dll_path(""),
    data(NULL)
{

}

DLLConfig::DLLConfig(const QString &path) :
    dll_path(path)
{
    loadMeFromLibrary();
}

DLLConfig::~DLLConfig()
{
    void (*fn_quit)();
    fn_quit = (void(*)())dlsym(lib_handle, "quit");
    if (fn_quit == NULL) {
        qDebug() << "[config/dll] quit()" << dlerror();
        return ;
    } else
        fn_quit();
}

void DLLConfig::loadMeFromLibrary()
{
    size_y = 192; // TODO :(
    size_x = 256;

    lib_handle = dlopen(dll_path.toStdString().c_str(), RTLD_LAZY);
    if(!lib_handle) {
        qDebug() << "[config/dll] ooops" << dlerror();
        return ;
    }

    void (*fn_init)();
    fn_init = (void(*)())dlsym(lib_handle, "init");
    if (fn_init == NULL) {
        qDebug() << "[config/dll] init()" << dlerror();
        return ;
    } else
        fn_init();

    // TODO: check errors
    lib_calc = (void(*)())dlsym(lib_handle, "calc");
    lib_data = (void*(*)())dlsym(lib_handle, "data");
    data = lib_data();
    ((char*)data)[0] = 0;
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
        data = lib_data();
    } else if(iteration == current_iteration_id + 1) {
        lib_calc();
        data = lib_data();
        current_iteration_id = iteration;
    }
    return current_iteration_id;
}

void DLLConfig::serialize(QDataStream &stream)
{
    preSerialize(stream);
    stream << dll_path;
    stream << qint32(size_x) << qint32(size_y);
    for(int i = 0; i < size_x * size_y; i++)
        stream << qint8(reinterpret_cast<qint8*>(data)[i]);
}

void DLLConfig::deserialize(QDataStream &stream)
{
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
}
