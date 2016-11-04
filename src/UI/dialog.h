#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"../Algorithm/people.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);

    ~Dialog();

signals:
    void sendPeople(People& p);
    void sendError();

private slots:
    void accept();
private:
    Ui::Dialog *ui;
    void init_connection();

};

#endif // DIALOG_H
