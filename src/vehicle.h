#pragma once
#include <string>
#include <iostream>
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
    static bool isVehicle(string item) ;
    static Vehicle *new_veh(string name);
    virtual void show() const;
    virtual ~Vehicle() = 0;
};

class Bike:public Vehicle
{
public:
    Bike();
    void show() const;
};

class E_Bike:public Vehicle
{
public:
    E_Bike();
    void show() const;
};

class Car:public Vehicle
{
public:
    Car();
    void show() const;
};

class Boat:public Vehicle
{
public:
    Boat();
    void show() const;
};