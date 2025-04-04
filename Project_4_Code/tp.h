#include "provided.h"
#include <string>
#include <unordered_set>
#include <queue>
#include <iostream>
using namespace std;


class TravelPlanner : public TravelPlannerBase {
private:
    unordered_set <string> m_preferred; //hashtable of preferred airlines
    struct Node {
        
        double m_g; //travel cost -->
        double m_h; //heuristic --> euclidean distance from cur airport to destination
        FlightSegment m_fs;
        int m_arrival;
        string m_airport;
        string prevAirport; //where the current airport comes from
        
        vector<FlightSegment> path;
        
        
        Node(double g, double h, string airport, int arrivalTime): m_fs(FlightSegment("", 0, "", "", 0, 0)) {
            //m_fs = fs;
            m_g = g;
            m_h = h;
            m_airport = airport;
            prevAirport = "";
            m_arrival = arrivalTime;
            
        }
        
        double f() const {return m_g + m_h;}
    };
    
    struct Compare {
        bool operator()(const Node& a, const Node& b) {
            return a.f() > b.f();
        }
    };
    
    void assignItinerary(Itinerary& it, Node destination);
    
public:
    TravelPlanner(const FlightManagerBase& flight_manager,
                  const AirportDB& airport_db) : TravelPlannerBase(flight_manager, airport_db) {}
    //~TravelPlanner();
    
    virtual void add_preferred_airline(std::string airline);
    virtual bool plan_travel(std::string source_airport, std::string destination_airport, int start_time, Itinerary& itinerary) const;

    
    
};

void TravelPlanner::add_preferred_airline(string airline) {
    m_preferred.insert(airline);
}


void TravelPlanner::assignItinerary(Itinerary &it, Node destination) {
//    while(destination.m_fs != nullptr) {
//        
//    }
}


bool TravelPlanner::plan_travel(string source_airport, string destination_airport, int start_time, Itinerary &itinerary) const {
    
    priority_queue <Node, std::vector<Node>, Compare> openSet;
    unordered_set<string> closedSet;
    //unordered_map<string, Node> searchNode; //associates an airport with a Node
    
    //unordered_map<string, FlightSegment*> searchFlight;
    
    openSet.push(Node (0, 0, source_airport, start_time));
    //cout << source_airport << " " << start_time << endl;
    bool firstFlight = true;
    
    
    while(!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();
        //cout << current.m_airport << "--> Heuristic: " << current.m_h << " , Arrival time: " << current.m_arrival << endl;
        
        if(current.m_airport == destination_airport) { //We've reached end destination
            //cerr << "HOORAY!" << current.m_arrival - start_time << endl;
//            string traceBack = current.m_airport;
//            
//            while(searchFlight.find(traceBack) != searchFlight.end()) {
//                cout << traceBack << endl;
//                FlightSegment* prev = searchFlight[traceBack];
//                itinerary.flights.push_back(*prev);
//                traceBack = prev->source_airport;
//            }
//
//            std::reverse(itinerary.flights.begin(), itinerary.flights.end());
            itinerary.flights = current.path;
            
            itinerary.source_airport = source_airport;
            itinerary.destination_airport = destination_airport;
            itinerary.total_duration = current.m_arrival - start_time;
            break;
        }
        if(closedSet.find(current.m_airport) != closedSet.end()) { //airport already visited before
            continue;
        }
        closedSet.insert(current.m_airport); //what happens when you double insert into an unordered_set??
        //Node toInsert = current;
        //searchNode.insert({current.m_airport, toInsert});
        
        
        vector<FlightSegment> flights = get_flight_manager().find_flights(current.m_airport, current.m_arrival, current.m_arrival + get_max_layover() + 1); //plus one because the end bound is exclusive
        //cout << "Current Node's Path size: " << current.path.size() << endl;
        
        for(int i = 0; i < flights.size(); i ++) {
            
            
            //preferred airline constraint
            if(!m_preferred.empty() && m_preferred.find(flights.at(i).airline) == m_preferred.end()) {
                continue; //preferred airline not found
            }
            
            //layover constraints
            int layover = flights.at(i).departure_time - current.m_arrival;
            if(layover < get_min_connection_time() && !firstFlight) {
                continue;
            }
            if(layover > get_max_layover()) {
                continue;
            }
            
            int nextFlightArrival = flights.at(i).departure_time + flights.at(i).duration_sec; //what time the next flight will land
            //max travel time duration constraint
            if(nextFlightArrival - start_time > get_max_duration()) {
                continue;
            }
            
            string nextAirport = flights.at(i).destination_airport;
            //airport already visited, so not optimal path
            if(closedSet.find(nextAirport) != closedSet.end()) {
                continue;
            }
            
            
            double g = flights.at(i).departure_time - current.m_arrival + flights.at(i).duration_sec + current.m_g; //layover + flight duration
            double h; //heuristic --> euclidean distance from the flight's destination to final destination
            bool dist = get_airport_db().get_distance(flights.at(i).destination_airport, destination_airport, h);
            if(!dist) {
                continue;
            }
            //^^should we check whether this guy is true or false???
            
            
            Node addFlight = Node(g, h, flights.at(i).destination_airport, nextFlightArrival);
            addFlight.prevAirport = current.m_airport;
            addFlight.m_fs = flights.at(i);
            addFlight.path = current.path;
            addFlight.path.push_back(flights.at(i));
            
            //cerr << "     " << addFlight.m_airport << " " << "Weight: " << addFlight.m_g + addFlight.m_h << endl;
            openSet.push(addFlight);
            
            
//            if(searchFlight.find(flights.at(i).destination_airport) == searchFlight.end()) {
//                searchFlight.insert({flights.at(i).destination_airport, fs});
//            } else {
//                int prior_departure = searchFlight[flights.at(i).destination_airport]->departure_time;
//                int prior_arrival = prior_departure + searchFlight[flights.at(i).destination_airport]->duration_sec;
//                
//                if(fs->departure_time + fs->duration_sec < prior_departure + prior_arrival) {
//                    searchFlight.insert({flights.at(i).destination_airport, fs});
//                }
//            }
            
        }
        firstFlight = false;
    }
    
//    for (unordered_map<string, FlightSegment*>::iterator it = searchFlight.begin(); it != searchFlight.end(); it ++) {
//        delete it->second;
//    }
    
    return true;
}





//    vector<FlightSegment> initial = get_flight_manager().find_flights(source_airport, start_time, start_time + get_max_layover());
//    cout << initial.size() << endl;
//    for(int i = 0; i < initial.size(); i ++) {
//        if(!m_preferred.empty() && m_preferred.find(initial.at(i).airline) == m_preferred.end()) { //there's a preferred flight
//            continue; //preferred flight not found
//        }
//
//        double g = initial.at(i).departure_time - start_time + initial.at(i).duration_sec; //g is the layover + travel_time
//        double h; //heuristic --> euclidean distance from the flight's destination to final destination
//        get_airport_db().get_distance(initial.at(i).destination_airport, destination_airport, h); //check if true?
//
//        Node* addFlight = new Node(g, h, &initial.at(i));
//        openSet.push(addFlight);
//    }
//
//    while(!openSet.empty()) {
//        cerr << "Leaving at: " << openSet.top()->m_fs->departure_time << " Duration: " << openSet.top()->m_fs->duration_sec << endl;
//        openSet.pop();
//    }
    
    
    //see if our priority queue sorts from least g+h to greatest g+h
    
    
    //REMEMBER TO DELETE ALL pointers, don't have leaking memory
    
    
    //airport DB provides the heuristic distance



//for(int i = 0; i < itinerary.flights.size(); i ++) {
//    FlightSegment temp = itinerary.flights.at(i);
//    cout << temp.source_airport << " " << temp.destination_airport << " : " << temp.departure_time << " " << temp.departure_time + temp.duration_sec << endl;
//    
//}
