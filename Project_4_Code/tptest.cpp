//#include "tp.h"
//#include "fm.h"
//#include <iostream>
//using namespace std;
//  tptest.cpp
//  CS32_Project4
//
//  Created by Benjamin Li on 3/17/25.
//
//
//void printFlightSegment(FlightSegment fs) {
//    cout << fs.airline << " " << fs.flight_no << " " << fs.source_airport << " " << fs.destination_airport << " " << fs.departure_time << " " << fs.duration_sec << endl;
//}
//
//int main () {
//    cout << "hello" << endl;
//    
//    FlightManager fm;
//    fm.load_flight_data("/Users/benjaminli/Library/Developer/Xcode/DerivedData/CS32_Project4-exryrwgepsmwfkfllkjpdllaednd/Build/all_flights.txt");
//    
//    AirportDB adb;
//    adb.load_airport_data("/Users/benjaminli/Documents/CS Coursework/CS 32/CS32_Project4/CS32_Project4/airports.txt");
//    
//    BSTSet<FlightSegment> test;
//    
//    vector<FlightSegment> segs = fm.find_flights("DEN", 1736311200, 1736321941);
//    
//    cout << segs.size() << endl;
//    
//    for (int i = 0; i < segs.size(); i++) {
//        printFlightSegment(segs.at(i));
//    }
    
    
    
//    TravelPlanner tp(fm, adb);
//    Itinerary it;
//    tp.plan_travel("CVG", "SAN", 1736347200, it);
//    for (int i = 0; i < it.flights.size(); i ++) {
//        printFlightSegment(it.flights.at(i));
//    }
    
    
        //tp.plan_travel("CVG", "SAN", 1736347200, it);
    
    
//    FlightSegment fs1 = FlightSegment("21 Air", 405, "SFO", "CVG", 1736220840, 27360);
//    FlightSegment fs2 = FlightSegment("21 Air", 405, "SFO", "CVG", 1736307240, 27360);
//    test.insert(fs1);
//    test.insert(fs2);
//    
//    
//    
//    BSTSet<FlightSegment>::SetIterator set = test.find_first_not_smaller(FlightSegment("21 Air", 405, "SFO", "CVG", 1736220840, 27360));
    

    
    
    
//    test.insert(FlightSegment("21 Air", 405, "SFO", "CVG", 1736220840, 1736248200, 27360));
//    test.insert(FlightSegment("21 Air", 405, "SFO", "CVG", 1736220840, 1736248200, 27360));
    
    //vector<FlightSegment> segs = fm.find_flights("SFO", 1736220840, 1736356500);
    
    
    
    
    
//    //cout <<
//    cout << "Size: " << segs.size() << endl;
//    
//    TravelPlanner tp(fm, adb);
//    Itinerary it;
//    tp.plan_travel("CVG", "SAN", 1736347200, it);
//    
//    for (int i = 0; i < it.flights.size(); i ++) {
//        printFlightSegment(it.flights.at(i));
//    }
    
//    vector<FlightSegment> initial = fm.find_flights("CVG", 1736260200, 1736260200 + 12*3600);
//    cout << initial.size() << endl;
    
//    FlightSegment fs ("21 Air", 2026, "CVG", "EWR", 1736359200, 6960);
//    FlightSegment fs1("21 Air", 405, "CVG", "EWR", 1736359200, 6960);
//    if(1736307240 > 1736359200) {
//        cout << "FUCK YOU" << endl;
//    }
    //double dist;
    //adb.get_distance("SFO", "LAX", dist);
    //cout << "Distance from SFO to LAX is: " << dist << endl;
//}
