//
//  People.h
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

#include "trafficnet.h"

class Line;
class TravelPlan
{
public:
    TravelPlan();
    TravelPlan(int, int, std::vector<int>, int);
    int source, destination, type;
    std::vector<int> station;
};

class People
{
friend class TrafficNet;
    
public:
    People();
private:
    std::string name, password;
    std::string realLocation;
    int location, histroy;                                             //用于 dfs
    TravelPlan plan;
    std::vector<Line> route;                                  //存储未来的旅行路线，存储元素是边序号 station 表示要经过
    void Assign_Route(const std::vector<Line> &);
    void Check_City;
};

#endif /* People_hpp */

