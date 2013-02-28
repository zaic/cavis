#pragma once

#include <QPainter>

class Layer
{
public:
	Layer();
	virtual ~Layer();

	virtual void setBuffer(QPainter *) = 0;
};
