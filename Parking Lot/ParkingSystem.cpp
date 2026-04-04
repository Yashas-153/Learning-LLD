/*

Design a Parking Lot System that can handle parking for different types of vehicles.

The system should support:

Multiple floors
Multiple parking spots on each floor
Different types of vehicles

Functionalities
1. Park a Vehicle -> assign the nearest available spot
2. Remove a Vehicle
3. Check Availability
4. Find Vehicle


Entities:

Vehicle
ParkingLot
ParkingFloor
ParkingSpot
Ticket

*/

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<memory>

using namespace std;

enum class VehicleType {
    MOTORCYCLE,
    CAR,
    TRUCK
};

enum class SpotType {
    MOTORCYCLE,
    CAR,
    TRUCK
};

enum class StatusType {
    ACTIVE,
    CLOSED
};

class Vehicle{
private:
    string licenseNumber;
    VehicleType type;
public:
    Vehicle(string license_number, VehicleType type) : licenseNumber(license_number), type(type) {}

    string getLicenseNumber(){
        return licenseNumber;
    }
    VehicleType getVehicleType(){
        return type;
    }
};

class Car : public Vehicle{  
public:
    Car(string licenseNumber) : Vehicle(licenseNumber,VehicleType::CAR) {}
};

class Motorcycle : public Vehicle{  
public:
    Motorcycle(string licenseNumber) : Vehicle(licenseNumber,VehicleType::MOTORCYCLE) {}
};

class Truck : public Vehicle{  
public:
    Truck(string licenseNumber) : Vehicle(licenseNumber,VehicleType::TRUCK) {}
};

class ParkingSpot{
private:
    int id;
    SpotType type;
    Vehicle* vehicle; 

public:
    ParkingSpot(int id, SpotType type) : id(id), type(type), vehicle(nullptr) {}

    bool isFree(){
        return vehicle == nullptr;
    }

    void parkVehicle(Vehicle *v){
        vehicle = v;        
    }

    void removeVehicle(){
        vehicle = nullptr;
    }

    Vehicle* getVehicle(){
        return vehicle;
    }
};


class ParkingFloor{
private:
    int id;
    map<SpotType, vector<unique_ptr<ParkingSpot>>> spots;
public:
    ParkingFloor(int id, int noOfCarSpots, int noOfMCSpots, int noOfTruckSpots): id(id) {
        int spotId = 0;
        for(int i=0;i<noOfCarSpots;i++){
            spots[SpotType::CAR].push_back(make_unique<ParkingSpot>(spotId++,SpotType::CAR));
        }
        for(int i=0;i<noOfMCSpots;i++){
            spots[SpotType::MOTORCYCLE].push_back(make_unique<ParkingSpot>(spotId++,SpotType::MOTORCYCLE));
        }
        for(int i=0;i<noOfTruckSpots;i++){
            spots[SpotType::TRUCK].push_back(make_unique<ParkingSpot>(spotId++,SpotType::TRUCK));
        }
    }
    
    ParkingSpot* getFreeSpot(VehicleType type){
        SpotType stype = static_cast<SpotType>(type);
        for(auto &spot :spots[stype]){
            if(spot->isFree()){
                return spot.get();
            }
        }
        return nullptr;
    }
    ParkingSpot* parkVehicle(Vehicle *vehicle){
        ParkingSpot *spot = getFreeSpot(vehicle->getVehicleType());
        if(spot){
            spot->parkVehicle(vehicle);
            return spot;
        }
        return nullptr;
    }
    int getAvailableSpots(SpotType type){
        int count = 0;
        for(auto &spot : spots[type]){
            if(spot->isFree()) count++;
        }
        return count;
    }
};


class PricingStrategy{
public:
    virtual int calculateFee(VehicleType type) = 0;
    virtual ~PricingStrategy() = default;
};


class FlatFreePricingStrategy : public PricingStrategy{
public:
    FlatFreePricingStrategy() {}

    int calculateFee(VehicleType type) {
        switch(type){
            case VehicleType::MOTORCYCLE:
                return 5;
            case VehicleType::CAR:
                return 10;
            case VehicleType::TRUCK:
                return 20;  
        }
        return 0;
    }
};

class Ticket{
private:
    static int ticketCounter;
    int id;
    Vehicle *vehicle;
    ParkingSpot *spot;
    int entryTime;
    int exitTime;
    StatusType status;
    unique_ptr<PricingStrategy> pricingStrategy;

public:
    Ticket(Vehicle *vehicle, ParkingSpot *spot, int entryTime): vehicle(vehicle), spot(spot), entryTime(entryTime) {
        id = ticketCounter++;
        status = StatusType::ACTIVE;
        pricingStrategy = make_unique<FlatFreePricingStrategy>();
    }

    void closeTicket(){
        status = StatusType::CLOSED;
    }

    int calculateFee(){
        return pricingStrategy->calculateFee(vehicle->getVehicleType());        
    }

    ParkingSpot* getSpot(){
        return spot;
    }

};

int Ticket::ticketCounter = 0;

class ParkingLot{
private :
    int id;
    int noOfFloors;
    vector<unique_ptr<ParkingFloor>> floors;

public:
    ParkingLot(int id, int noOfFloors){
        for(int i=0;i<noOfFloors;i++){
            floors.push_back(make_unique<ParkingFloor>(i, 10, 10, 5));
        }
    }
    ParkingSpot* parkVehicle(Vehicle *vehicle){
        for(auto &floor:floors){
            ParkingSpot *spot = floor->parkVehicle(vehicle);
            if(spot) return spot;
        }
        return nullptr;
    }
};

class ParkingService{
private:
    unique_ptr<ParkingLot> lot;
    map<string,unique_ptr<Ticket>> tickets;

public:
    ParkingService(){
        lot = make_unique<ParkingLot>(1,3);
    }


    Ticket* parkVehicle(Vehicle *vehicle, int entryTime){

        ParkingSpot* spot = lot->parkVehicle(vehicle);

        if(!spot) {
            cout<<"No Spot Available"<<endl;
            return nullptr;
        }

        auto ticket = make_unique<Ticket>(vehicle, spot, entryTime);
        Ticket* ticketPtr = ticket.get();

        tickets[vehicle->getLicenseNumber()] = std::move(ticket);

        return ticketPtr;
    }

    void removeVehicle(string licenseNumber){

        auto it = tickets.find(licenseNumber);
        if(it == tickets.end()) return;
        
        Ticket *ticket = it->second.get();
        ticket->closeTicket();
        int fee = ticket->calculateFee();
        cout << "Fee: " << fee << endl;

        ticket->getSpot()->removeVehicle();
        tickets.erase(it);
    }

    ParkingSpot* findVehicle(string licenseNumber){
        auto it = tickets.find(licenseNumber);
        if(it == tickets.end()) return nullptr;
        return it->second->getSpot();
    }
};

int main() {

    ParkingService service;

    // Create vehicles
    Vehicle* car1 = new Car("KA01AB1234");
    Vehicle* bike1 = new Motorcycle("KA02XY5678");

    // Park vehicles
    cout << "Parking vehicles..." << endl;

    Ticket* t1 = service.parkVehicle(car1, 10);
    Ticket* t2 = service.parkVehicle(bike1, 12);

    // Find vehicle
    cout << "\nFinding vehicle KA01AB1234..." << endl;
    ParkingSpot* spot = service.findVehicle("KA01AB1234");
    if(spot) cout << "Vehicle found!" << endl;
    else cout << "Vehicle not found!" << endl;

    // Remove vehicle
    cout << "\nRemoving vehicle KA01AB1234..." << endl;
    service.removeVehicle("KA01AB1234");

    return 0;
}

