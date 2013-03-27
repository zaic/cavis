#include "qtsimplebuffer.h"

QtSimpleBuffer::QtSimpleBuffer() : GraphicBuffer()
{
#ifndef BUFFER_OPENGL
    render_area = new RenderArea;
#else
    render_area = new OpenGLArea;
#endif

    scroll_area = new QScrollArea;
    //scroll_area->setWidget(qobject_cast<QWidget*>(render_area));

    scb_render_height = scroll_area->verticalScrollBar();
    scb_render_height = new QScrollBar(Qt::Vertical);
    QObject::connect(scb_render_height, SIGNAL(valueChanged(int)), render_area, SLOT(update()));
    scb_render_width = scroll_area->horizontalScrollBar();
    scb_render_width = new QScrollBar(Qt::Horizontal);
    QObject::connect(scb_render_width, SIGNAL(valueChanged(int)), render_area, SLOT(update()));

    /*render_window = qobject_cast<QWidget*>(scroll_area);
    render_window = render_area;*/

#if 1
    render_window = new QWidget;
    QGridLayout *lay_main = new QGridLayout;
    lay_main->setSpacing(0);
    lay_main->addWidget(render_area, 0, 0);
    lay_main->addWidget(scb_render_height, 0, 1);
    lay_main->addWidget(scb_render_width, 1, 0);
    scb_render_width->show();
    render_window->setLayout(lay_main);
#else
    render_window = qobject_cast<QWidget*>(scroll_area);
    //scroll_area->setWidget(render_area);
    scroll_area->show();
    render_area->show();
    //scb_render_height->hide();
    //scb_render_width->hide();
    qDebug() << "[buffer/qt] viewport_size" << scroll_area->viewport()->width() << scroll_area->viewport()->height();
#endif

    // TODO: fix hack
#if 0
    render_window->show();
    render_window->resize(800, 600);
#endif
}

QtSimpleBuffer::~QtSimpleBuffer()
{
    delete scroll_area;
}

void QtSimpleBuffer::create()
{
    use_xscroll = false;
    use_yscroll = false;
}

void QtSimpleBuffer::prepare()
{
    scb_render_width->setVisible(use_xscroll);
    scb_render_height->setVisible(use_yscroll);

    // TODO SMART POINTERS!!!!111
    // call new without delete :'(
    image = new QImage(width(), height(), QImage::Format_RGB32);
    if(image == NULL) return ;
    image->fill(Qt::white);

    painter = new QPainter(image);
    if(painter == NULL) return ;
}

void QtSimpleBuffer::complete()
{
    delete painter;
    render_area->drawImage(image);
    //scroll_area->update();
}

void QtSimpleBuffer::setXScroll(int max_value, int current_value)
{
    if(max_value == GraphicBuffer::SCROLL_DISABLE) {
        use_xscroll = false;
    } else {
        use_xscroll = true;
        scb_render_width->setMaximum(max_value);
        if(current_value != GraphicBuffer::SCROLL_PREVIOUS_VALUE)
            scb_render_width->setValue(current_value);
    }
}

void QtSimpleBuffer::setYScroll(int max_value, int current_value)
{
    if(max_value == GraphicBuffer::SCROLL_DISABLE) {
        use_yscroll = false;
    } else {
        use_yscroll = true;
        scb_render_height->setMaximum(max_value);
        if(current_value != GraphicBuffer::SCROLL_PREVIOUS_VALUE)
            scb_render_height->setValue(current_value);
    }
}
