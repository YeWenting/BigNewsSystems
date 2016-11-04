#include "dialogerror.h"
#include "ui_dialogerror.h"

Dialogerror::Dialogerror(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogerror)
{
    ui->setupUi(this);
    init_connection();

}
Dialogerror::~Dialogerror()
{
    delete ui;
}

void Dialogerror::init_connection()
{
    connect(ui->confirm,SIGNAL(clicked(bool)),this,SLOT(accept()));

}
