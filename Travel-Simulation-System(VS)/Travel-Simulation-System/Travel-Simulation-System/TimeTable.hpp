//
//  TimeTable.h
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
	std::string VechileNo;	//线路名
	int StartPoint;	//出发点
	int EndPoint;	//目的地
	int StartTime;	//出发时间(0-23 h)
	int EndTime;	//到达时间(0-n h)
};
std::ostream& operator<<(std::ostream& out, const TimeTableItem& item) {
	out << item.VechileNo << "\t" << item.StartPoint << "\t" << item.EndPoint << "\t" << item.StartTime << "\t" << item.EndTime << std::endl;
	return out;
}

class TimeTable
{
public:
	TimeTable();
	~TimeTable(){}

	void Print_Table()const;
	
private:
	std::ifstream& Read_Table(std::ifstream&);
	std::ifstream& Read_City_Name(std::ifstream&);

	std::vector<TimeTableItem> Table;
	std::map<std::string, int>   CityNum;
//	map<int, string>   NumCity;
};
std::ifstream& TimeTable::Read_Table(std::ifstream& in) {
	std::string line;
	while (std::getline(in, line)) {
		std::stringstream word(line);
		TimeTableItem Item;
		std::string Start;
		std::string End;
		word >> Item.VechileNo>> Start >> End >> Item.StartTime >> Item.EndTime;
		Item.StartPoint = CityNum[Start];
		Item.EndPoint = CityNum[End];
		Table.push_back(Item);
	}
	return in;
}
std::ifstream& TimeTable::Read_City_Name(std::ifstream& in) {
	std::string City;
	int Num;
	while (in >> City) {
		in >> Num;
		CityNum[City] = Num;
//		NumCity[Num] = City;
	}
	return in;
}
TimeTable::TimeTable()
{
	std::ifstream CityName("CityName.dat");
	std::ifstream Table("TimeTable.dat");
	Read_City_Name(CityName);
	Read_Table(Table);
}
void TimeTable::Print_Table()const {
	for (auto u : Table)
		std::cout << u;
}