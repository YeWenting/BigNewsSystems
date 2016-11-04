#pragma once
#include <QLabel>
#include <QTimer>

class blinkLine : public QWidget
{
	Q_OBJECT
private:
	QTimer *t;
	int x1;
	int y1;
	int x2;
	int y2;
	float Vy;
	int change;
	int add;
	Qt::GlobalColor color;
public:
	blinkLine(int x1, int y1, int x2, int y2, Qt::GlobalColor color = Qt::blue, QWidget *parent = 0);
	void addSize();
protected:
	void paintEvent(QPaintEvent *event);
};