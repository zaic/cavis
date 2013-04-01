#include "config.h"

Config::Config() : current_iteration_id(-1)
{

}

Config::~Config()
{

}

void Config::preSerialize(QDataStream &stream)
{
    stream << QString(metaObject()->className());
    qDebug() << "[config/serial]" << metaObject()->className();
    stream << qint32(current_iteration_id);
}

void Config::preDeserialize(QDataStream &stream)
{
    qint32 tmp;
    stream >> tmp;
    current_iteration_id = tmp;
}
