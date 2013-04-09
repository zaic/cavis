#include "project.h"

Project::Project()
{

}

Project::~Project()
{

}

Model* Project::addModel(const QStringList &renderers, Config *config)
{
    Model *model = new Model(renderers, config);
    //windows[model].clear(); // clear? oO
    return model;
}

Model* Project::getModel(QMdiSubWindow *win)
{
    auto it = models.find(win);
    return (it == models.end() ? NULL : it.value());
}

void Project::removeModel(Model *model_obj)
{
    auto it = windows.find(model_obj);
    if(it == windows.end()) {
        qWarning() << "[wrkspc/project] can't remove model" << model_obj;
        return ;
    }
    for(QMdiSubWindow *win : it.value()) {
        auto jt = models.find(win);
        if(jt == models.end())
            qWarning() << "[wrkspc/project] broken consistency :(";
        else
            models.erase(jt);
    }
    windows.erase(it);
    delete model_obj;
}

void Project::removeModel(QMdiSubWindow *win)
{
    removeModel(getModel(win));
}

QMdiSubWindow* Project::addWindowToModel(Model *model_obj, QtSimpleBuffer *buf)
{
    QMdiSubWindow *win = model_obj->addWindow(buf);
    models[win] = model_obj;
    windows[model_obj].insert(win);
    return win;
}

void Project::removeWindowFromModel(QMdiSubWindow *win)
{
    qDebug() << "[wrkspc/project] removing window" << win;
    Model *model = getModel(win);
    if(!model) {
        qWarning() << "[wrkspc/project] can't remove window from unknown model";
        return ;
    }
    model->removeWindow(win);

    auto it = models.find(win);
    if(it == models.end() || it.value() != model) {
        qWarning() << "[wrkspc/project] remove windows: broken consistency, can't find model by window";
        return ;
    }

    auto jt = windows[model].find(win);
    if(jt == windows[model].end()) {
        qWarning() << "[wrkspc/project] remove windows: broken consistency, can't find window in model";
        return ;
    }

    windows[model].erase(jt);
    models.erase(it);
}

void Project::updateProjectTree(QTreeWidget *wgt_project_tree)
{
    wgt_project_tree->clear(); // eh :(
    for(auto it : windows.keys()) {
        QTreeWidgetItem *tree_model_item = new QTreeWidgetItem(QStringList("Model"));
        for(auto jt : it->windows) {
            QTreeWidgetItem *tree_window_iterm = new QTreeWidgetItem(QStringList({"View", jt->getCurrentGUI()->getName()}));
            tree_model_item->addChild(tree_window_iterm);
        }
        wgt_project_tree->addTopLevelItem(tree_model_item);
    }
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
    /*
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
        //tmp_model->buffer = dynamic_cast<GraphicBuffer*>(qt_buffer);
        QMdiSubWindow *tmp_mdi_sub_win = mdi_area->addSubWindow(qt_buffer->render_window);
        qt_buffer->render_window->showMaximized();
        addModel(tmp_mdi_sub_win, tmp_model);
    }
    */
}
