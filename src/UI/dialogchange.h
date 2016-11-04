#ifndef DIALOGCHANGE_H
#define DIALOGCHANGE_H

#include <QDialog>
#include"../Algorithm/people.h"
namespace Ui {
class Dialogchange;
}

class Dialogchange : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogchange(QWidget *parent = 0);
    ~Dialogchange();
signals:
    void sendPeople(People& p);
    void sendError();

private slots:
    void accept();
private:
    Ui::Dialogchange *ui;
    void init_connection();
};

#endif
