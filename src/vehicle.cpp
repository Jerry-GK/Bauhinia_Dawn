#include "vehicle.h"


Vehicle::Vehicle(const string setname ,const int setspeed , const int setmove_capability)
{
    name = setname ;
    speed = setspeed ;
    move_capability = setmove_capability;
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
