#pragma once
#include <string>
using namespace std;
class Vehicle
{
protected:
    string name;
    double speed;
public:
    virtual ~Vehicle()=0;
};

class Bike:public Vehicle
{

};

class Car:public Vehicle
{

};

class Boat:public Vehicle
{

};

