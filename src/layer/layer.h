#pragma once

#include <QPainter>

class Layer
{
    Layer(const Layer& );
    Layer& operator=(const Layer& );

protected:
    QPainter *painter;

public:
	Layer();
	virtual ~Layer();

    virtual void setPainter(QPainter *_painter) { painter = _painter; }
};
