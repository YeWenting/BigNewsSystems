//
//  TrafficNet.cpp
//  Travel-Simulation-System I
//
//  Created by YeWenting. on 16/4/10.
//  Copyright © 2016年 Apart I, 404. All rights reserved.
//

#include "TrafficNet.h"

void Tour::RotateCities( const int& c1,
                        const int& c2,
                        const int& c3 )
{
    int c1_new = c1 == 0 ? 1 : c1;
    
    std::vector<int>::iterator it1 = cities.begin() + c1_new;
    std::vector<int>::iterator it2 = cities.begin() + c2;
    std::vector<int>::iterator it3 = cities.begin() + c3;
    
    rotate( it1, it2, it3 );
}

void Tour::ReverseCities( const int& c1, const int& c2 )
{
    int c1_n = c1 < c2 ? c1 : c2;
    int c2_n = c1 < c2 ? c2 : c1;
    
    if ( c1_n == 0 ) c1_n = 1;
    
    std::vector<int>::iterator it1, it2;
    
    it1 = cities.begin() + c1_n;
    it2 = cities.begin() + c2_n;
    
    reverse( it1, it2 );
}

void TSPalgorithm::Run()
{
    tour.Reset();
    tour.CreateRandomTour();
    //tour.CreateNearestNeighbourTour();
    size = tour.TourSize();
    
    // Create the optimal tour
    for ( int i = 0; i < iterations; i++ )
    {
        Rotate( i );
        Reverse( i );
        SwapRandomPair( i );
        Notify( (const int&) tour.TourDistance(), (const int&) i );
    }
}