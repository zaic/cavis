#include "gui.h"

HPPLoupeGUI::HPPLoupeGUI(Renderer *_renderer) :
    RendererGUI(_renderer),
    renderer(qobject_cast<HPPLoupeRenderer*>(_renderer))
{
    buildMainWidget();
}

HPPLoupeGUI::~HPPLoupeGUI()
{
    delete main_widget;
}

void HPPLoupeGUI::buildMainWidget()
{
    chk_autoscale = new QCheckBox;
    chk_autoscale->setText(tr("autoscale"));

    QLabel *lbl_scale = new QLabel(tr("scale:"));
    spn_scale = new QSpinBox;
    spn_scale->setMinimum(HPPLoupeRenderer::MIN_CELL_SIZE);

    connect(chk_autoscale, SIGNAL(toggled(bool)), spn_scale, SLOT(setDisabled(bool)));
    connect(chk_autoscale, SIGNAL(toggled(bool)), this, SLOT(autoscaleToggled(bool)));
    connect(spn_scale, SIGNAL(valueChanged(int)), this, SLOT(scaleChanged(int)));
    chk_autoscale->setChecked(true);

    QHBoxLayout *laytmpscale = new QHBoxLayout;
    laytmpscale->addWidget(lbl_scale);
    laytmpscale->addWidget(spn_scale);
    // TODO: пыщ пыщ пыщ, да ололо
    QVBoxLayout *laytmpall = new QVBoxLayout;
    laytmpall->addWidget(chk_autoscale);
    laytmpall->addLayout(laytmpscale);

    main_widget = new QWidget;
    main_widget->setLayout(laytmpall);
}

void HPPLoupeGUI::autoscaleToggled(bool value)
{
    renderer->setAutoscale(value);
    if(!value)
        scaleChanged(spn_scale->value());
    else
        WindowEvent::get()->doRequireRepaint();
}

void HPPLoupeGUI::scaleChanged(int value)
{
    renderer->setScale(value);
    WindowEvent::get()->doRequireRepaint();
}
