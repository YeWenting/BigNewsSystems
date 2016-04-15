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
        Line *NextLine;                                         //下一条边
        int tail, LeaveTime, duration;                          //tail该边的指向的点，LeaveTime这条路什么时候走，duration所需时间
    };
    class City
    {
    public:
        Line *FirstLine;                                        //第一条边
        std::string name;                                       //名字
    };
    City citys[MaxV];
};

TrafficNet::TrafficNet(const std::string filename)              //从文件中读入 初始化交通网 支持增加边
{
//    ifstream 
}

#endif /* TrafficNet_hpp */
