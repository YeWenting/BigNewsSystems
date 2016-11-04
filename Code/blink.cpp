#include "blink.h"
#include <qpainter.h>

blink::blink(int x, int y, int maxDiameter, Qt::GlobalColor color, QWidget *parent)
	: QWidget(parent)
{
	if (maxDiameter == 0)
		maxDiameter = 66;
	size = maxDiameter / 2;
    change = maxDiameter / 33;
	if (change == 0)
		change = 1;
	this->maxDiameter = maxDiameter;
	t = new QTimer(this);
	this->color = color;
	this->x = x;
	this->y = y;
    this->setGeometry(QRect(0, 0, 1558, 926));
	connect(t, &QTimer::timeout, this, &blink::addSize);
    t->start(100);
}

void blink::paintEvent(QPaintEvent *event)
{
	QPainter *paint = new QPainter(this);
	paint->setPen(Qt::NoPen);
	paint->setBrush(color);
	for (int i = 0; i < (size / 2 + 1); ++i)
	{ 
		paint->setOpacity(0.03);
		paint->drawEllipse(x + i - size / 2, y + i - size / 2, size - 2 * i, size - 2 * i);
	}
	
	
}
void blink::addSize()
{
	size = size + change;
	if (size > maxDiameter)
		size = maxDiameter / 2;
	this->update();
}
