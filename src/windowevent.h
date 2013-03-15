#pragma once

#include <QObject>

class WindowEvent : public QObject
{
	Q_OBJECT

	explicit WindowEvent(QObject *_parent = NULL);
	WindowEvent(const WindowEvent&);
	WindowEvent& operator=(const WindowEvent&);
public:
	~WindowEvent();

	static WindowEvent* get();
	
    void doRequireRepaint() { emit requireRepaint(); }

signals:
	void requireRepaint();
	
public slots:
	
};
