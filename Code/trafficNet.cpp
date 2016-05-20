//
//  TrafficNet.cpp
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/10.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//
//小函数写宏

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <deque>
#include <cstring>
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
	Init_Citys();
   // Print_Edges();
    Run_Floyd();
    Run_SPFA();
//    if (quickRoute[0][4][0].empty()) cout<<"??"<<endl;
//    for (auto i = cityNum.begin(); i != cityNum.end(); i++)
//        cout << i->first << ' ' << i->second << endl;
    //Print_Route(cityNum["0"], cheapRoute[cityNum["0"]][cityNum["4"]]);
   // Print_Route(0, cheapRoute[0][6]);
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

int TrafficNet::Move(const int &time, const Line &edge) const   //表示在 time 时间走某边 将在什么时候到达 可大于23
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
        
        cheapRoute[v.startPoint][v.endPoint].clear();
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
    ifstream table("20.txt");
    
    num_of_city = num_of_people = 0;
    people.resize(0);
    srand((unsigned int)clock());
    
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
   // cout << num_of_city << endl;
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
    
//    for (int i = 0; i < num_of_city; i++, cout << endl)
//        for (int j = 0; j < num_of_city; ++j)
//            cout << cheapWay[i][j] <<' ' ;
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

int TrafficNet::Get_Quick_Time(const int &s, const int &d, const int &t)
{
    return (quickWay[s][d][t % MAXTIME] - t % MAXTIME);
}

int TrafficNet::Get_Rough_Time(People &p, const int & t)  //current time + t
{
    int niceAns = 0, temp = p.plan.source, badAns = 0;
    
    p.plan.type = 2;
    p.plan.source = p.location;
    niceAns = Get_Time(Run_SA(p, LOWTEMP, (t + current_time) % MAXTIME), p, t + current_time) - (t + current_time);
    p.plan.type = 3;
    p.plan.source = temp;
    
    vector <int> sbAns(0);
    for (int i = 0; i < p.plan.station.size(); ++i)
        sbAns.push_back(p.plan.station[i]);
    random_shuffle(sbAns.begin(), sbAns.end());
    badAns = Get_Time(sbAns, p, t + current_time) - (t + current_time);
    
    if (badAns < niceAns)
    {
        badAns = niceAns ^ badAns;
        niceAns = niceAns ^ badAns;
        badAns = niceAns ^ badAns;
    }
    return 2 * niceAns - badAns;
}

int TrafficNet::Get_Rough_Cost(People &p)  //current time + t
{
    int niceAns = 0, temp = p.plan.source, badAns = 0;
    
    p.plan.type = 1;
    p.plan.source = p.location;
    niceAns = Get_Cost(Run_SA(p, LOWTEMP), p);
    p.plan.type = 3;
    p.plan.source = temp;
    
    vector <int> sbAns(0);
    for (int i = 0; i < p.plan.station.size(); ++i)
        sbAns.push_back(p.plan.station[i]);
    random_shuffle(sbAns.begin(), sbAns.end());
    badAns = Get_Cost(sbAns, p);
    
    if (badAns < niceAns)
    {
        badAns = niceAns ^ badAns;
        niceAns = niceAns ^ badAns;
        badAns = niceAns ^ badAns;
    }
    return 2 * niceAns - badAns;
}

void TrafficNet::Run_DFS(People &p, const int &money, const int &t)
{
//                     cout << p.location << endl;
    //到达终点且遍历完全部
    //Print_Route(p.plan.source, currentRoute);
    if ((p.location == p.plan.destination) && (p.plan.station.empty()))
    {
        if ((minMixCost > money) && (t <= p.plan.timeLimit))
        {
            minMixCost = money;
            bestRoute.assign(currentRoute.begin(), currentRoute.end());
            //Print_Route(p.plan.source, bestRoute);
            return;
        }
        else        //已经走过所有点 并到达终点 但是花钱更多活时间更多 显然可以结束搜索
            return;
    }
    
    //时间不够用 or 花的钱太多
    if (t + Get_Rough_Time(p, t) > p.plan.timeLimit || money + Get_Rough_Cost(p) > minMixCost)
        return;
//    if (t > p.plan.timeLimit || money > minMixCost)
//        return;
    
    // 限制搜索深度
    //if (currentRoute.size() > p.plan.num_of_station + 2) return;
    
    //遍历完所有的点
    int now = p.location;
    Line *temp = citys[p.location].FirstLine;
//    int static num = 0;
    
    while (temp != NULL)
    {
        p.location = temp->tail;
        currentRoute.push_back(*temp);
        
        int seq = p.Check_City();
        if (seq >= 0)
        {
//            num++;
//            cout << num << ": ";
//            copy(p.plan.station.begin(), p.plan.station.end(), ostream_iterator<int>(cout, " "));
//            cout << endl;
            p.plan.station.erase(p.plan.station.begin() + seq);
            Run_DFS(p, money + temp->cost, Move(t + current_time, *temp) - current_time);
            p.location = now;
            p.plan.station.insert(p.plan.station.begin() + seq, temp->tail);
//            cout << num << ": ";
//            copy(p.plan.station.begin(), p.plan.station.end(), ostream_iterator<int>(cout, " "));
//            cout << endl;
        }
        else
            Run_DFS(p, money + temp->cost, Move(t + current_time, *temp) - current_time);
        
        p.location = now; //可移动
        currentRoute.pop_back();
        temp = temp->NextLine;
    }
}

int TrafficNet::Get_Route_Time(const vector<Line> &a, const int & time)       //计算路线总耗时
{
    int t = time;
    for (int i = 0; i < a.size(); ++i)
        t = Move(t, a[i]);
    return t - time;
}

//int TrafficNet::Get_Route_Time(const vector<Line> &a)
//{
//    int ans = 0;
//    for (int i = 0; i < a.size(); ++i)
//        ans += a[i].cost;
//    return ans;
//}

int TrafficNet::Get_Cost(const vector <int> &a, const People &p) const          //已知经过必经点的顺序， 求最少花费
{
    int tot, i;
    
    //考虑无必经点的情况
    if (p.plan.station.empty())
    {
        if (p.route.empty()) return cheapWay[p.plan.source][p.plan.destination];
        else return p.route[0].cost + cheapWay[p.route[0].tail][p.plan.destination];
    }
    
    if (p.route.size() == 0)
        tot = cheapWay[p.plan.source][a[0]];
    else
        tot = cheapWay[p.route[0].tail][a[0]];
    
    for (i = 0; i < a.size() - 1; ++i)
        tot += cheapWay[a[i]][a[i + 1]];
    return tot + cheapWay[a[i]][p.plan.destination];
}

int TrafficNet::Get_Time(const vector <int> &a, const People &p, const int &time) const  //传入time 可以大于23
{
    int t, i;
    
    //考虑无必经点的情况
    if (p.plan.station.empty())
    {
        if (p.route.empty()) return time + (quickWay[p.plan.source][p.plan.destination][time % MAXTIME] - time % MAXTIME);
        else return time + (quickWay[p.route[0].tail][p.plan.destination][(time + p.route[0].tail) % MAXTIME] - (time + p.route[0].tail) % MAXTIME);
    }
    
    if (p.route.size() != 0)
    {
        t = time + p.route[0].duration;
        t = quickWay[p.route[0].tail][a[0]][t % MAXTIME];
    }
    else t = time + (quickWay[p.plan.source][a[0]][time % MAXTIME] - time % MAXTIME);
    
    for (i = 0; i < a.size() - 1; ++i)
        t += quickWay[a[i]][a[i + 1]][t % MAXTIME] - (t % MAXTIME);
    return t + (quickWay[a[i]][p.plan.destination][t % MAXTIME] - (t % MAXTIME));
}

vector <Line> TrafficNet::Generate_Cheap_Route(People &p, const vector <int> &bestTour)
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
    
    return bestRoute;
}

vector <Line> TrafficNet::Generate_Quick_Route(People &p, const vector <int> &bestTour)
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
    
    return bestRoute;
}

double TrafficNet::Accept_Rate(const int &newEnergy, const int &oldEnergy, const double &tem) const
{
    if (newEnergy < oldEnergy) return 1;
    else return exp((oldEnergy - newEnergy) / tem);
}

vector <int> TrafficNet::Run_SA(const People &p, const double &control, const int &time)
{
    int kind = p.plan.type, newEnergy = 0, oldEnergy = 0;
    vector <int> tour(0);
    double temperature = control, coolRate = 0.003;
    
    for (int i = 0; i < p.plan.station.size(); ++i)
        tour.push_back(p.plan.station[i]);

    random_shuffle(tour.begin(), tour.end());
    
    vector <int> bestTour(tour);
    int minCost;
    
    if (!tour.empty())
    {
        if (kind == 1) minCost = Get_Cost(tour, p);
        else minCost = Get_Time(tour, p, time);
        oldEnergy = minCost;
        //int num = 0;
        
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
            if (kind == 1) newEnergy = Get_Cost(newTour, p);
            else newEnergy = Get_Time(newTour, p, time);
            
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
            
            //num++;
            //if (control == LOWTEMP) cout << num << " " << temperature << ' '<< minCost<<endl;
        }
    }
    
    return bestTour;
}

void TrafficNet::Design_Route(People &p)
{
    bestRoute.clear();
    
    if (p.plan.type == 1)
        bestRoute = Generate_Cheap_Route(p, Run_SA(p, HIGHTEMP));
    else if (p.plan.type == 2)
        bestRoute = Generate_Quick_Route(p, Run_SA(p, HIGHTEMP));
    
    else            //必经30个点
    {
        clock_t start = clock();
        vector <int> roughTour(0);
        vector <Line> temp(0);
        
        p.plan.type = 1;
        minMixCost = MAXVALUE;
        bestRoute.clear();
        currentRoute.clear();
        p.plan.num_of_station = (int) p.plan.station.size();
        
        if (p.route.size() == 0)
        {
            p.location = p.plan.source;
            p.Check_City();
            roughTour = Run_SA(p, HIGHTEMP);     //获得最便宜路线
            temp = Generate_Quick_Route(p, roughTour);
            if (Get_Route_Time(temp, current_time) <= p.plan.timeLimit)
                bestRoute = temp;
            
            else
            {
                p.plan.type = 2;
                roughTour = Run_SA(p, MIDTEMP);
                if (Get_Time(roughTour, p, current_time) - current_time <= p.plan.timeLimit)
                {
                    bestRoute = Generate_Quick_Route(p, roughTour);
                    minMixCost = 0;
                    for (int i = 0; i < bestRoute.size(); i ++)
                        minMixCost += bestRoute[i].cost;
                    p.plan.type = 3;
                    Run_DFS(p, 0, 0);
                }
            }
        }
        else
        {
            p.location = p.plan.source = p.route[0].tail;
            p.Check_City();
            currentRoute.push_back(p.route[0]);
            roughTour = Run_SA(p, HIGHTEMP);     //获得最便宜路线
            temp = Generate_Quick_Route(p, roughTour);
            if (Get_Route_Time(temp, current_time + p.route[0].duration) <= p.plan.timeLimit)
                bestRoute = temp;
            
            else
            {
                p.plan.type = 2;
                roughTour = Run_SA(p, MIDTEMP, (current_time + p.route[0].duration) % MAXTIME);

                if (Get_Time(roughTour, p, current_time + p.route[0].duration) - (current_time + p.route[0].duration) <= p.plan.timeLimit)
                {
                    bestRoute = Generate_Quick_Route(p, roughTour);
                    bestRoute.insert(bestRoute.begin(), p.route[0]);
                    minMixCost = 0;
                    for (int i = 1; i < bestRoute.size(); i ++)
                        minMixCost += bestRoute[i].cost;
                    p.plan.type = 3;
                    Run_DFS(p, 0, p.route[0].duration);
                }
            }
        }
        clock_t end = clock();
        cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
    }
    
    p.route.assign(bestRoute.begin(), bestRoute.end());
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
    
    if (route.empty())
    {
        cout << "There isn't a route that can satify your need:(" << endl;
        return;
    }
    
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
  //  cout << cityNum["SH"] << endl;
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
    //    (temp->plan).isStation[cityNum[s]] = i;
    }
    
    if (temp->plan.type == 3)
    {
        cout << "And what's your time limit?" << endl;
        cin >> (temp->plan).timeLimit;
    }
    Design_Route(*temp);    //如果是中途改变，要保留当前边
    
    people.push_back(*temp);
    
    cout << "For client" << temp->name << ", Your route is:" << endl;
    Print_Route((temp->plan).source, temp->route);
}
