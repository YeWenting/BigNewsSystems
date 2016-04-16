//
//  People.hpp
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/15.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#ifndef People_hpp
#define People_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <deque>
#define MaxV 11

class TravelPlan                                      //存储用户旅行方案的类
{
public:
    TravelPlan();
    TravelPlan(int, int,  std::vector<int>, int);
    int source, destination, type;
    std::vector<int> station;
};

class People
{
public:
    People();
    void Simulate(const int&);                          //模拟经过多少时间 0 <= time <= 1
    void Make_Route(const std::vector<int>&);           //把计算出来的路线赋值给用户
    TravelPlan Get_Plan();
private:
    std::string name, password;
    int id;
    int location;                                       //正表示停留在某一点上，负表示停留在某条边上 abs()为下标
    int duration;                                       //下次位置转移是什么时候
    TravelPlan plan;
    std::deque<int> route;                              //存储未来的旅行路线，存储元素是边序号
};

#endif /* People_hpp */
