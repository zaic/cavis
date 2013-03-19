#include "dllconfig.h"

DLLConfig::DLLConfig(const char *path)
{
    size_y = 128; // TODO :(
    size_x = 192;

    lib_handle = dlopen(path, RTLD_LAZY);
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

int DLLConfig::getDimSize(int dim) const {
    if(dim == 0) return size_x;
    if(dim == 1) return size_y;
    return 1;
}

int DLLConfig::setFrame(int frame) {
    if(frame < current_frame_id || frame > current_frame_id + 1) return Config::FRAME_NOT_CHANGED;
    if(frame == current_frame_id + 1) {
        lib_calc();
        data = lib_data();
        current_frame_id = frame;
    }
    return current_frame_id;
}
