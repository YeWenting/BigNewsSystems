#include "dialog.h"
#include "ui_dialog.h"
#include<sstream>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    init_connection();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::accept()
{

    People p;
    TravelPlan tp;
    bool ok = true;
    bool temp;


    if (trafficNet.cityNum.find(ui->fromeEdit->text().toStdString()) == trafficNet.cityNum.end())
        ok = false;
    else
        tp.source = trafficNet.cityNum[ui->fromeEdit->text().toStdString()];

    if (trafficNet.cityNum.find(ui->toEdit->text().toStdString()) == trafficNet.cityNum.end())
        ok = false;
    else
        tp.destination = trafficNet.cityNum[ui->toEdit->text().toStdString()];

    tp.type = ui->strategyEdit->text().toInt(&temp,10);
    ok = ok && temp;
    if (!(tp.type <= 3 && tp.type >= 1))
        ok = false;

    if (tp.type == 3) {
        tp.timeLimit = ui->tlEdit->text().toInt(&temp,10);
        ok = ok && temp ;//&& (tp.timeLimit >= 10) ;
    }

    std::string temp1 = ui->textEdit->toPlainText().toStdString();
    std::string temp2;
    std::stringstream read(temp1);
    while (read>>temp2) {
        if (trafficNet.cityNum.find(temp2) != trafficNet.cityNum.end())
            tp.station.push_back(trafficNet.cityNum[temp2]);
        else
            ok = false;
    }

    p.name = ui->NameEdit->text().toStdString();
    if (p.name.size() == 0)
        ok = false;

    if (ok) {
        p.location = tp.source;
        p.plan = tp;
        emit sendPeople(p);
    } else {
        emit sendError();
    }

    QDialog::accept();
}

void Dialog::init_connection()
{
    connect(ui->confirm,SIGNAL(clicked(bool)),this,SLOT(accept()));

}


