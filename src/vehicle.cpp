#include "vehicle.h"
#include "global.h"

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
bool Vehicle::isVehicle(string item)
{
    return global_set_vehicles.find(item)!=global_set_vehicles.end();
}
 
void Vehicle::show() const
{
    string str = move_capability == 1 ? "入水" : "无";
    cout << "载具信息：" << endl;
    cout << "名称：" << name << endl;
    cout <<"速度：" <<speed << endl;
    cout << "特殊功能："<<str << endl;
}

void Bike::show() const
{
    Vehicle::show();
}
void E_Bike::show() const
{
    Vehicle::show();
}
void Car::show() const
{
    Vehicle::show();
}
void Boat::show() const
{
    Vehicle::show();
}

Vehicle::~Vehicle() {}

Vehicle* Vehicle::new_veh(string name)
{
    Vehicle *ret = NULL;
    if(name==global_bike_name)
    {
        ret = new Bike();
    }
    else if(name==global_ebike_name)
    {
        ret = new E_Bike();
    }
    else if(name==global_car_name)
    {
        ret = new Car();
    }
    else if(name==global_boat_name)
    {
        ret = new Boat();
    }
    return ret;
}
Bike::Bike() : Vehicle(global_bike_name, global_bike_speed, global_bike_mc){};

E_Bike::E_Bike() : Vehicle(global_ebike_name,global_ebike_speed,global_ebike_mc){};

Car::Car() : Vehicle(global_car_name,global_car_speed,global_car_mc){};

Boat::Boat() : Vehicle(global_boat_name,global_boat_speed,global_boat_mc){};
