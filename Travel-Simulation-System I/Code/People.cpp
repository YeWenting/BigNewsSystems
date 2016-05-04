//
//  People.cpp
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/15.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#include <iostream>
#include "People.h"
#include "TrafficNet.h"

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
    static int num = 0;
    cout<<"Input the your name and password"<<endl;
    cin>>name;
    cin>>password;
    id = num++;
    cout<<"Your ID is "<<id<<", please keep it in your mind:)"<<endl;
    cout<<"What's your departure and destination and plans?"<<endl;
    cin>>plan.source>>plan.destination>>plan.type;
    cout<<"How many cities you wanna pass by, and what are they?"<<endl;
    
    int n;
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin>>x;
        plan.station.push_back(x);
    }
    
    //求出旅行方案后，再求其 location&duration&route
    net.Plan_Route(*this);
}

void People:: Simulate(const int &time)
{
    if (location < 0) //在某边上
        if (duration > time)  duration -= time;
        else if ()//到了一个新点
}

void People:: Make_Route(const vector<int> &way)
{
    route.clear();
    for (auto i = way.begin(); i < way.end(); ++i)
        route.push_back(*i);
}

TravelPlan People:: Get_Plan()
{
    return plan;
}
