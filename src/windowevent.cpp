#include "windowevent.h"

WindowEvent::WindowEvent(QObject *_parent) :
    QObject(_parent)
{

}

WindowEvent::~WindowEvent()
{

}

WindowEvent* WindowEvent::get()
{
    static WindowEvent *obj = new WindowEvent;
    return obj;
}
