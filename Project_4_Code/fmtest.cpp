//#include "fm.h"
//#include "bstset.h"
//#include "provided.h"
//#include <iostream>
//using namespace std;
//
//
////bool operator<(const FlightSegment& lhs, const FlightSegment& rhs) {
////    return lhs.departure_time < rhs.departure_time;  // Compare flights based on flight number
////}
////
////bool operator>(const FlightSegment& lhs, const FlightSegment& rhs) {
////    return lhs.departure_time > rhs.departure_time;  // Compare flights based on flight number
////}
//
//int main () {
//    cout << "hello" << endl;
//    
//    FlightManager fm;
//    fm.load_flight_data("/Users/benjaminli/Documents/CS Coursework/CS 32/CS32_Project4/CS32_Project4/someflights.txt");
//    vector<FlightSegment> vs = fm.find_flights("CVG", 1736260200, 1736346840);
//    
//    cout << vs.size() << endl;
//    
//    BSTSet<FlightSegment> bset;
//    FlightSegment fs("Delta", 10, "SFO", "LAX", 11000000, 3600);
//    FlightSegment fs2("21 Air", 507, "CVG", "HRL", 1736260440, 3600);
//    
//    if(fs2 > fs) {
//        cout << "bingo!" << endl;
//    } else {
//        cout << "fuck off" << endl;
//    }
//    
//    
////    unordered_map <string, BSTSet<int>> m_flights;
////    
////    unordered_map <string, BSTSet<FlightSegment>> m_flights1;
////    
////    m_flights["polaris"].insert(5);
////    m_flights["southwest"].insert(3);
////    
////    FlightSegment fs("Delta", 10, "SFO", "LAX", 11000000, 3600);
////    m_flights1["SFO"].insert(fs);
//    //m_flights.find("polaris");
//    //FlightManager fm;
//    
//}
