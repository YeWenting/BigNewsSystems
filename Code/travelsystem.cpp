#include "travelsystem.h"
#include "dialog.h"
#include"people.h"
#include"trafficNet.h"
#include"rightlist.h"
#include"livemap.h"



TravelSystem::TravelSystem(QWidget *parent)
    : QMainWindow(parent)
{
    //渐变出现
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();


    setupUi(this);
    initConnection();
}

TravelSystem::~TravelSystem()
{

}

void TravelSystem::setupUi(QMainWindow *MainWindow)
{
    index = -1;
    if (MainWindow->objectName().isEmpty())
    MainWindow->setObjectName(QStringLiteral("TravelSystem"));
    MainWindow->setEnabled(true);
    MainWindow->resize(1898, 1197);
    MainWindow->setMinimumSize(QSize(1898, 1030));//原数据1197
    MainWindow->setMaximumSize(QSize(1898, 1030));//合适1030
    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
  //  centralWidget->setStyleSheet(QStringLiteral("background:rgb(183, 183, 183)"));

    updateTimer = new QTimer();
    updateTimer->start(5000);

    //part1 userlist and add button
    part1 = new QWidget(centralWidget);
    part1->setObjectName(QStringLiteral("part1"));
    part1->setGeometry(QRect(-2, 0, 341, 1203));
    part1->setStyleSheet(QLatin1String("background:rgb(255, 255, 255)\n"
""));
    add = new QPushButton(part1);
    add->setObjectName(QStringLiteral("add"));
    add->setGeometry(QRect(11, 60, 50, 50));
    add->setStyleSheet(QLatin1String("background:rgb(255,255 , 255);\n"
"color:rgb(57, 154, 214);\n"
"font: 20pt \"Consolas\";\n"
"border:2px  rgb(255,255,255);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    add->setFlat(false);




    leftList = new LeftList(part1);
    leftList->setObjectName(QStringLiteral("leftList"));
    leftList->setGeometry(QRect(0, 115, 342, 841));//(QRect(0, 115, 342, 1001)
    leftList->setStyleSheet(QLatin1String("background:rgb(255,255 , 255);\n"
"border:2px  rgb(255,255,255);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));




    userLabel = new QLabel(part1);
    userLabel->setObjectName(QStringLiteral("userLabel"));
    userLabel->setGeometry(QRect(90, 75, 131, 31));
    userLabel-> setStyleSheet(QLatin1String("font: 10pt \"Consolas\";\n"
"color:rgb(102, 102, 102);"));
    timer = new LCDClock(this);
    timer->setGeometry(QRect(0,991,342,76));//QRect(0,1141,342,76)

    //part2
    part2 = new QWidget(centralWidget);
    part2->setObjectName(QStringLiteral("part2"));
    part2->setGeometry(QRect(340, -40, 1561, 121));//    上排选择按钮     QRect(340, -3, 1561, 121)
    part2->setStyleSheet(QStringLiteral("background:rgb(255, 255, 255)"));
    schedule = new QRadioButton(part2);
    schedule->setObjectName(QStringLiteral("schedule"));
    schedule->setGeometry(QRect(545, 50, 174, 51));
    schedule->setStyleSheet(QLatin1String("background:rgb(255,255 , 255);\n"
"color:rgb(57, 154, 214);\n"
"font: 75 10pt \"Consolas\";\n"
"border:2px  rgb(255,255,255);\n"
"border-radius:2px;\n"
"padding:1px 2px;"));
    schedule->setChecked(true);



    map = new QRadioButton(part2);
    map->setObjectName(QStringLiteral("map"));
    map->setGeometry(QRect(720, 50, 174, 51));
    map->setStyleSheet(QLatin1String("background:rgb(255,255 , 255);\n"
"color:rgb(57, 154, 214);\n"
"font: 75 10pt \"Consolas\";\n"
"border:2px  rgb(255,255,255);\n"
"border-radius:2px;\n"
"padding:2px 4px;"));
    map->setIconSize(QSize(32, 32));
    map->setChecked(false);



    //part3 schedule top
    part3 = new QWidget(centralWidget);
    part3->setObjectName(QStringLiteral("part3"));
    part3->setGeometry(QRect(340, 78, 1561, 302));//      信息栏           QRect(340, 118, 1561, 352)
    part3->setStyleSheet(QStringLiteral("background:rgb(51, 51, 51)"));
    change = new QPushButton(part3);
    change->setObjectName(QStringLiteral("change"));
    change->setGeometry(QRect(1300, 230, 150, 46));//QRect(1300, 256, 150, 46)
    change->setStyleSheet(QLatin1String("background:rgb(77, 77, 77);\n"
"color:rgb(243, 243, 243);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
//    deleteUser = new QPushButton(part3);
//    deleteUser->setObjectName(QStringLiteral("change"));
//    deleteUser->setGeometry(QRect(1300, 266, 150, 46));
//    deleteUser->setStyleSheet(QLatin1String("background:rgb(77, 77, 77);\n"
//"color:rgb(243, 243, 243);\n"
//"font: 9pt \"Consolas\";\n"
//"border:2px  rgb(77,77,77);\n"
//"border-radius:10px;\n"
//"padding:2px 4px;"));
    routeLabel = new QLabel(part3);
    routeLabel->setObjectName(QStringLiteral("routeLabel"));
    routeLabel->setGeometry(QRect(836, 47, 108, 24));
    routeLabel->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    route = new QTextEdit(part3);
    route->setObjectName(QStringLiteral("route"));
    route->setGeometry(QRect(830, 70, 711, 131));
    route->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    route->setReadOnly(true);
    from = new QTextEdit(part3);
    from->setObjectName(QStringLiteral("from"));
    from->setGeometry(QRect(170, 92, 141, 41));
    from->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    from->setReadOnly(true);
    to = new QTextEdit(part3);
    to->setObjectName(QStringLiteral("to"));
    to->setGeometry(QRect(171, 142, 171, 41));
    to->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    to->setReadOnly(true);
    timelimit = new QTextEdit(part3);
    timelimit->setObjectName(QStringLiteral("timelimit"));
    timelimit->setGeometry(QRect(558, 143, 221, 41));
    timelimit->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    timelimit->setReadOnly(true);
    strategy = new QTextEdit(part3);
    strategy->setObjectName(QStringLiteral("strategy"));
    strategy->setGeometry(QRect(448, 90, 381, 41));
    strategy->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    strategy->setReadOnly(true);
    name = new QTextEdit(part3);
    name->setObjectName(QStringLiteral("name"));
    name->setGeometry(QRect(170, 44, 221, 41));
    name->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    name->setReadOnly(true);
    passbylabel = new QLabel(part3);
    passbylabel->setObjectName(QStringLiteral("passbylabel"));
    passbylabel->setGeometry(QRect(70, 200, 108, 24));
    passbylabel->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    passby = new QTextEdit(part3);
    passby->setObjectName(QStringLiteral("passby"));
    passby->setGeometry(QRect(61, 240, 461, 71));
    passby->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    passby->setReadOnly(true);
    costLabel = new QLabel(part3);
    costLabel->setObjectName(QStringLiteral("costLabel"));
    costLabel->setGeometry(QRect(616, 250, 77, 21));
    costLabel->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    timeLabel = new QLabel(part3);
    timeLabel->setObjectName(QStringLiteral("timeLabel"));
    timeLabel->setGeometry(QRect(880, 250, 77, 21));
    timeLabel->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    cost = new QTextEdit(part3);
    cost->setObjectName(QStringLiteral("cost"));
    cost->setGeometry(QRect(695, 240, 111, 41));
    cost->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    cost->setReadOnly(true);
    time = new QTextEdit(part3);
    time->setObjectName(QStringLiteral("time"));
    time->setGeometry(QRect(981, 240, 111, 41));
    time->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    time->setReadOnly(true);
    nameLabel = new QLabel(part3);
    nameLabel->setObjectName(QStringLiteral("nameLabel"));
    nameLabel->setGeometry(QRect(70, 50, 77, 27));
    nameLabel->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    fromLabel = new QLabel(part3);
    fromLabel->setObjectName(QStringLiteral("fromLabel"));
    fromLabel->setGeometry(QRect(70, 100, 70, 27));
    fromLabel->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    Tolabel = new QLabel(part3);
    Tolabel->setObjectName(QStringLiteral("Tolabel"));
    Tolabel->setGeometry(QRect(70, 150, 38, 27));
    Tolabel->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    strategyLabel = new QLabel(part3);
    strategyLabel->setObjectName(QStringLiteral("strategyLabel"));
    strategyLabel->setGeometry(QRect(410, 50, 100, 27));
    strategyLabel->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    tlLabel = new QLabel(part3);
    tlLabel->setObjectName(QStringLiteral("tlLabel"));
    tlLabel->setGeometry(QRect(410, 150, 115, 27));
    tlLabel->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    change->raise();
  //  deleteUser->hide();
    routeLabel->raise();
    route->raise();
    from->raise();
    to->raise();
    name->raise();
    timelimit->raise();
    strategy->raise();
    passbylabel->raise();
    passby->raise();
    costLabel->raise();
    timeLabel->raise();
    cost->raise();
    time->raise();

    //part4 the timetable page
    part4 = new QWidget(centralWidget);
    part4->setObjectName(QStringLiteral("part4"));
    part4->setGeometry(QRect(340, 380, 1571, 733));//QRect(340, 470, 1571, 733)

    //part4->setStyleSheet(QLatin1String("background:rgb(255, 255, 255)\n"""));
    rightList = new RightList(part4);
    rightList->setGeometry(QRect(0, 40, 1560, 611));//QRect(0, 40, 1560, 691)
    rightList->setObjectName(QStringLiteral("rightList"));
    rightList->setStyleSheet(QLatin1String("border:0px ;\n""font: 11pt \"Consolas\";\n"""));

    listHead = new QWidget(part4);
    listHead->setGeometry(QRect(0,0,1571,40));
    listHead->setStyleSheet(QLatin1String("background:rgb(255,255,255);\n"
                                          "font:\"Consolas\";\n"));

    label1 = new QLabel(listHead);
    label1->setGeometry(QRect(210,0,200,40));//QRect(250,0,200,40)
    label1->setText(QString("No."));

    label2 = new QLabel(listHead);
    label2->setGeometry(QRect(440,0,200,40));//QRect(450,0,200,40)
    label2->setText(QString("Beginning City"));

    label3 = new QLabel(listHead);
    label3->setGeometry(QRect(670,0,200,40));//QRect(690,0,200,40)
    label3->setText(QString("Terminal City"));

    label4 = new QLabel(listHead);
    label4->setGeometry(QRect(895,0,200,40));//QRect(900,0,200,40)
    label4->setText(QString("Departure Time"));

    label5 = new QLabel(listHead);
    label5->setGeometry(QRect(1130,0,200,40));//QRect(1150,0,200,40)
    label5->setText(QString("Arrival Time"));

    label6 = new QLabel(listHead);
    label6->setGeometry(QRect(1355,0,200,40));//QRect(1390,0,200,40)
    label6->setText(QString("Cost"));


    label1->raise();
    label2->raise();
    label3->raise();
    label4->raise();
    label5->raise();
    label6->raise();





    //part 5 the map page top
    part5 = new QWidget(centralWidget);
    part5->setObjectName(QStringLiteral("part5"));
    part5->setGeometry(QRect(340, 88, 1561, 151));//QRect(340, 118, 1561, 151)
    part5->setStyleSheet(QStringLiteral("background:rgb(51, 51, 51)"));
    from_1 = new QTextEdit(part5);
    from_1->setObjectName(QStringLiteral("from_1"));
    from_1->setGeometry(QRect(340, 50, 181, 40));
    from_1->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    from_1->setReadOnly(true);
    to_1 = new QTextEdit(part5);
    to_1->setObjectName(QStringLiteral("to_1"));
    to_1->setGeometry(QRect(610, 50, 171, 40));//QRect(610, 80, 171, 40)
    to_1->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    to_1->setReadOnly(true);
    name_1 = new QTextEdit(part5);
    name_1->setObjectName(QStringLiteral("name_1"));
    name_1->setGeometry(QRect(61, 50, 211, 40));
    name_1->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    name_1->setReadOnly(true);
    locationLabel_1 = new QLabel(part5);
    locationLabel_1->setObjectName(QStringLiteral("locationLabel_1"));
    locationLabel_1->setGeometry(QRect(849, 20, 111, 27));
    locationLabel_1->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    nextCityLabel_1 = new QLabel(part5);
    nextCityLabel_1->setObjectName(QStringLiteral("nextCityLabel_1"));
    nextCityLabel_1->setGeometry(QRect(1214, 20, 111, 27));
    nextCityLabel_1->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    location_1 = new QTextEdit(part5);
    location_1->setObjectName(QStringLiteral("location_1"));
    location_1->setGeometry(QRect(840, 50, 341, 40));
    location_1->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    location_1->setReadOnly(true);
    nextCity_1 = new QTextEdit(part5);
    nextCity_1->setObjectName(QStringLiteral("nextCity_1"));
    nextCity_1->setGeometry(QRect(1205, 50, 241, 40));
    nextCity_1->setStyleSheet(QLatin1String("background:rgb(51, 51, 51);\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Consolas\";\n"
"border:2px  rgb(77,77,77);\n"
"border-radius:10px;\n"
"padding:2px 4px;"));
    nextCity_1->setReadOnly(true);
    nameLabel_1 = new QLabel(part5);
    nameLabel_1->setObjectName(QStringLiteral("nameLabel_1"));
    nameLabel_1->setGeometry(QRect(70, 20, 77, 27));
    nameLabel_1->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    fromLabel_1 = new QLabel(part5);
    fromLabel_1->setObjectName(QStringLiteral("fromLabel_1"));
    fromLabel_1->setGeometry(QRect(348, 20, 77, 27));
    fromLabel_1->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
    Tolabel_1 = new QLabel(part5);
    Tolabel_1->setObjectName(QStringLiteral("Tolabel_1"));
    Tolabel_1->setGeometry(QRect(614, 20, 77, 27));
    Tolabel_1->setStyleSheet(QLatin1String("\n"
"color:rgb(135, 139, 141);\n"
"font: 9pt \"Arial\";\n"
""));
   // part5->hide();

    //part6 the map page
    part6 = new QWidget(centralWidget);
    part6->setObjectName(QStringLiteral("part6"));
    part6->setGeometry(QRect(340, 191, 1558, 926));//QRect(340, 271, 1558, 926)
//    part6->setStyleSheet(QLatin1String("background:rgb(255, 255, 255)\n"
//""));
    liveMap = new LiveMap(part6);
    liveMap->setObjectName(QStringLiteral("liveMap"));
    liveMap->setGeometry(QRect(0,0,1557,926));
    liveMap->raise();


    part7 = new QWidget(centralWidget);
    part7->setGeometry(QRect(0,0,1898,1030));
    part7->setWindowOpacity(0.7);
    part7->setStyleSheet(QStringLiteral("background:rgb(255, 255, 255)"));
    waitLabel = new QLabel(part7);
    waitLabel->setGeometry(QRect(650,300,1051,261));
    waitLabel->setStyleSheet(QLatin1String("font: 35pt \"Agency FB\";"));
    waitLabel->setText("Waiting for caculating route . . . . . .");
    waitTimer = new QTimer();
    waitTimer->setSingleShot(true);

    //part6->hide();
    part3->raise();
    part4->raise();

    part7->lower();




    MainWindow->setCentralWidget(centralWidget);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void TravelSystem::retranslateUi(QMainWindow *MainWindow)
{

    MainWindow->setWindowTitle(QApplication::translate("    Travel System", "  Travel System", 0));
    MainWindow->setWindowIcon(QIcon(QStringLiteral(":/travelsystem/map")));
    add->setText(QApplication::translate("MainWindow", "+", 0));
    userLabel->setText(QApplication::translate("MainWindow", "UserList", 0));
    schedule->setText(QApplication::translate("MainWindow", "SCHEDULE", 0));
    map->setText(QApplication::translate("MainWindow", "  MAP", 0));
    change->setText(QApplication::translate("Widget", "change", 0));
   // deleteUser->setText(QApplication::translate("MainWindow", "delete", 0));
    routeLabel->setText(QApplication::translate("Widget", "Route :", 0));
    route->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">BeiJing - ShangHai - FuZhou - BeiJing - ShangHai - FuZhou - BeiJing - ShangHai - FuZhou - BeiJing - ShangHai - FuZhou - BeiJing - ShangHai - FuZhou - BeiJing - ShangHai -&gt; FuZhou - BeiJing - ShangHai</p></body></html>", 0));
    from->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">changchun</p></body></html>", 0));
    to->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">huhehaote</p></body></html>", 0));
    timelimit->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4h</p></body></html>", 0));
    strategy->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Mini Cost with limit</p></body></html>", 0));
    name->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">dongshenghua</p></body></html>", 0));
    passbylabel->setText(QApplication::translate("Widget", "PassBy :", 0));
    passby->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">BeiJing ShangHai FuZhou guangzhou shenzhen</p></body></html>", 0));
    costLabel->setText(QApplication::translate("Widget", "Cost :", 0));
    timeLabel->setText(QApplication::translate("Widget", "Time :", 0));
    cost->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1000$</p></body></html>", 0));
    time->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">4h</p></body></html>", 0));
    nameLabel->setText(QApplication::translate("Widget", "Name :", 0));
    fromLabel->setText(QApplication::translate("Widget", "From :", 0));
    Tolabel->setText(QApplication::translate("Widget", "To :", 0));
    strategyLabel->setText(QApplication::translate("Widget", "Plan :", 0));
    tlLabel->setText(QApplication::translate("Widget", "TimeLimit :", 0));
    from_1->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">huhehaotebj</p></body></html>", 0));
    to_1->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">huhehaote</p></body></html>", 0));
    name_1->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">dongshenghua</p></body></html>", 0));
    locationLabel_1->setText(QApplication::translate("Widget", "Location :", 0));
    nextCityLabel_1->setText(QApplication::translate("Widget", "NextCity:", 0));
    location_1->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">huhehaote -&gt; hangzhou</p></body></html>", 0));
    nextCity_1->setHtml(QApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Consolas'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">huhehaotedong</p></body></html>", 0));
    nameLabel_1->setText(QApplication::translate("Widget", "Name :", 0));
    fromLabel_1->setText(QApplication::translate("Widget", "From :", 0));
    Tolabel_1->setText(QApplication::translate("Widget", "To :", 0));
} // retranslateUi

void TravelSystem::initConnection()
{

    connect(schedule,SIGNAL(toggled(bool)),part3,SLOT(raise()));
    connect(schedule,SIGNAL(toggled(bool)),part4,SLOT(raise()));
    connect(schedule,SIGNAL(toggled(bool)),liveMap,SLOT(setSleep()));

    connect(map,SIGNAL(toggled(bool)),part5,SLOT(raise()));
    connect(map,SIGNAL(toggled(bool)),part6,SLOT(raise()));
    connect(map,SIGNAL(toggled(bool)),liveMap,SLOT(setActive()));
    connect(map,SIGNAL(toggled(bool)),this,SLOT(updateMap()));

    connect(add,SIGNAL(clicked(bool)),this,SLOT(openAddDialog()));
    connect(change,SIGNAL(clicked(bool)),this,SLOT(openChangeDialog()));


    connect(leftList,SIGNAL(clicked(const QModelIndex&)),this,SLOT(changeInfo(const QModelIndex&)));
    connect(leftList,SIGNAL(clicked(const QModelIndex&)),this,SLOT(updateMap()));

    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updateClock()));
    connect(updateTimer,SIGNAL(timeout()),timer,SLOT(showTime()));
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updateLoc()));
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updateInfo()));
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updateMap()));
   // connect(updateTimer,SIGNAL(timeout()),updateTimer,SLOT(start()));

    connect(waitTimer,SIGNAL(timeout()),part7,SLOT(lower()));


}

//wait for typing



void TravelSystem::openAddDialog()
{
    Dialog *dialog1 = new Dialog(this);
    connect(dialog1,&Dialog::sendPeople,this,&TravelSystem::putinlist);
    connect(dialog1,&Dialog::sendError,this,&TravelSystem::openErrorDialog);
    dialog1->show();
}

void TravelSystem::openErrorDialog()
{
    Dialogerror *dialog3 = new Dialogerror(this);

    dialog3->exec();
}

void TravelSystem::openError2Dialog()
{
    Dialogerror2 *dialog4 = new Dialogerror2(this);

    dialog4->exec();
}
void TravelSystem::updateClock()
{
    mainClock = mainClock.addSecs(3600);
    current_time ++;
    if (current_time >= MAXTIME)
    {
        current_time = 0;
        current_day++;
    }
}

void TravelSystem::updateLoc()
{
    trafficNet.Move_People();
    //qDebug()<<"kobe"<<" "<<current_time;
}

void TravelSystem::updateMap()
{

    if (index >= 0 && index < trafficNet.people.size() && liveMap->isActive()) {
        // updateMap
        int x1,y1,x2,y2;
        std::string loc = trafficNet.Get_Location(index);
        std::stringstream readLocation(loc);
        std::string tmp;
        std::string locPrint;
        int i = 0;
        while(readLocation>>tmp) {
            i++;
        }
        if (i == 1) {

            getCoordinate(loc,x1,y1);
            if (trafficNet.people[index].route.size() == 0)
                liveMap->setBlinkPart(x1,y1,-1,-1);
            else
                liveMap->setBlinkPart(x1,y1,0,0);
        } else {
            std::stringstream read(loc);
            read>>tmp;
            getCoordinate(tmp,x1,y1);
            read>>tmp;
            getCoordinate(tmp,x2,y2);
            liveMap->setBlinkPart(x1,y1,x2,y2);
        }
    }
}

void TravelSystem::getCoordinate(const std::string &s, int &x, int &y)
{
    qDebug()<<"checking";
    if (s == "Beijing") {
        x = 957;
        y = 340;
    } else if (s == "Haerbin") {
        x = 1208;
        y = 136;
    } else if (s == "Huhehaote") {
        x = 841;
        y = 296;
    } else if (s == "Wulumuqi") {
        x = 266;
        y = 221;
    } else if (s == "Xining") {
        x = 605;
        y = 446;
    } else if (s == "Zhengzhou") {
        x = 861;
        y = 530;
    } else if (s == "Shanghai") {
        x = 1075;
        y = 595;
    } else if (s == "Nanjing") {
        x = 1017;
        y = 565;
    } else if (s == "Chengdu") {
        x = 680;
        y = 609;
    } else if (s == "Guangzhou") {
        x = 923;
        y = 813;
    } else if (s == "Fuzhou") {
        x = 1023;
        y = 733;
    } else if (s == "Changsha") {
        x = 870;
        y = 700;
    } else if (s == "Nanning") {
        x = 765;
        y = 815;
    } else if (s == "Lasa") {
        x = 340;
        y = 603;
    } else {
        x = 0;
        y = 0;
    }

}
