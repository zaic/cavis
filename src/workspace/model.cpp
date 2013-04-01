#include "model.h"
#include "config/factory.h"
#include <QtWidgets>

Model::Model()
{

}

Model::~Model()
{

}

void Model::draw()
{
    buffer->create(renderer->getBufferFormat());
    renderer->setConfig(config);
    renderer->setBuffer(buffer);
    renderer->draw();
    buffer->complete();
}

bool Model::save(QDataStream &stream)
{
    config->serialize(stream);
    return true;
}

bool Model::load(QDataStream &stream)
{
    QString config_type;
    stream >> config_type;
    qDebug() << "[wrkspc/model] load config type" << config_type;
    config = ConfigFactory::createConfig(config_type);
    if(!config) {
        QMessageBox::critical(NULL, QObject::tr("Can not open project"), QObject::tr("Invalid Config type '%1'").arg(config_type));
        return false;
    }
    config->deserialize(stream);
    return true;
}
