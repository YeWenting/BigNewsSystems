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
	std::ifstream 
}