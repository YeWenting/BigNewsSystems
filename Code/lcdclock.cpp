#include "lcdclock.h"
#include "ui_lcdclock.h"

LCDClock::LCDClock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LCDClock)
{
    ui->setupUi(this);
    showTime();
   // QTimer *myTimer = new QTimer(this);

   // connect(myTimer,SIGNAL(timeout()),this,SLOT(showTime()));
   // myTimer->start(166);
}



LCDClock::~LCDClock()
{
    delete ui;
}

void LCDClock::showTime() {
    QString txtTime = mainClock.toString("hh:mm");
    QString day = QString::number(current_day);
    ui->timmer->display(txtTime);
    ui->timmer_2->display(day);

}
