//
//  People.cpp
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/15.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#include <iostream>
#include <string>

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

void People::Check_City()
{
    for (int i = 0; i < plan.station.size(); ++i)
        if (location == plan.station[i])
            histroy = histroy && (1 << i);
}


//void People:: Make_Route(const vector<int> &way)
//{
//    route.clear();
//    for (auto i = .begin(); i < way.end(); ++i)
//        route.push_back(*i);
//}
