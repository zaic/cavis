#pragma once

#include <QtCore>
#include "dll/dllconfig.h"
#include "local/localfileconfig.h"
//#include "file/filebasedconfig.h"
//#include "network-tcp/tcpconfig.h"
#include "stub/stubconfig.h"

class ConfigFactory
{
    ConfigFactory();
    ConfigFactory(const ConfigFactory& );
    ConfigFactory& operator=(const ConfigFactory& );
    ~ConfigFactory();

    static QMap<QString, const QMetaObject*> config_factory;

    static void initConfig();

public:
    static Config* createConfig(const QString& name);

};
