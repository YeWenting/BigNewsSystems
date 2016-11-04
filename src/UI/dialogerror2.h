#ifndef DIALOGERROR2_H
#define DIALOGERROR2_H

#include <QDialog>

namespace Ui {
class Dialogerror2;
}

class Dialogerror2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogerror2(QWidget *parent = 0);
    ~Dialogerror2();

private:
    Ui::Dialogerror2 *ui;
    void init_connection();

};

#endif // DIALOGERROR2_H
