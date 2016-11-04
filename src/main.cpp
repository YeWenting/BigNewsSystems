#include "UI/travelsystem.h"
#include"Algorithm/trafficNet.h"
#include <QApplication>
#include<fstream>
//#include"blink.h"

TrafficNet trafficNet;

int current_time = 0;
int current_day  = 0;

std::ifstream infile("input.txt");
std::ofstream routeFile("route.log"), eventFile("event.log");

QTime mainClock(00,00,00);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 //   LeftList w;
   // mainClock = new QTime(00,00,00);
    TravelSystem w;
   // blink *w = new blink(50,50,100,Qt::blue);
    //w->show();
    w.show();

    return a.exec();
}
