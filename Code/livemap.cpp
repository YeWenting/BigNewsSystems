#include "livemap.h"
#include "ui_livemap.h"
#include<QPalette>
#include<QPainter>
#include<QDebug>

LiveMap::LiveMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LiveMap)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/travelsystem/livemap")));
    setPalette(palette);
    x1 = x2 = y1 = y2 = 0;
    active = false;
    b = NULL;
    bl = NULL;
}

LiveMap::~LiveMap()
{
    delete ui;
}
void LiveMap::setBlinkPart(int a1,int b1,int a2,int b2)
{
    x1 = a1;
    y1 = b1;
    x2 = a2;
    y2 = b2;
    qDebug()<< x1 << " "<<y1 <<" " <<x2 <<" " <<y2;
    if ((x1 == 0 && y1 == 0)&& (x2 == 0 && y2 == 0)) {
        active = false;
        //delete blink part
        qDebug()<<"eat shit";
    } else if ((x1 != 0 || y1 != 0) && (x2 == -1 && y2 == -1)) {
        active = true;
        if (b != NULL) {
            delete b;
            b = NULL;
        } else if (bl != NULL) {
            delete bl;
            bl = NULL;
        }
        b = new blink(x1,y1,120,Qt::red,this);
        b->show();
        qDebug()<<"on the end"<<x1<<" "<<y1;
        //delete old new a blink point in red arrived
    } else if ((x1 != 0 || y1 != 0) && (x2 == 0 && y2 == 0)) {
        active = true;
        if (b != NULL) {
            delete b;
            b = NULL;
        } else if (bl != NULL) {
            delete bl;
            bl = NULL;
        }
        b = new blink(x1,y1,120,Qt::blue,this);
        b->show();
        qDebug()<<"on the point"<<x1<< " "<<y1;
        //delete old new a blink point in blue waie for moving
    } else {
        active = true;
        if (b != NULL) {
            delete b;
            b = NULL;
        } else if (bl != NULL) {
            delete bl;
            bl = NULL;
        }
        //340 271
        bl = new blinkLine(x1,y1,x2,y2,Qt::blue,this);
        bl->show();
        qDebug()<<"on the way";
        //delete old new a blink edge from x to y;
    }
}




//void LiveMap::paintEvent(QPaintEvent *event)
//{
//    QPainter painter;
//    QPixmap *background = new QPixmap(":/travelsystem/livemap");
//    painter.drawPixmap(0,0,1158,926,*background);
//}
