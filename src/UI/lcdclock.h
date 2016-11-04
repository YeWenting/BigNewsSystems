#ifndef LCDCLOCK_H
#define LCDCLOCK_H

#include <QWidget>
#include <QTime>
#include <QTimer>

extern int current_day;
extern QTime mainClock;
namespace Ui {
class LCDClock;
}

class LCDClock : public QWidget
{
    Q_OBJECT

public:
    explicit LCDClock(QWidget *parent = 0);
    ~LCDClock();

private:
    Ui::LCDClock *ui;
public slots:
    void showTime();
};

#endif // LCDCLOCK_H
