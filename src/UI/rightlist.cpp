#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <qlabel.h>
#include <QString>
#include <qfile.h>
#include <qtextstream.h>
#include <sstream>
#include "rightList.h"

#define bus 0
#define plane 1
#define train 2

RightList::RightList(QWidget *parent)
    :QListWidget(parent)
{
    //qDebug()<<"yes";
    QFile data("./bin/list_e.txt");//打开文件
    data.open(QFile::ReadOnly);
    QTextStream in(&data);
//    //qDebug()<<"hi";
    ////qDebug()<<"no";


    QVector<QString> list;

    int i = 0;//读入数据并排序
    while (!in.atEnd())
    {
        QString line = in.readLine();
        list.push_back(line);
        ++i;
    }
    data.close();
    qSort(list.begin(), list.end());

    for (int j = 0; j<i; ++j)
    {
        table m_list;
        QStringToTable(list[j], m_list);//将数据转化为table

        int t;
        if (m_list.type[2] <= 'Z' && m_list.type[2] >= 'A')
            t = bus;
        else if (m_list.type[1] <= 'Z' && m_list.type[1] >= 'A')
            t = plane;
        else t = train;
        QString tool[3] = {QStringLiteral(":/travelsystem/busIcon"),QStringLiteral(":/travelsystem/planeIcon"),QStringLiteral(":/travelsystem/trainIcon") };
        QListWidgetItem* lst1 = new QListWidgetItem(QIcon(tool[t]), "", this);//打开相应图片
        lst1->setSizeHint(QSize(lst1->sizeHint().width(), 98));//调 整item大小


        QLabel *box = new QLabel;//所有元素的显示父模块
       // box->setFrameShadow(QFrame::WinPanel);

        QLabel *m_type = new QLabel(m_list.type, box);//显示车次并调整位置
        m_type->setGeometry(QRect(130, 0, 200, 98));


        QLabel *m_from = new QLabel(m_list.from, box);//显示始发站并调整位置
        m_from->setGeometry(QRect(360, 0, 200, 98));

        QLabel *m_to = new QLabel(m_list.to, box);//显示终点站并调整位置
        m_to->setGeometry(QRect(590, 0, 200, 98));

        QLabel *m_start = new QLabel(m_list.start + ":00", box);//显示开始时间并调整位置
        m_start->setGeometry(QRect(820, 0, 200, 98));


        int past_day;
        past_day = m_list.end / 24;
        m_list.end = m_list.end % 24;
        QString n_end = QString::number(m_list.end, 10);
        QLabel *m_end;
        if (past_day)
            m_end = new QLabel(QString::fromLocal8Bit("Day") + QString::number(past_day + 1, 10) + " " + n_end + ":00", box);
        else m_end = new QLabel(n_end + ":00", box);
        m_end->setGeometry(QRect(1050, 0, 200, 98));//显示到达时间车次并调整位置

        QLabel *m_cost = new QLabel(QString("$") + m_list.cost, box);
        m_cost->setGeometry(QRect(1280, 0, 200, 98));//显示花费并调整位置

        this->setItemWidget(lst1, box);
    }
    this->setIconSize(QSize(70, 70));//调整图片大小
}

void RightList::QStringToTable(QString line, table &list)
{
    std::string type, from, to, start, cost;
    std::string m_line = line.toStdString();
    std::stringstream work(m_line);
    work >> type >> from >> to >> start >> list.end >> cost;
    list.type = QString::fromStdString(type);
    list.from = QString::fromStdString(from);
    list.to = QString::fromStdString(to);
    list.start = QString::fromStdString(start);
    list.cost = QString::fromStdString(cost);
}
