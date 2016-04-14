#define MaxV 20
#include <string>
#include <fstream>
#include <iostream>

class TrafficNet
{
	public:
	TrafficNet();
	TrafficNet(const string);
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
				string name;
		};
		City citys[MaxV];

};

TrafficNet::TrafficNet(const string filename)
{
	ifstream 
}