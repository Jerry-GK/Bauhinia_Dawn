#include "vehicle.h"


Vehicle::Vehicle(const string setname ,const int setspeed , const int setmove_capability)
{
    name = setname ;
    speed = setspeed ;
    move_capability = setmove_capability;
}
Vehicle::Vehicle(const string setname)
{
    name = setname ;
    move_capability=0;
    if (setname == "car")
    {
        speed = 15 ;
    }
    else if (setname == "bike")
    {
        speed = 4 ;
    }
    else if (setname == "e-bike")
    {
        speed = 7 ;
    }
    else if (setname == "boat")
    {
        speed = 3 ;
        move_capability = 1; 
    }
}
string Vehicle::getname() const 
{
    return name ;
}
int Vehicle::getspeed() const 
{
    return speed ;
}
int Vehicle::getmove_capability() const 
{
    return move_capability ;
}
bool isVehicle(string item)
{
    string Vehicle = "boat#bike#car#e-bike" ;
    return (Vehicle.find(item) < Vehicle.length() );
}
