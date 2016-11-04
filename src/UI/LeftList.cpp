#include "LeftList.h"


MyItem::MyItem(const QIcon &icon, const QString &text, int ID, QListWidget *view) : QListWidgetItem(icon, text, view, 0)
{
	this->ID = ID;
}

int MyItem::getID()
{
	return ID;
}

LeftList::LeftList(QWidget *parent) :QListWidget(parent)
{
	number = 0;
}

void LeftList::GetItemXXXX()
{
	//this->currentItem();
}

//void LeftList::on_add(QString tmp)
//{
//    MyItem *item = new MyItem(QIcon("XXXX"), tmp, number, this);
//	item->setSizeHint(QSize(item->sizeHint().width(), 98));//调整item大小
//	++number;
//}

void LeftList::on_del()
{
	this->takeItem(this->currentRow());
}
