//
//  People.h
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/15.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#ifndef People_hpp
#define People_hpp

#define DEPART 0
#define ARRIVE 1
#define FINISH 2

#define CLIENT_SLEEP -1

#include <stdio.h>
#include <string>
#include <vector>

#include "trafficnet.h"

class Line;
class TrafficNet;
extern TrafficNet trafficNet;

class TravelPlan
{
public:
    TravelPlan();
    TravelPlan(int, int, std::vector<int>, int);
    int source, destination, type;
    std::vector<int> station;
    int timeLimit;
};
class TravelSystem;
class Dialog;
class People
{
friend class TrafficNet;
friend class TravelSystem;
friend class Dialog;
friend class Dialogchange;
public:
    People();
    std::string Get_Location();
private:
    std::string name;
    int location;
    TravelPlan plan;
    std::vector<Line> route;                                  //存储未来的旅行路线，存储元素是边序号 station 表示要经过
    int usedMoney, usedTime;
    
    void Report(const int &type);
    int Check_City();
    void Transfer();
};

#endif /* People_hpp */

