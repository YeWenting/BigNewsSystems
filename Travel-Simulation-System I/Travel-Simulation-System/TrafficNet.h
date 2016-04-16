//
//  TrafficNet.hpp
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/10.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#pragma once

#define MapMaxV 20
#include <string>
#include <fstream>
#include <iostream>
#include"People.h"
#include"TimeTable.h"

class TrafficNet                                                //是不是有一种方法可以让整个程序只有一个实例？？
{
public:
    TrafficNet(const TimeTable&);
    ~TrafficNet();
    void Plan_Route(const People&);
private:
	void Init_Citys(const TimeTable&);
//	void Get_Cheap_Way();
//	void Get_Min_Cost();
    class Line
    {
    public:
        std::string name;                                       //线路名
        Line *NextLine;                                         //下一条边
        int tail, LeaveTime, duration, cost;                    //tail该边的指向的点
    };
    class City
    {
    public:
        Line *FirstLine;                                        //第一条边
        std::string name;                                       //名字
    };
    City citys[MapMaxV];
    int CheapWay[MapMaxV][MapMaxV];                                   //用来求两地最省钱的邻接矩阵
    int MinCost[MapMaxV][MapMaxV];                                    //用 Floyd 算法求出的最省钱路线
};


