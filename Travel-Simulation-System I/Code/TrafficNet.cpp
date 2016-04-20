//
//  TrafficNet.cpp
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/10.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#include "TrafficNet.h"

using namespace std;
TrafficNet::TrafficNet(const TimeTable& t) {
	Init_Citys(t);
//	Get_Cheap_Way();
//	Get_Min_Cost();
}
TrafficNet::~TrafficNet() {
	//wait for typing
	for (int u = 0; u != MapMaxV; u++) {
	//	cout << u;
		if (citys[u].FirstLine) {
			Line*temp = NULL;
	//		cout << citys[u].name;
			while (citys[u].FirstLine) {
				temp = citys[u].FirstLine;
				citys[u].FirstLine = temp->NextLine;
				delete temp;
				temp = NULL;
			}
		}
	}

}
void TrafficNet::Plan_Route(const People& p) {
	//wait for typing
}
void TrafficNet::Init_Citys(const TimeTable& t) {
	for (auto u = 0; u != MapMaxV; u++) 
		citys[u].FirstLine = NULL;
	for (auto u : t.cityNum) 
		citys[u.second].name = u.first;
	
	for (auto u : t.table) {
		Line*temp = new Line;
		Line*search = citys[u.startPoint].FirstLine;
		temp->name = u.vechileNo;
		temp->cost = u.price;
		temp->LeaveTime = u.startTime;
		temp->duration = u.endTime - u.startTime;
		temp->tail = u.endPoint;
		temp->NextLine = NULL;

		if (!citys[u.startPoint].FirstLine)
			citys[u.startPoint].FirstLine = temp;
		else {
			temp->NextLine = citys[u.startPoint].FirstLine;
			citys[u.startPoint].FirstLine = temp;
		}
	}

}

void TrafficNet::Print_Citys()const {
	for (int u = 0; u != MapMaxV; u++) {
		cout << u << " -> ";
		Line*search = citys[u].FirstLine;
		
		while (search!=NULL) {
			cout << search->name;
			cout << " -> ";
			search = search->NextLine;
		}
		cout << endl;
	}
	
}