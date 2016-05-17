//
//  TrafficNet.cpp
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/10.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <deque>
#include "trafficNet.h"

using namespace std;

extern int current_time;

Line::Line()
{
    name = "";
    tail = leaveTime = duration = cost = 0;
    NextLine = NULL;
}

Line::Line(const Line &a)
{
    this->name = a.name;
    this->tail = a.tail;
    this->leaveTime = a.leaveTime;
    this->duration = a.duration;
    this->cost = a.cost;
    this->NextLine = NULL;
}

Line::Line(const std::string &na, const int &t, const int &st, const int &dura, const int &co = 0)
{
    name = na;
    tail = t;
    leaveTime = st;
    duration = dura;
    cost = co;
    NextLine = NULL;
}

TrafficNet::TrafficNet()
{
    cout << "hello" << endl;
	Init_Citys();
   // Print_Edges();
    Run_Floyd();
    Run_SPFA();
//    if (quickRoute[0][4][0].empty()) cout<<"??"<<endl;
//    for (auto i = cityNum.begin(); i != cityNum.end(); i++)
//        cout << i->first << ' ' << i->second << endl;
    Print_Route(0, quickRoute[1][4][0]);
    Add_People();
}

TrafficNet::~TrafficNet()
{
	//wait for typing
	for (int u = 0; u < num_of_city; u++)
    {
		if (citys[u].FirstLine)
        {
			Line* temp = NULL;
            
			while (citys[u].FirstLine) {
				temp = citys[u].FirstLine;
				citys[u].FirstLine = temp->NextLine;
				delete temp;
				temp = NULL;
			}
		}
	}
}

int TrafficNet::Find_City(const string &cityname)
{
    auto it = cityNum.find(cityname);
    
    if (it != cityNum.end())
        return it->second;
    else
    {
        cityNum.insert(make_pair(cityname, num_of_city));
        citys[num_of_city].name = cityname;
        
        num_of_city++;
        return num_of_city - 1;
    }
}

int TrafficNet::Move(const int &time, const Line &edge) const
{
    if (time % MAXTIME <= edge.leaveTime )
        return time + (edge.leaveTime - time % MAXTIME) +edge.duration;
    else
        return time + (edge.leaveTime + MAXTIME - time % MAXTIME) +edge.duration;
}

void TrafficNet::Add_Edge(const Item &v)
{
    Line *temp = new Line(v.edgeID, v.endPoint, v.startTime, v.endTime - v.startTime, v.price);
    
    //记录下两点间最便宜的路径
    if (cheapWay[v.startPoint][v.endPoint] > v.price)
    {
        cheapWay[v.startPoint][v.endPoint] = v.price;
        
        cheapRoute[v.startPoint][v.endPoint].push_back(*temp);
    }
    
    if (citys[v.startPoint].FirstLine == NULL)
        citys[v.startPoint].FirstLine = temp;
    else
    {
        temp->NextLine = citys[v.startPoint].FirstLine;
        citys[v.startPoint].FirstLine = temp;
    }
}

void TrafficNet::Init_Citys()
{
    ifstream table("2.txt");
    
    num_of_city = num_of_people = 0;
    //people.resize(0);
    
    for (int i = 0; i < MAXV; ++i)
        for (int j = 0; j < MAXV; ++j)
        {
            if (i != j)
            {
                cheapWay[i][j] = MAXVALUE + 1;
                
                for (int k = 0; k < MAXTIME; ++k)
                    quickWay[i][j][k] = MAXVALUE + 1;
            }
            else
            {
                cheapWay[i][j] = 0;
                
                for (int k = 0; k < MAXTIME; ++k)
                    quickWay[i][j][k] = k;
            }
            
            cheapRoute[i][j].resize(0);
            
            for (int k = 0; k < MAXTIME; ++k)
                quickRoute[i][j][k].resize(0);
        }
    
    for (int u = 0; u < MAXV; u++)
        citys[u].FirstLine = NULL;
    
    string line;
    while (getline(table, line))
    {
        stringstream word(line);
        Item v;
        std::string start;
        std::string end;
        word >> v.edgeID >> start >> end >> v.startTime >> v.endTime >> v.price;
        v.startPoint = Find_City(start);
        v.endPoint = Find_City(end);
        Add_Edge(v);
    }
}

void TrafficNet::Run_Floyd()    //最后需要的是：最短距离，最优路线， 可以优化
{
    for (int k = 0; k < num_of_city; k++)
        for (int i = 0; i < num_of_city; i++)
            for (int j = 0; j < num_of_city; j++)
                if (cheapWay[i][j] > cheapWay[i][k] + cheapWay[k][j])
                {
                    cheapWay[i][j] = cheapWay[i][k] + cheapWay[k][j];
                    cheapRoute[i][j].clear();
                    cheapRoute[i][j].insert(cheapRoute[i][j].begin(), cheapRoute[k][j].begin(), cheapRoute[k][j].end());
                    cheapRoute[i][j].insert(cheapRoute[i][j].begin(), cheapRoute[i][k].begin(), cheapRoute[i][k].end());
                }
//    cout << "0->";
//    for (auto i = cheapRoute[0][2].begin(); i != cheapRoute[0][2].end(); ++i)
//        cout << i->tail << "->";
//    cout << "success" << endl;
}

void TrafficNet::Run_SPFA() //生成用时最短 i城市到 j 城市 出发时间为 k
{
//    for (int i = 0; i < num_of_city; ++i, cout<<endl)
//        for (int j = 0; j < num_of_city; ++j)
//            cout << quickWay[i][j][1] << ' ';
    for (int source = 0; source < num_of_city; ++source)
        for (int time = 0; time < MAXTIME; ++time)
        {
            deque <int> q(0);
            bool used[MAXV] = {};
            
            q.push_back(source);
            used[source] = true;
            
            while (!q.empty())
            {
                int node = q.front();
                Line *k = citys[node].FirstLine;
                
                while (k != NULL)
                {
                    if (quickWay[source][k->tail][time] > Move(quickWay[source][node][time], *k))
                    {
                        quickWay[source][k->tail][time] = Move(quickWay[source][node][time], *k);
                        
                        quickRoute[source][k->tail][time].clear();
                        quickRoute[source][k->tail][time].insert(quickRoute[source][k->tail][time].begin(), quickRoute[source][node][time].begin(), quickRoute[source][node][time].end());
                        quickRoute[source][k->tail][time].push_back(*k);
                        
                        if (used[k->tail] == false)
                        {
                            used[k->tail] = true;
                            q.push_back(k->tail);
                        }
                    }
                    k = k->NextLine;
                }
                used[node] = false;
                q.pop_front();
            }
        }
}

void TrafficNet::Run_DFS(People &p)
{
    p.Check_City();
    //到达终点且遍历完全部
    //花的钱太多
}

int TrafficNet::Get_Cost(const vector <int> &a, const TravelPlan &p) const
{
    int tot = cheapWay[p.source][a[0]], i;
    for (i = 0; i < a.size() - 1; ++i)
        tot += cheapWay[a[i]][a[i + 1]];
    return tot + cheapWay[a[i]][p.destination];
}

int TrafficNet::Get_Time(const vector <int> &a, const People &p) const
{
    int t, i;
    
    if (p.route.size() != 0)
    {
        t = current_time + p.route[0].duration;
        t = quickWay[p.route[0].tail][a[0]][t % MAXTIME];
    }
    else t = quickWay[p.plan.source][a[0]][current_time];
    
    for (i = 0; i < a.size() - 1; ++i)
        t += quickWay[a[i]][a[i + 1]][t % MAXTIME] - (t % MAXTIME);
    return t + (quickWay[a[i]][p.plan.destination][t % MAXTIME] - (t % MAXTIME));
}

void TrafficNet::Generate_Cheap_Route(People &p, const vector <int> &bestTour)
{
    vector <Line> bestRoute(0);
    int i;
    
    if (p.plan.station.size() == 0)
    {
        if (p.route.size() == 0) bestRoute.assign(cheapRoute[p.plan.source][p.plan.destination].begin(), cheapRoute[p.plan.source][p.plan.destination].end());
        else
        {
            bestRoute.push_back(p.route[0]);
            bestRoute.insert(bestRoute.end(), cheapRoute[p.route[0].tail][p.plan.destination].begin(), cheapRoute[p.plan.source][p.plan.destination].end());
        }
    }
    
    else
    {
        if (p.route.size() == 0)
            bestRoute.insert(bestRoute.begin(), cheapRoute[p.plan.source][bestTour[0]].begin(), cheapRoute[p.plan.source][bestTour[0]].end());
        else
        {
            bestRoute.push_back(p.route[0]);
            bestRoute.insert(bestRoute.begin(), cheapRoute[p.route[0].tail][bestTour[0]].begin(), cheapRoute[p.route[0].tail][bestTour[0]].end());
        }
        
        for (i = 0; i < bestTour.size() - 1; i++)
            bestRoute.insert(bestRoute.end(), cheapRoute[bestTour[i]][bestTour[i + 1]].begin(), cheapRoute[bestTour[i]][bestTour[i + 1]].end());
        
        bestRoute.insert(bestRoute.end(), cheapRoute[bestTour[i]][p.plan.destination].begin(), cheapRoute[bestTour[i]][p.plan.destination].end());
    }
    
    p.route.assign(bestRoute.begin(), bestRoute.end());
}

void TrafficNet::Generate_Quick_Route(People &p, const vector <int> &bestTour)
{
    vector <Line> bestRoute(0);
    int t = current_time, i;
    
    if (bestTour.empty())
    {
        if (p.route.size() == 0)
            bestRoute.assign(quickRoute[p.plan.source][p.plan.destination][current_time].begin(), quickRoute[p.plan.source][p.plan.destination][current_time].end());
        else
        {
            bestRoute.push_back(p.route[0]);
            bestRoute.insert(bestRoute.end(), quickRoute[p.route[0].tail][p.plan.destination][(t + p.route[0].duration) % MAXTIME].begin(), quickRoute[p.route[0].tail][p.plan.destination][(t + p.route[0].duration) % MAXTIME].end());
        }
    }
    
    else
    {
        if (p.route.size() == 0)
        {
            bestRoute.insert(bestRoute.begin(), quickRoute[p.plan.source][bestTour[0]][t].begin(), quickRoute[p.plan.source][bestTour[0]][t].end());
            t = quickWay[p.plan.source][bestTour[0]][t] % MAXTIME;
        }
        else
        {
            bestRoute.push_back(p.route[0]);
            bestRoute.insert(bestRoute.begin(), quickRoute[p.route[0].tail][bestTour[0]][t].begin(), quickRoute[p.route[0].tail][bestTour[0]][t].end());
            t = t + p.route[0].duration;
            t = quickWay[p.route[0].tail][bestTour[0]][t] % MAXTIME;
        }

        for (i = 0; i < bestTour.size() - 1; ++i)
        {
            bestRoute.insert(bestRoute.end(), quickRoute[bestTour[i]][bestTour[i + 1]][t].begin(), quickRoute[bestTour[i]][bestTour[i + 1]][t].end());
            t = quickWay[bestTour[i]][bestTour[i + 1]][t] % MAXTIME;
        }
        
        bestRoute.insert(bestRoute.end(), quickRoute[bestTour[i]][p.plan.destination][t].begin(), quickRoute[bestTour[i]][p.plan.destination][t].end());
    }
    
    p.route.assign(bestRoute.begin(), bestRoute.end());
}

double TrafficNet::Accept_Rate(const int &newEnergy, const int &oldEnergy, const double &tem) const
{
    if (newEnergy < oldEnergy) return 1;
    else return exp((oldEnergy - newEnergy) / tem);
}

void TrafficNet::Run_SA(People &p)
{
    int kind = p.plan.type, newEnergy = 0, oldEnergy = 0;
    vector <int> tour(0);
    double temperature = 100, coolRate = 0.003;
    
    for (int i = 0; i < p.plan.station.size(); ++i)
        tour.push_back(p.plan.station[i]);
    
    srand((unsigned int)clock());
    random_shuffle(tour.begin(), tour.end());
    
    vector <int> bestTour(tour);
    int minCost;
    
    if (!tour.empty())
    {
        if (kind == 1) minCost = Get_Cost(tour, p.plan);
        else minCost = Get_Time(tour, p);
        oldEnergy = minCost;
        
        while (temperature > 1 && tour.size() != 1)
        {
            vector <int> newTour(tour);
            
            int pos1 = rand() % tour.size();
            int pos2;
            do
            {
                pos2 = rand() % tour.size();
            }while (pos2 == pos1);
            
            int temp = newTour[pos1];
            newTour[pos1] = newTour[pos2];
            newTour[pos2] = temp;
            if (kind == 1) newEnergy = Get_Cost(newTour, p.plan);
            else newEnergy = Get_Time(newTour, p);
            
            if (Accept_Rate(newEnergy, oldEnergy, temperature) > ((double)rand() /RAND_MAX))
            {
                tour.assign(newTour.begin(), newTour.end());
                oldEnergy = newEnergy;
            }
            
            if (oldEnergy < minCost)
            {
                minCost = oldEnergy;
                bestTour.assign(tour.begin(), tour.end());
            }
            temperature *= 1 - coolRate;
            
            //cout << temperature << ' '<< minCost<<endl;
        }
    }
    
    if (kind == 1)
        Generate_Cheap_Route(p, bestTour);
    else
        Generate_Quick_Route(p, bestTour);
}

void TrafficNet::Design_Route(People &p)
{
    if (p.plan.type != 3) Run_SA(p);
    else            //必经30个点
    {
        minMixCost = MAXVALUE;
        p.histroy = 0;
        
        if (p.route.size() == 0)
        {
            p.location = p.plan.source;
            
            Run_DFS(p);
        }
        else
        {
            p.location = p.route[0].tail;
            while (p.route.size() > 1) p.route.pop_back();
            Run_DFS(p);
        }
        
    }
}

void TrafficNet::Print_Edges() const
{
	for (int u = 0; u < num_of_city; u++)
    {
		Line* search = citys[u].FirstLine;

		while (search != NULL)
        {
            cout << citys[u].name << " -> " << citys[search->tail].name <<", leave at "<< search->leaveTime;
            cout <<", itsduration is " << search->duration <<" and price " << search->cost << endl;
			search = search -> NextLine;
		}
	}
}

void TrafficNet::Print_Route(const int start, const vector<Line> & route) const
{
    int now = start, t = current_time, day = 0, money = 0;
    
    for (auto next = route.begin();  next != route.end(); ++next)
    {
        cout << "At " << next->leaveTime << ":00, take on the " << next->name << " from " << citys[now].name
            << " to " << citys[next->tail].name << ", arrive at " << Move(t, *next) % MAXTIME << ":00." << endl;
        t = Move(t, *next);
        if (t >= MAXTIME)
        {
            t -= MAXTIME;
            day++;
        }
        money += next->cost;
        now = next->tail;
    }
    cout <<"Totally, it takes you $"<< money << " and " << day * MAXTIME + t - current_time << "h." << endl;
}

void TrafficNet::Add_People()
{
    People *temp = new People;
    
    num_of_people ++;
//    cout << "Input the your name and password" << endl;
//    cin >> temp->name;
//    cin >> temp->password;
//    
    string start, end;
    cout << "What's your departure and destination and plans?" << endl;
    cin >> start >> end >> (temp->plan).type;
    (temp->plan).source = cityNum[start];
    (temp->plan).destination = cityNum[end];
    cout << "How many cities you wanna pass by, and what are they?" << endl;
    
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        string s;
        cin >> s;
        (temp->plan).station.push_back(cityNum[s]);
    }
    
    Design_Route(*temp);    //如果是中途改变，要保留当前边
    
    people.push_back(*temp);
    
    cout << "For client" << temp->name << ", Your route is:" << endl;
    Print_Route((temp->plan).source, temp->route);
}