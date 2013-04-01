#include "factory.h"

QMap<QString, const QMetaObject*> ConfigFactory::config_factory;

void ConfigFactory::initConfig()
{
    // DLL config
    DLLConfig *config_dll = new DLLConfig;
    config_factory[config_dll->metaObject()->className()] = config_dll->metaObject();

    // Local file config
    LocalFileConfig *config_local = new LocalFileConfig;
    config_factory[config_local->metaObject()->className()] = config_local->metaObject();

    // Stub config
    StubConfig *config_stub = new StubConfig();
    config_factory[config_stub->metaObject()->className()] = config_stub->metaObject();
}

Config* ConfigFactory::createConfig(const QString &name)
{
    if(config_factory.empty())
        initConfig();
    if(!config_factory.contains(name))
        return NULL;
    return qobject_cast<Config*>(config_factory[name]->newInstance());
}
