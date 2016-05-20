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

#include "People.h"

using namespace std;

TrafficNet trafficNet;

int current_time = 0;
int current_day  = 0;
ifstream infile("input.txt");


int main(int argc, const char * argv[])
{
    
    for (int i = 0; i < 1000; i++)
    {
        if (i == 1 || i == 4 || i == 10)
            trafficNet.Add_People();
        
        sleep(1);
        current_time++;
        if (current_time == MAXTIME)
        {
            current_time = 0;
            current_day++;
        }
        
        trafficNet.Move_People();
    }
//    vector <int> a(3, 10), b(2, 20);
//    
//    a.insert(a.end(), b.begin(), b.end());
//    copy(a.begin(), a.end(), ostream_iterator <int>(cout," "));
    return 0;
}
