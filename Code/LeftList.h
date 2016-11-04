#include <QLabel.h> 
#include <qlistwidget.h>

class MyItem : public QObject, public QListWidgetItem
{
    Q_OBJECT

public:
    MyItem(const QIcon &icon, const QString &text, int ID, QListWidget *view = Q_NULLPTR);
    int getID();
private:
    int ID;
};

class LeftList : public QListWidget
{
	Q_OBJECT

public:
	LeftList(QWidget *parent = NULL);
private:
	int number;

public slots:
	void GetItemXXXX();
    void on_add(QString tmp)
    {
        MyItem *item = new MyItem(QIcon("XXXX"), tmp, number, this);
        item->setSizeHint(QSize(item->sizeHint().width(),75));//调整item大小
        //item->setTextAlignment(Qt::AlignCenter);
        item->setIcon(QIcon(QStringLiteral(":/travelsystem/guest")));


        ++number;
    }
	void on_del();
};


