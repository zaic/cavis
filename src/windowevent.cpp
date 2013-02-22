#include "windowevent.h"

WindowEvent::WindowEvent(QObject *parent) : QObject(parent) {
}

WindowEvent::~WindowEvent() {

}

WindowEvent* WindowEvent::get() {
	static WindowEvent *obj = new WindowEvent;
	return obj;
}

void WindowEvent::doRequireRepaint() {
	emit requireRepaint();
}
