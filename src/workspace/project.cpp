#include "project.h"

Project::Project()
{

}

Project::~Project()
{

}

void Project::remModel(QMdiSubWindow *model_win)
{
    auto it = models.find(model_win);
    if(it == models.end()) return;
    models.erase(it);
}

void Project::save(const QString &filename)
{
    proj_filename = filename;
    QFile file(proj_filename);
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);
    stream << qint16(0x1807);
    stream << qint16(models.size());
    for(auto it : models)
        it->save(stream);
}

void Project::load(const QString &filename, QMdiArea *mdi_area)
{
    proj_filename = filename;
    QFile file(proj_filename);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);

    qint16 signature;
    stream >> signature;
    assert(signature == 0x1807);

    qint16 models_count;
    stream >> models_count;
    for(qint16 i = 0; i < models_count; i++) {
        qDebug() << "[proj/load] load model" << i;

        Model *tmp_model = new Model;
        tmp_model->load(stream);

        // TODO убрать временные костыли
        QtSimpleBuffer* qt_buffer = new QtSimpleBuffer();
        tmp_model->buffer = dynamic_cast<GraphicBuffer*>(qt_buffer);
        QMdiSubWindow *tmp_mdi_sub_win = mdi_area->addSubWindow(qt_buffer->render_window);
        qt_buffer->render_window->showMaximized();
        addModel(tmp_mdi_sub_win, tmp_model);
    }
}
