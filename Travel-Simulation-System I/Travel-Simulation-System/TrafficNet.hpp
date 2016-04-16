//
//  TrafficNet.hpp
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/10.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#ifndef TrafficNet_hpp
#define TrafficNet_hpp

#define MaxV 20
#include <string>
#include <fstream>
#include <iostream>
#include "People.hpp"

class TrafficNet                                                //是不是有一种方法可以让整个程序只有一个实例？？
{
public:
    TrafficNet();
    ~TrafficNet();
    void Plan_Route(People);
private:
    class Line
    {
    public:
        std::string name;                                       //线路名
        Line *NextLine;                                         //下一条边
        int tail, LeaveTime, duration, cost;                          //tail该边的指向的点
    };
    class City
    {
    public:
        Line *FirstLine;                                        //第一条边
        std::string name;                                       //名字
    };
    City citys[MaxV];
    int CheapWay[MaxV][MaxV];                                   //用来求两地最省钱的邻接矩阵
    int MinCost[MaxV][MaxV];                                    //用 Floyd 算法求出的最省钱路线
};

TrafficNet net;

TrafficNet::TrafficNet()              //从文件中读入 初始化交通网
{
//    ifstream 
}

#endif /* TrafficNet_hpp */
