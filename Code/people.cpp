//
//  People.cpp
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/15.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#include <iostream>
#include <string>
#include <cstring>

#include "people.h"
#include "trafficNet.h"

using namespace std;

TravelPlan::TravelPlan():station(0)
{
    source = 0;
    destination = 0;
    type = 0;
}

TravelPlan::TravelPlan(int s, int d, vector<int> stop, int t):station(stop)
{
    source = s;
    destination = d;
    type = t;
}

People::People()
{
    name = password = realLocation = "";
    route.clear();
    plan.source = plan.destination = plan.type = 0;
}

int People::Check_City()                       //到达一个新城市 判断是不是必经城市
{
    for (int i = 0; i < plan.station.size(); ++i)
        if (plan.station[i] == location)
            return i;
    return -1;
}

//void People:: Make_Route(const vector<int> &way)
//{
//    route.clear();
//    for (auto i = .begin(); i < way.end(); ++i)
//        route.push_back(*i);
//}

//模拟中 到达一个必经点 要去掉这个点
