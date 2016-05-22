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
    name = "";
    route.clear();
    plan.source = plan.destination = plan.type = plan.timeLimit = 0;
    plan.station.clear();
    usedTime = usedMoney = 0;
}

int People::Check_City()                       //到达一个新城市 判断是不是必经城市
{
    for (int i = 0; i < plan.station.size(); ++i)
        if (plan.station[i] == location)
            return i;
    return -1;
}

void People::Report(const int &type)
{
    eventFile << "Day " << current_day << " " << current_time << ":00\t";
    switch (type) {
        case DEPART:
            eventFile << "Client " << name << " take the " << route[0].name << " to "<< trafficNet.Get_City(route[0].tail) << endl;
            break;
            
        case ARRIVE:
            eventFile << "Client " << name << " arrive " << trafficNet.Get_City(location) << endl;
            break;
            
        default:
            eventFile <<  "Client " << name << " arrive the destination " << trafficNet.Get_City(location) << ", spending $" << usedMoney << " and " << usedTime + 1 << " hours totally." << endl;
            break;
    }
}

void People::Transfer()
{
    //route[0]的还没开始 跳过
    //如果 route[0]开始了(active|| current_time )duration--
    if (route[0].leaveTime == ACTIVE)
        route[0].duration--;
    if (route[0].leaveTime == current_time)
    {
        route[0].leaveTime = ACTIVE;
        usedMoney += route[0].cost;
        Report(DEPART);
    }
    //0说明到达了一个新城市 查看是不是到了一个必经点
    if (route[0].duration == 0)
    {
        location = route[0].tail;
        Report(ARRIVE);
        
        int x = Check_City();
        if (x >= 0) plan.station.erase(plan.station.begin() + x);
        
        route.erase(route.begin());
        
        //如果不存在下一条了 则到达终点
        if (route.empty())
        {
            Report(FINISH);
            location = CLIENT_SLEEP;
        }
        
        //check next line
        if (route[0].leaveTime == current_time)
        {
            route[0].leaveTime = ACTIVE;
            usedMoney += route[0].cost;
            Report(DEPART);
        }
    }
    usedTime++;
}
