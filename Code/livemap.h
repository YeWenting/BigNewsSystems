#ifndef LIVEMAP_H
#define LIVEMAP_H

#include <QWidget>
#include"blink.h"
#include"blinkLine.h"

namespace Ui {
class LiveMap;
}

class LiveMap : public QWidget
{
    Q_OBJECT

public:
    explicit LiveMap(QWidget *parent = 0);
    ~LiveMap();
    void setBlinkPart(int,int,int,int);
    bool isActive() {
        return active;
    }
public slots:
    void setSleep() {
        active = false;
        if (b != NULL) {
            delete b;
            b = NULL;
        } else if (bl != NULL) {
            delete bl;
            bl = NULL;
        }
    }
    void setActive() {
        active = true;
    }
protected:
  //  void paintEvent(QPaintEvent *);
private:

    Ui::LiveMap *ui;
    int x1,y1,x2,y2;
    bool active;
    blinkLine *bl;
    blink *b;
};

#endif // LIVEMAP_H
