#pragma once

#include <QListWidget>

struct
{
    QString type,//车次
            from ,//始发站
            to;//终点站
    QString start;//开始时间
    int     end;//结束时间
    QString	cost;//花费
}typedef table;//交通工具的信息

class RightList : public QListWidget//右侧时刻表
{
private:

    void QStringToTable(QString line, table &list);//QString信息转为table
public:
    RightList(QWidget *parent = 0);//初始化并且读入信息
};
