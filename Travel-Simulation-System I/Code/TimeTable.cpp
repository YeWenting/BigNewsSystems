#include"TimeTable.h"

std::ostream& operator<<(std::ostream& out, const TimeTableItem& item) {
	out << item.vechileNo << "\t" << item.startPoint << "\t" << item.endPoint << "\t" << item.startTime << "\t" << item.endTime << "\t" << item.price << std::endl;
	return out;
}

std::ifstream& TimeTable::Read_Table(std::ifstream& in)
{
	std::string line;
	while (std::getline(in, line)) {
		std::stringstream word(line);
		TimeTableItem item;
		std::string start;
		std::string end;
		word >> item.vechileNo >> start >> end >> item.startTime >> item.endTime >> item.price;
		item.startPoint = cityNum[start];
		item.endPoint = cityNum[end];
		table.push_back(item);
	}
	return in;
}
std::ifstream& TimeTable::Read_City_Name(std::ifstream& in)
{
	std::string city;
	int num;
	while (in >> city) {
		in >> num;
		cityNum[city] = num;
		//		numCity[num] = city;
	}
	return in;
}
TimeTable::TimeTable()
{
	std::ifstream cityName("CityName.dat");
	std::ifstream table("TimeTable.dat");
	Read_City_Name(cityName);
	Read_Table(table);
}
void TimeTable::Print_Table()const {
	for (auto u : table)
		std::cout << u;
}