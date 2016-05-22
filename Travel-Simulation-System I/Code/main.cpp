//
//  main.cpp
//  Travel-Simulation-System
//
//  Created by YeWenting. on 16/4/10.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//


#include "TrafficNet.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <ctime>
#include <cmath>

#include "People.h"

using namespace std;

TrafficNet trafficNet;

int current_time = 0;
int current_day  = 0;

ifstream infile("input.txt");
ofstream routeFile("route.log"), eventFile("event.log");

int main(int argc, const char * argv[])
{
    time_t lastTime = time(NULL), nowTime = lastTime;

    while (true)
    {
        nowTime = time(NULL);
        if ((double)(nowTime - lastTime > TIME_PER_SEC) )
        {
            int timeDelta = floor((double)(nowTime - lastTime) / TIME_PER_SEC);
            current_time += timeDelta;
            lastTime += timeDelta * TIME_PER_SEC;
            
            while (current_time >= MAXTIME)
            {
                current_time -= MAXTIME;
                current_day++;
            }
            
            for (int i = 0; i < timeDelta; ++i) trafficNet.Move_People();
            
            if ((current_day == 0) && (current_time == 1 || current_time == 4 || current_time == 10))
                trafficNet.Add_People();
            if ((current_day == 0) && (current_time == 5))
            {
                string thisName;
                string newDest;
                int newType;
                infile >> thisName >> newDest >> newType;
                
                int n;
                infile >> n;
                vector <string> newStation(n);
                for (int i = 0; i < n; i++)
                    infile >> newStation[i];
                
                int newTimeLimit = 0;
                
                if (newType == 3)
                    infile >> newTimeLimit;
                
                if (trafficNet.Change_Plan(thisName, newDest, newType, newStation, newTimeLimit) == ERROR)
                    cout << "Your message is uncorrect." <<endl;
            }
        }
        sleep(1);
        
    }

    return 0;
}
