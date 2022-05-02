#pragma once
#include <string>
using namespace std;
class Vehicle
{
private:
    string name;
    int speed;
    int move_capability ;
public:
    Vehicle(const string setname ,const int setspeed , const int setmove_capability);
    string getname() const ;
    int getspeed() const ;
    int getmove_capability() const ;
};


