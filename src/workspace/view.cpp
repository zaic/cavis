#include "view.h"

View::View(const QStringList &sup_rens, QObject *_parent) :
    QObject(_parent)
{
    loadRenderers(sup_rens);
    createGUI();
}

View::~View()
{
    for(QMap<QString, RendererGUI*>::Iterator it = gui_by_caption.begin(); it != gui_by_caption.end(); ++it) {
        delete it.value()->getRenderer();
        delete it.value();
    }
    delete gui_settings;
}

void View::loadRenderers(const QStringList& supported_renderers)
{
    for(const QString& i : supported_renderers) {
        RendererGUI *r = RendererFactory::createRenderer(i);
        if(r == NULL)
            qDebug() << "[wrkspc/view] unknown renderer type" << i;
        else
            gui_by_caption[i] = r;
    }
    current_gui = (gui_by_caption.empty() ? NULL : gui_by_caption.begin().value());
}

void View::createGUI()
{
    QLabel *lbl_switch_label = new QLabel(tr("View:"));

    cmb_settings = new QComboBox;
    connect(cmb_settings, SIGNAL(currentIndexChanged(QString)), this, SLOT(updateCurrentRenderer(QString)));
    cmb_settings->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred));

    QHBoxLayout *lay_caption_bar = new QHBoxLayout;
    lay_caption_bar->addWidget(lbl_switch_label);
    lay_caption_bar->addWidget(cmb_settings);

    QVBoxLayout *lay_config_all = new QVBoxLayout;
    lay_config_all->addLayout(lay_caption_bar);
    for(QMap<QString, RendererGUI*>::Iterator it = gui_by_caption.begin(); it != gui_by_caption.end(); ++it) {
        it.value()->getWidget()->setVisible(false);
        lay_config_all->addWidget(it.value()->getWidget());
        cmb_settings->addItem(it.key());
    }
    lay_config_all->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    gui_settings = new QWidget;
    gui_settings->setLayout(lay_config_all);
}

void View::updateCurrentRenderer(const QString &new_renderer_caption)
{
    qDebug() << "[wrkspc/view] change view to" << new_renderer_caption;
    if(current_gui)
        current_gui->getWidget()->setVisible(false);
    current_gui = gui_by_caption[new_renderer_caption];
    if(!current_gui) {
        qCritical() << "[wrkspc/view] invalid new caption" << new_renderer_caption;
        return ;
    }
    current_gui->getWidget()->setVisible(true);
    buffer->update();
}
