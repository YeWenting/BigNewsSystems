//
//  TrafficNet.h
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/10.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#pragma once

#define ERROR           -1
#define OK              0

#define MAXV            50
#define MAXVALUE        (1 << 27)
#define MAXTIME         24
#define TIME_PER_SEC    2

#define HIGHTEMP        10000000
#define MIDTEMP         5
#define LOWTEMP         (1.00001)

#define ACTIVE -1

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include "people.h"

extern int current_time;
extern int current_day;

extern std::ofstream routeFile, eventFile;

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
    Line(const std::string &, const int &, const int &, const int &, const int &, const int &);
    std::string name;                                       //线路名
    Line *NextLine;                                         //下一条边
    int head, tail, leaveTime, duration, cost;                    //tail该边的指向的点
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
    friend class TravelSystem;
public:
    TrafficNet();
    ~TrafficNet();
	void Print_Edges() const;
    bool Add_People(People&);
    void Move_People();
    void Design_Route(People &);
    int Find_People(const std::string &);
    int Change_Plan(const std::string &, const std::string &, const int &, const std::vector <std::string> &, const int &);
    std::string Get_Location(const int &);
    std::string Get_City(const int &);
    std::map<std::string, int> cityNum;
    std::map<int,std::string > numCity;
private:
    void Init_Citys();
    void Add_Edge(const Item &);
    int  Find_City(const std::string &);
//    void Design_Route(People &);
    void Print_Route(const People &) const;
    
    int Move(const int &, const Line &) const;                  //在某一时刻，经某边到达另一个邻点的时刻
    double Accept_Rate(const int &, const int &, const double &) const;
    std::vector <Line> Generate_Cheap_Route(People &, const std::vector <int> &);
    std::vector <Line> Generate_Quick_Route(People &, const std::vector <int> &);
    
    int Get_Quick_Time(const int &, const int &, const int &);
    int Get_Route_Time(const std::vector <Line> &, const int &);
    int Get_Cost(const std::vector <int> &, const People &) const;
    int Get_Time(const std::vector <int> &, const People &, const int &) const;                      //因为
    int Get_Rough_Time(People &, const int &);
    int Get_Rough_Cost(People &);
 
    City citys[MAXV];
    std::vector <People> people;
    int num_of_city, num_of_people;
//    std::map<std::string, int> cityNum;
    
    std::vector <Line> cheapRoute[MAXV][MAXV];
    int cheapWay[MAXV][MAXV];                                   //用来求两地最省钱的邻接矩阵
    
    std::vector <Line> quickRoute[MAXV][MAXV][MAXTIME];
    int quickWay[MAXV][MAXV][MAXTIME];                                    //i 城市到 j 城市 从某时刻出发 最早几点到（可超过24小时）
    
    void Run_Floyd();
    void Run_SPFA();
    std::vector <int> Run_SA(const People &, const double &, const int & x = current_time);
    
    int minMixCost;
    std::vector <Line> bestRoute, currentRoute;
    void Run_DFS(People &, const int &, const int &);

};
