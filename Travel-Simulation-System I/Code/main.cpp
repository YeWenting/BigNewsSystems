//
//  main.cpp
//  Travel-Simulation-System
//
//  Created by YeWenting. on 16/4/10.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//


#include"TrafficNet.h"
#include"TimeTable.h"
//#include"People.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
	TimeTable table;
	table.Print_Table();

	TrafficNet trafficNet(table);
	trafficNet.Print_Citys();
    cout<<"1"<<endl;
    return 0;
}
