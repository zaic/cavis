#include "qtsimplebuffer.h"

QtSimpleBuffer::QtSimpleBuffer() :
    GraphicBuffer(),
    cur_buffer_type(""),
    gl_data(NULL)
{
    render_area_simple = new RenderArea;
    render_area_opengl = new OpenGLArea;

    scb_render_height = new QScrollBar(Qt::Vertical);
    QObject::connect(scb_render_height, SIGNAL(valueChanged(int)), render_area_simple, SLOT(update()));
    scb_render_width = new QScrollBar(Qt::Horizontal);
    QObject::connect(scb_render_width, SIGNAL(valueChanged(int)), render_area_simple, SLOT(update()));

    render_window = new QWidget;
    QGridLayout *lay_main = new QGridLayout;
    lay_main->setSpacing(0);
    lay_main->addWidget(render_area_simple, 0, 0);
    //lay_main->addWidget(render_area_opengl, 0, 0);
    lay_main->addWidget(scb_render_height, 0, 1);
    lay_main->addWidget(scb_render_width, 1, 0);
    scb_render_width->show();
    render_window->setLayout(lay_main);
}

QtSimpleBuffer::~QtSimpleBuffer()
{
    delete render_window;
}

void QtSimpleBuffer::create(const QString buffer_type)
{
    use_xscroll = false;
    use_yscroll = false;

    qDebug() << "[buffer/qt] new buffer type is" << buffer_type;
    render_area_simple->setVisible(buffer_type.toLower() == "simple");
    render_area_opengl->setVisible(buffer_type.toLower() == "opengl");
    if(render_area_simple->isHidden() && render_area_opengl->isHidden()) {
        qCritical() << "[buffer/qt] unsupported buffer type" << buffer_type;
        cur_buffer_type = "";
    } else {
        cur_buffer_type = buffer_type.toLower();
    }
}

void QtSimpleBuffer::prepare()
{
    scb_render_width->setVisible(use_xscroll);
    scb_render_height->setVisible(use_yscroll);

    if(cur_buffer_type == "simple") {
        // TODO SMART POINTERS!!!!111
        // call new without delete :'(
        image = new QImage(width(), height(), QImage::Format_RGB32);
        if(image == NULL) return ;
        image->fill(Qt::white);

        painter = new QPainter(image);
        if(painter == NULL) return ;

    } else if(cur_buffer_type == "opengl") {
        if(gl_data) delete[] gl_data;
        gl_data = new float[gl_sizex * gl_sizey];
    }
}

void QtSimpleBuffer::complete()
{
    if(cur_buffer_type == "simple") {
        delete painter;
        render_area_simple->drawImage(image);
    } else if(cur_buffer_type == "opengl") {
        render_area_opengl->drawDots(gl_sizex, gl_sizey, gl_data);
    }
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

void QtSimpleBuffer::update() const
{
    if(cur_buffer_type == "simple") {
        render_area_simple->update();
    } else if(cur_buffer_type == "opengl") {
        render_area_opengl->update();
    }
}
