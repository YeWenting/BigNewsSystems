#pragma once
#include <QLabel>
#include <QTimer>

class blink : public QWidget
{
	Q_OBJECT
private:
	QTimer *t;
	int size;
	int x;
	int y;
	int change;
	int maxDiameter;
	Qt::GlobalColor color;
public:
	blink(int x, int y, int maxDiameter = 0, Qt::GlobalColor color = Qt::blue, QWidget *parent = 0);
	void addSize();
protected:
	void paintEvent(QPaintEvent *event);
};