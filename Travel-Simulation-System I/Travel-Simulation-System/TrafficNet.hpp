//
//  TrafficNet.hpp
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/10.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#ifndef TrafficNet_hpp
#define TrafficNet_hpp

#define MaxV 20
#include <string>
#include <fstream>
#include <iostream>

class TrafficNet
{
public:
    TrafficNet();
    TrafficNet(const std::string);
    ~TrafficNet();
    
private:
    class Line
    {
    public:
        Line *NextLine;
        int tail, LeaveTime, duration;
    };
    class City
    {
    public:
        Line *FirstLine;
        std::string name;
    };
    City citys[MaxV];
    
};

TrafficNet::TrafficNet(const std::string filename)
{
//    ifstream 
}

#endif /* TrafficNet_hpp */
