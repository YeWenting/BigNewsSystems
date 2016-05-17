//
//  TrafficNet.h
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/10.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#pragma once

#define MAXV 1000
#define MAXVALUE (1 << 27)
#define MAXTIME 24

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "people.h"

class People;
class TravelPlan;
class Item
{
public:
    std::string edgeID;         //线路名
    int startPoint;             //出发点
    int endPoint;               //目的地
    int startTime;              //出发时间(0-23 h)
    int endTime;                //到达时间(0-n h)
    int price;                  //费用
};

class Line
{
public:
    Line();
    Line(const Line &);
    Line(const std::string &, const int &, const int &, const int &, const int &);
    std::string name;                                       //线路名
    Line *NextLine;                                         //下一条边
    int tail, leaveTime, duration, cost;                    //tail该边的指向的点
};


//到达一个必经点 要从计划中删除
class City
{
public:
    Line *FirstLine;                                        //第一条边
    std::string name;                                       //名字
};

class TrafficNet
{
friend class People;
public:
    TrafficNet();
    ~TrafficNet();
    void Plan_Route(People& p);
	void Print_Edges() const;
    void Add_People();
private:
    void Init_Citys();
    void Add_Edge(const Item &);
    int  Find_City(const std::string &);
    void Run_Floyd();
    void Run_SPFA();
    void Run_DFS(People &);
    void Print_Route(const int, const std::vector<Line> &) const;
    int Move(const int &, const Line &) const;                  //在某一时刻，经某边到达另一个邻点的时刻
    
    int Get_Cost(const std::vector <int> &, const TravelPlan &) const;
    int Get_Time(const std::vector <int> &, const People &) const;                      //因为
    void Design_Route(People &);
    double Accept_Rate(const int &, const int &, const double &) const;
    void Run_SA(People &);
    void Generate_Cheap_Route(People &, const std::vector <int> &);
    void Generate_Quick_Route(People &, const std::vector <int> &);
 
    City citys[MAXV];
    std::vector <People> people;
    int num_of_city, num_of_edge, num_of_people;
    std::map<std::string, int>   cityNum;
    
    std::vector <Line> cheapRoute[MAXV][MAXV];
    int cheapWay[MAXV][MAXV];                                   //用来求两地最省钱的邻接矩阵
    
    std::vector <Line> quickRoute[MAXV][MAXV][MAXTIME];
    int quickWay[MAXV][MAXV][MAXTIME];                                    //i 城市到 j 城市 从某时刻出发 最早几点到（可超过24小时）
    
    int minMixCost;
};
