#include "dialogerror2.h"
#include "ui_dialogerror2.h"

Dialogerror2::Dialogerror2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogerror2)
{
    ui->setupUi(this);
    init_connection();
}

Dialogerror2::~Dialogerror2()
{
    delete ui;
}

void Dialogerror2::init_connection()
{
    connect(ui->confirm,SIGNAL(clicked(bool)),this,SLOT(accept()));

}
