#ifndef TRAVELSYSTEM_H
#define TRAVELSYSTEM_H

#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QStringListModel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QListWidget>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <qDebug>
#include <map>
#include <QTime>
#include <QTimer>
#include<sstream>






#include"dialog.h"
#include"dialogchange.h"
#include"dialogerror.h"
#include"dialogerror2.h"
#include"../Algorithm/people.h"
#include"rightList.h"
#include"LeftList.h"
#include"lcdclock.h"
#include"livemap.h"


extern QTime mainClock;
class TravelSystem : public QMainWindow
{

    Q_OBJECT

public:
    TravelSystem(QWidget *parent = 0);
    ~TravelSystem();

private slots:
    void openAddDialog();
    void openChangeDialog() {
        if (index <= trafficNet.people.size() - 1 && index >= 0) {
            Dialogchange *dialog2 = new Dialogchange(this);
            connect(dialog2,&Dialogchange::sendPeople,this,&TravelSystem::changeinlist);
            connect(dialog2,&Dialogchange::sendError,this,&TravelSystem::openErrorDialog);

            dialog2->show();
        } else {
            //qDebug()<<"cant do that";
        }

    }
    void openErrorDialog();
    void openError2Dialog();
    void updateMap();
    void updateClock();
    void updateLoc();
    void updateInfo(){
        if (index <= trafficNet.people.size() - 1 && index >= 0) {
            name->setText(QString::fromStdString(trafficNet.people[index].name));
            name_1->setText(QString::fromStdString(trafficNet.people[index].name));
            from->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.source]));
            from_1->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.source]));
            to->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.destination]));
            to_1->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.destination]));



            std::string loc = trafficNet.Get_Location(index);
            std::stringstream readLocation(loc);
            std::string tmp;
            std::string locPrint ;
            int i = 0;
            while(readLocation >> tmp) {
                i++;
                if (i == 2) {
                    locPrint = locPrint + " -> ";
                }
                locPrint = locPrint + tmp;
            }
            location_1->setText(QString::fromStdString(locPrint));

            if (trafficNet.people[index].route.size() == 0)
                nextCity_1->setText("Arrived");
            else
                nextCity_1->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].route[0].tail]));

            switch (trafficNet.people[index].plan.type) {
                case 1:
                    strategy->setText(QString("Cost-optimiced plan"));
                    break;
                case 2:
                    strategy->setText(QString("Time-optimiced plan"));
                    break;
                case 3:
                    strategy->setText(QString("Combined-optimiced plan"));
                    break;
            }

            if (trafficNet.people[index].plan.type != 3)
                timelimit->setText(QString("No limit"));
            else
                timelimit->setText(QString::number(trafficNet.people[index].plan.timeLimit));

            std::string routetmp;
            std::string passtmp;
            //qDebug()<<"0";



            for (auto beg = trafficNet.people[index].plan.station.begin(); beg != trafficNet.people[index].plan.station.end(); beg++) {
                if (beg == trafficNet.people[index].plan.station.begin())
                    passtmp = passtmp + trafficNet.numCity[*beg];
                else
                    passtmp = passtmp + " - " + trafficNet.numCity[*beg];
            }//qDebug()<<"1";
            if (trafficNet.people[index].plan.station.size() == 0)
                passtmp = "No station";



            for (auto beg = trafficNet.people[index].route.begin(); beg != trafficNet.people[index].route.end(); beg++) {
                routetmp = routetmp + (beg->name) + "\t";
                if (beg->name.size() < 7) routetmp = routetmp + "\t";
                routetmp = routetmp + trafficNet.numCity[beg->head] + " -> " + trafficNet.numCity[beg->tail] + "\n";
            }
            //qDebug()<<"2";
            if (trafficNet.people[index].route.size() == 0)
                routetmp = "Arrived";
            passby->setText(QString::fromStdString(passtmp));
            route->setText(QString::fromStdString(routetmp));

            cost->setText(QString("$") + QString::number(trafficNet.people[index].usedMoney));
            time->setText(QString::number(trafficNet.people[index].usedTime) + QString(" h"));


        }


    }
    void putinlist(People &p)
    {
        waitTimer->start(2000);
        part7->raise();

        if(trafficNet.Add_People(p))
            leftList->on_add(QString::fromStdString(p.name));
        else {
            openError2Dialog();
        }
    }
    void changeInfo(const QModelIndex& i) {
        leftList->setCurrentIndex(i);
        index = i.row();
        if (index <= trafficNet.people.size() - 1 && index >= 0){
            qDebug()<<"A";
            name->setText(QString::fromStdString(trafficNet.people[index].name));
            name_1->setText(QString::fromStdString(trafficNet.people[index].name));
            from->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.source]));
            from_1->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.source]));
            to->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.destination]));
            to_1->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.destination]));
            qDebug()<<"B";
            std::string loc = trafficNet.Get_Location(index);
            std::stringstream readLocation(loc);
            std::string tmp;
            std::string locPrint;
            int i = 0;
            while(readLocation>>tmp) {
                i++;
                if (i >= 2) {
                    locPrint = locPrint + " -> ";
                }
                locPrint = locPrint + tmp;
            }
            qDebug()<<"c";
            location_1->setText(QString::fromStdString(locPrint));
            if (trafficNet.people[index].route.size() == 0)
                nextCity_1->setText("Arrived");
            else
                nextCity_1->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].route[0].tail]));

            switch (trafficNet.people[index].plan.type) {
                case 1:
                    strategy->setText(QString("Cost-optimiced plan"));
                    break;
                case 2:
                    strategy->setText(QString("Time-optimiced plan"));
                    break;
                case 3:
                    strategy->setText(QString("Combined-optimiced plan"));
                    break;
            }
            qDebug()<<"D";

            if (trafficNet.people[index].plan.type != 3)
                timelimit->setText(QString("No limit"));
            else
                timelimit->setText(QString::number(trafficNet.people[index].plan.timeLimit));

            std::string routetmp;
            std::string passtmp;
            qDebug()<<"F";


            for (auto beg = trafficNet.people[index].plan.station.begin(); beg != trafficNet.people[index].plan.station.end(); beg++) {
                if (beg == trafficNet.people[index].plan.station.begin())
                    passtmp = passtmp + trafficNet.numCity[*beg];
                else
                    passtmp = passtmp + " - " + trafficNet.numCity[*beg];
            }
            if (trafficNet.people[index].plan.station.size() == 0)
                passtmp = "No station";
            //qDebug()<<"E";

            for (auto beg = trafficNet.people[index].route.begin(); beg != trafficNet.people[index].route.end(); beg++) {
                    routetmp = routetmp + (beg->name) + "\t";
                    if (beg->name.size() < 7) routetmp = routetmp + "\t";
                    routetmp = routetmp + trafficNet.numCity[beg->head] + " -> " + trafficNet.numCity[beg->tail] + "\n";
            }
            if (trafficNet.people[index].route.size() == 0)
                routetmp = "Arrived";
            //qDebug()<<"F";
            passby->setText(QString::fromStdString(passtmp));
            route->setText(QString::fromStdString(routetmp));

            cost->setText(QString("$") + QString::number(trafficNet.people[index].usedMoney));
            time->setText(QString::number(trafficNet.people[index].usedTime) + QString(" h"));

        }


    }

    void changeinlist(People& p) {

        if (index <= trafficNet.people.size() - 1 && index >= 0){
            trafficNet.people[index].plan.destination = p.plan.destination;
            trafficNet.people[index].plan.type = p.plan.type;
            trafficNet.people[index].plan.station.clear();
            trafficNet.people[index].plan.station = p.plan.station;


            trafficNet.Design_Route(trafficNet.people[index]);

            name->setText(QString::fromStdString(trafficNet.people[index].name));
            name_1->setText(QString::fromStdString(trafficNet.people[index].name));
            from->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.source]));
            from_1->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.source]));
            to->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.destination]));
            to_1->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].plan.destination]));
            std::string loc = trafficNet.Get_Location(index);
            std::stringstream readLocation(loc);
            std::string tmp;
            std::string locPrint;
            int i = 0;
            while(readLocation>>tmp) {
                i++;
                if (i >= 2) {
                    locPrint = locPrint + " -> ";
                }
                locPrint = locPrint + tmp;
            }
            location_1->setText(QString::fromStdString(locPrint));
            if (trafficNet.people[index].route.size() == 0)
                nextCity_1->setText("Arrived");
            else
                nextCity_1->setText(QString::fromStdString(trafficNet.numCity[trafficNet.people[index].route[0].tail]));

            switch (trafficNet.people[index].plan.type) {
                case 1:
                    strategy->setText(QString("Cost-optimiced plan"));
                    break;
                case 2:
                    strategy->setText(QString("Time-optimiced plan"));
                    break;
                case 3:
                    strategy->setText(QString("Combined-optimiced plan"));
                break;
            }

            if (trafficNet.people[index].plan.type != 3)
                timelimit->setText(QString("No limit"));
            else
                timelimit->setText(QString::number(trafficNet.people[index].plan.timeLimit));

            std::string routetmp;
            std::string passtmp;

            for (auto beg = trafficNet.people[index].plan.station.begin(); beg != trafficNet.people[index].plan.station.end(); beg++) {
                if (beg == trafficNet.people[index].plan.station.begin())
                    passtmp = passtmp + trafficNet.numCity[*beg];
                else
                    passtmp = passtmp + " - " + trafficNet.numCity[*beg];
            }
            if (trafficNet.people[index].plan.station.size() == 0)
                passtmp = "No station";

            for (auto beg = trafficNet.people[index].route.begin(); beg != trafficNet.people[index].route.end(); beg++) {
                routetmp = routetmp + (beg->name) + "\t";
                if (beg->name.size() < 7) routetmp = routetmp + "\t";
                routetmp = routetmp + trafficNet.numCity[beg->head] + " -> " + trafficNet.numCity[beg->tail] + "\n";
            }
            if (trafficNet.people[index].route.size() == 0)
                routetmp = "Arrived";
            passby->setText(QString::fromStdString(passtmp));
            route->setText(QString::fromStdString(routetmp));

            cost->setText(QString("$") + QString::number(trafficNet.people[index].usedMoney));
            time->setText(QString::number(trafficNet.people[index].usedTime) + QString(" h"));

        }



    }
private:
    void setupUi(QMainWindow *MainWindow);

    void retranslateUi(QMainWindow *MainWindow);

    void initConnection();

    void  getCoordinate(const std::string&,int&,int&);



    QTimer *updateTimer;

    QWidget *centralWidget;

    QWidget *part1;
    QPushButton *add;
    LeftList *leftList;


    QStringList data;
    QLabel *userLabel;
    LCDClock    *timer;


    QWidget *part2;
    QRadioButton *schedule;
    QRadioButton *map;


    QWidget *part3;
    QPushButton *change;
  //  QPushButton *deleteUser;
    QLabel *routeLabel;
    QTextEdit *route;
    QTextEdit *from;
    QTextEdit *to;
    QTextEdit *timelimit;
    QTextEdit *strategy;
    QTextEdit *name;
    QLabel *passbylabel;
    QTextEdit *passby;
    QLabel *costLabel;
    QLabel *timeLabel;
    QTextEdit *cost;
    QTextEdit *time;
    QLabel *nameLabel;
    QLabel *fromLabel;
    QLabel *Tolabel;
    QLabel *strategyLabel;
    QLabel *tlLabel;


    QWidget *part4;
    RightList *rightList;
    QWidget *listHead;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;



    QWidget *part5;
    QTextEdit *from_1;
    QTextEdit *to_1;
    QTextEdit *name_1;
    QLabel *locationLabel_1;
    QLabel *nextCityLabel_1;
    QTextEdit *location_1;
    QTextEdit *nextCity_1;
    QLabel *nameLabel_1;
    QLabel *fromLabel_1;
    QLabel *Tolabel_1;

    QWidget *part6;
    LiveMap *liveMap;


    //waiting mask
    QWidget *part7;
    QLabel *waitLabel;
    QTimer *waitTimer;

    int index;
};

#endif // TRAVELSYSTEM_H
