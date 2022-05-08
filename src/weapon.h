#pragma once
#include <string>
#include <iostream>
using namespace std;

class Weapon//≥ÈœÛ¿‡
{
private:
    string name ;
    int attack ;
    int occupancy ;
    int cost;

public:
    Weapon(const string setname, const int setattack, const int setoccupancy, int setcost);
    string getname() const;
    int getattack() const;
    int getoccupancy() const;
    int getcost() const;
    virtual void show() const;
    virtual ~Weapon() = 0;
    static bool isWeapon(string item) ;
    static Weapon *new_wep(string name);
};

class Fork:public Weapon
{
public:
    Fork();
    void show() const;
};

class Knife:public Weapon
{
public:
    Knife();
    void show() const;
};

class Umbrella:public Weapon
{
public:
    Umbrella();
    void show() const;
};

class Gun:public Weapon
{
public:
    Gun();
    void show() const;
};