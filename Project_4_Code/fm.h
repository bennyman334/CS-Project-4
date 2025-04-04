#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "provided.h"
#include "bstset.h"
using namespace std;


//bool operator<(const FlightSegment& lhs, const FlightSegment& rhs) {
//    if(lhs.departure_time != rhs.departure_time) {
//        return lhs.departure_time < rhs.departure_time;  // Compare flights based on flight number
//    }
//    return lhs.duration_sec < rhs.duration_sec;
//}

bool operator==(const FlightSegment& lhs, const FlightSegment& rhs) {
    return lhs.departure_time == rhs.departure_time && lhs.source_airport == rhs.source_airport && lhs.destination_airport == rhs.destination_airport && lhs.duration_sec == rhs.duration_sec && lhs.flight_no == rhs.flight_no;
}

//bool operator>(const FlightSegment& lhs, const FlightSegment& rhs) {
//    return lhs.departure_time > rhs.departure_time;  // Compare flights based on flight number
//}

bool operator<(const FlightSegment& first, const FlightSegment& second) {
    if (first.departure_time < second.departure_time)
        return true;
    else if (second.departure_time < first.departure_time)
        return false;
    else {
        if (first.destination_airport < second.destination_airport)
            return true;
        else if (second.destination_airport < first.destination_airport)
            return false;
        else {
            if (first.source_airport < second.source_airport)
                return true;
            else if (second.source_airport < first.source_airport)
                return false;
            else {
                if (first.airline < second.airline)
                    return true;
                else if (second.airline < first.airline)
                    return false;
                else {
                    if (first.flight_no < second.flight_no)
                        return true;
                    else if (second.flight_no < first.flight_no)
                        return false;
                    else {
                        return false;
                    }
                }
            }
        }
    }
}

class FlightManager: public FlightManagerBase {
public:
    //FlightManager();
    //~FlightManager();
    virtual bool load_flight_data(std::string filename);
    virtual std::vector<FlightSegment> find_flights(std::string source_airport, int start_time, int end_time) const;
    
private:
    unordered_map <string, BSTSet<FlightSegment>> m_flights;
};


bool FlightManager::load_flight_data(std::string filename) {
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Can't open airport database: " << filename << std::endl;
        return false;
    }
    
    std::string line;
    while (std::getline(file, line))
    {
        
        std::istringstream ss(line);
        string airline;
        string flightNum_str;
        string src; //three letter abbrev. for source airport
        string dest; //three letter abbrev. for destination airport
        string depart_time;
        string arrival_time;
        string duration_str;
        
        if (!std::getline(ss, airline, ',') ||
            !std::getline(ss, flightNum_str, ',') ||
            !std::getline(ss, src, ',') ||
            !std::getline(ss, dest, ',') ||
            !std::getline(ss, depart_time, ',') ||
            !std::getline(ss, arrival_time, ',') ||
            !std::getline(ss, duration_str, ','))
            continue;
        
        //cerr << airline << " " << flightNum_str << " " << src << " " << dest << " " << depart_time << " " << arrival_time << " " << duration_str << endl;
        
        int flightNum = std::stoi(flightNum_str);
        int departure = std::stoi(depart_time);
        //int arrival = std::stoi(arrival_time);
        int duration = std::stoi(duration_str);
        
        
//        if(src == "DEN" && dest == "SEA" && departure == 1736311200 && duration == 7200) {
//            cout << "Boom Found!" << endl;
//        }
        
        FlightSegment fs(airline, flightNum, src, dest, departure, duration);
        m_flights[src].insert(fs);
        
//        if(src == "DEN" && dest == "SEA" && departure == 1736311200 && duration == 7200) {
//            BSTSet<FlightSegment>::SetIterator setIt = m_flights["DEN"].find(fs);
//            const FlightSegment* fs1 = setIt.get_and_advance();
//            cout << fs1->departure_time << endl;
//        }
        
        //m_airports[code] = { latitude, longitude };
    }
    
//    FlightSegment fs2 ("Southwest Airlines",540,"DEN","SEA",1736311200,7200);
//    
//    BSTSet<FlightSegment>::SetIterator setIt = m_flights["DEN"].find(fs2);
//    const FlightSegment* fs1 = setIt.get_and_advance();
//    //cout << fs1->departure_time << endl;
//    
//    FlightSegment temp("", 0, "", "", 1736311200, 0);
//    BSTSet<FlightSegment>::SetIterator setIt2 =  m_flights["DEN"].find_first_not_smaller(temp);
//    
//    //vector<FlightSegment> segs = m_flights.find_flights("DEN", 1736307540, 1736321941);
//
//    const FlightSegment* get = setIt2.get_and_advance();
//    
//    //cout << get->departure_time << endl;
    
    return true;
}


std::vector<FlightSegment> FlightManager::find_flights(std::string source_airport, int start_time, int end_time) const {
    
    std::vector<FlightSegment> found;
    auto it = m_flights.find(source_airport);
    if (it == m_flights.end()) {
        return found;
    }
    FlightSegment temp("", 0, "", "", start_time, 0);
    BSTSet<FlightSegment>::SetIterator iter = it->second.find_first_not_smaller(temp);
    const FlightSegment* fs;
    while ((fs = iter.get_and_advance()) != nullptr) {
        if (fs->departure_time >= end_time) {
            break;
        }
        found.push_back(*fs);
    }
    return found;
    
}




