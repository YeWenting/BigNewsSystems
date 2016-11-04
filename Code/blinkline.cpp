#include "blinkLine.h"
#include <qpainter.h>
#include <cmath>

blinkLine::blinkLine(int x1, int y1, int x2, int y2, Qt::GlobalColor color, QWidget *parent)
	: QWidget(parent)
{
	t = new QTimer(this);
	this->color = color;
    add = 1;
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	if (y2 - y1 == 0)
		Vy = -1;
	else Vy = (x1 - x2) / (y2 - y1);
	change = 0;
	int x = x1 > x2 ? x2 : x1;
	int y = y1 > y2 ? y2 : y1;
    this->setGeometry(QRect(0, 0, 1558, 926));
	connect(t, &QTimer::timeout, this, &blinkLine::addSize);
    t->start(500);
}

void blinkLine::paintEvent(QPaintEvent *event)
{
	QPainter *paint = new QPainter(this);
	paint->setPen(QPen(color,4 ));
    //paint->drawLine(x1, y1, x2, y2);
	if (Vy == -1)
	{
        for (int i = 0; i < change+4; ++i)
		{
            //for (int j = 0; j < change - i; ++j)
			{
                paint->setOpacity(0.2);
                paint->setPen(QPen(color, 10+(change-i)*2));
                paint->drawLine(x1, y1  , x2, y2  );
                //paint->drawLine(x1, y1 - change + i, x2, y2 - change + i);
			}
		}
	}
	else
	{
        for (int i = 0; i < change+4; ++i)
		{
            //for (int j = 0; j < change - i; ++j)
			{
                paint->setOpacity(0.2);
                paint->setPen(QPen(color, 4+2*(change-i)));
                paint->drawLine(x1  , y1 , x2  , y2 );
                //paint->drawLine(x1 - change + i, y1 - Vy*(change - i), x2 - change + i, y2 - Vy*(change - i));
			}
		}
	}
	//for (int i = 0; i < (size / 2 + 1); ++i)
	int i = 0;
	{
		//paint->setOpacity(0.5);
	//	paint->drawLine(x + i - size / 2, y + i - size / 2, size - 2 * i, size - 2 * i);
	}


}

void blinkLine::addSize()
{
	change = change + add;
    if (change > 4 || change < 0)
		add = -1 * add;
	this->update();
}
