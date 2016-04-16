//
//  TimeTable.hpp
//  Travel-Simulation-System I
//
//  Created by Xiong. on 16/4/16.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//
#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

class TimeTable;
struct TimeTableItem
{
	friend std::ostream& operator<<(std::ostream&,const TimeTableItem&);
	std::string vechileNo;	//线路名
	int startPoint;	//出发点
	int endPoint;	//目的地
	int startTime;	//出发时间(0-23 h)
	int endTime;	//到达时间(0-n h)
	int price;	//费用
};
//std::ostream& operator<<(std::ostream& out, const TimeTableItem& item) {
//	out << item.vechileNo << "\t" << item.startPoint << "\t" << item.endPoint << "\t" << item.startTime << "\t" << item.endTime <<"\t"<<item.price<< std::endl;
//	return out;
//}

class TimeTable
{
	friend class TrafficNet;
public:
	TimeTable();
	~TimeTable(){}

	void Print_Table()const;
	
private:
	std::ifstream& Read_Table(std::ifstream&);
	std::ifstream& Read_City_Name(std::ifstream&);

	std::vector<TimeTableItem> table;
	std::map<std::string, int>   cityNum;
//	std::map<int, std::string>   numCity;
};
//std::ifstream& TimeTable::Read_Table(std::ifstream& in) 
//{
//	std::string line;
//	while (std::getline(in, line)) {
//		std::stringstream word(line);
//		TimeTableItem item;
//		std::string start;
//		std::string end;
//		word >> item.vechileNo>> start >> end >> item.startTime >> item.endTime>>item.price;
//		item.startPoint = cityNum[start];
//		item.endPoint = cityNum[end];
//		table.push_back(item);
//	}
//	return in;
//}
//std::ifstream& TimeTable::Read_City_Name(std::ifstream& in) 
//{
//	std::string city;
//	int num;
//	while (in >> city) {
//		in >> num;
//		cityNum[city] = num;
////		numCity[num] = city;
//	}
//	return in;
//}
//TimeTable::TimeTable()
//{
//	std::ifstream cityName("CityName.dat");
//	std::ifstream table("TimeTable.dat");
//	Read_City_Name(cityName);
//	Read_Table(table);
//}
//void TimeTable::Print_Table()const {
//	for (auto u : table)
//		std::cout << u;
//}