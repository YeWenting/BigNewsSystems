#ifndef DIALOGERROR_H
#define DIALOGERROR_H

#include <QDialog>

namespace Ui {
class Dialogerror;
}

class Dialogerror : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogerror(QWidget *parent = 0);
    ~Dialogerror();

private:
    Ui::Dialogerror *ui;
    void init_connection();
};

#endif // DIALOGERROR_H
