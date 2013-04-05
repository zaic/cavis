#include "model.h"
#include "config/factory.h"
#include "windowevent.h"
#include "buffercontainer.h"

Model::Model(const QStringList &sup_renderers, Config *_config) :
    supported_renderers(sup_renderers),
    config(_config)
{

}

Model::~Model()
{

}

View* Model::setCurrentView(QMdiSubWindow *win)
{
    auto it = windows.find(win);
    if(it == windows.end()) {
        qWarning() << "[wrkspc/model] non-exists mdisubwin";
        current_view = NULL;
    } else {
        current_view = it.value();
    }
    return current_view;
}

void Model::drawOne(GraphicBuffer *buffer, Renderer *renderer)
{
    qDebug() << renderer;
    if(!renderer) return ;
    buffer->create(renderer->getBufferFormat());
    renderer->setConfig(config);
    renderer->setBuffer(buffer);
    renderer->draw();
    buffer->complete();
}

void Model::draw(QMdiSubWindow *win)
{
    if(!setCurrentView(win)) return ;
    drawOne(current_view->buffer, current_view->getCurrentRenderer());
    win->update();
}

void Model::drawAll()
{
    for(auto i : windows)
        drawOne(i->buffer, i->getCurrentRenderer());
}

QWidget* Model::getRenderersGUI(QMdiSubWindow *win)
{
    auto it = windows.find(win);
    if(it == windows.end()) {
        qWarning() << "[wrkspc/model] ooops";
        return NULL;
    }
    return it.value()->getGUI();
}

QMdiSubWindow *Model::addWindow(QtSimpleBuffer *buf)
{
    View *v = new View(supported_renderers, buf);
    QMdiSubWindow *mdiwin = new QMdiSubWindow;
    BufferContainer *example_container = new BufferContainer(buf->render_window, mdiwin);
    mdiwin->setWidget(example_container);
    mdiwin->setAttribute(Qt::WA_DeleteOnClose);
    windows[mdiwin] = v;
    return mdiwin;
}

void Model::removeWindow(QMdiSubWindow *win)
{
    auto it = windows.find(win);
    if(it != windows.end())
        windows.erase(it);
    else
        qWarning() << "[wrkspc/model] removing non-exists mdisubwin";
    WindowEvent::get()->doProjectChanged();
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
