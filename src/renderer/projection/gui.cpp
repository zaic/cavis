#include "gui.h"

ProjectionGUI::ProjectionGUI(Renderer *_renderer) : RendererGUI(dynamic_cast<Renderer*>(_renderer))
{
    _renderer->setParameters(this);
    buildMainWidget();
}

ProjectionGUI::~ProjectionGUI()
{

}

QHBoxLayout* ProjectionGUI::buildScalePanel(QSpinBox*& spin_box, const char* name)
{
    QLabel *lbl_scale = new QLabel(QObject::tr(name));
    spin_box = new QSpinBox;
    spin_box->setMinimum(1);
    spin_box->setMaximum(100500);
    spin_box->setValue(100);
    spin_box->setSuffix("%");

    // TODO: move icons to another resource file
    QPushButton *btn_zoom_out = createButtonFromIcon(":/icons/zoom-out.png", 24);
    QObject::connect(btn_zoom_out, &QPushButton::clicked, [=](){ updateScale(spin_box, 0.5); });

    QPushButton *btn_zoom_in  = createButtonFromIcon(":/icons/zoom-in.png",  24);
    QObject::connect(btn_zoom_in,  &QPushButton::clicked, [=](){ updateScale(spin_box, 2.0); });

    QHBoxLayout *laytmpscale = new QHBoxLayout;
    laytmpscale->addWidget(lbl_scale);
    laytmpscale->addWidget(spin_box);
    laytmpscale->addWidget(btn_zoom_out);
    laytmpscale->addWidget(btn_zoom_in);

    return laytmpscale;
}

void ProjectionGUI::buildMainWidget()
{
    // Scale
    QHBoxLayout *lay_scale_x = buildScalePanel(x_scale, "X-scale:");
    QHBoxLayout *lay_scale_y = buildScalePanel(y_scale, "Y-scale:");

    // Interpolation
    chk_interpolation = new QCheckBox(tr("Interpolation"));
    chk_segments = new QCheckBox(tr("Segments"));
    chk_segments->setChecked(true);

    QVBoxLayout *laytmpall = new QVBoxLayout;
    laytmpall->addLayout(lay_scale_x);
    laytmpall->addLayout(lay_scale_y);
    laytmpall->addWidget(chk_interpolation);
    laytmpall->addWidget(chk_segments);

    main_widget = new QWidget;
    main_widget->setLayout(laytmpall);
}

void ProjectionGUI::updateScale(QSpinBox *spn_scale, float multiplier)
{
    int old_value = spn_scale->value();
    int new_value = old_value * multiplier;
    spn_scale->setValue(new_value);
    if(spn_scale->value() != old_value)
        WindowEvent::get()->doRequireRepaint();
}
