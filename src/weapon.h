#pragma once
#include <string>
#include <iostream>
#include "zombie.h"
using namespace std;

class Zombie;

class Weapon
{
private:
    string name ;
    int attack ;
    int occupancy ;
    int cost;
    int special_attack_chance ;
    string property ;
public:
    Weapon(const string setname, const int setattack, const int setoccupancy,const int setcost ,const int chance , const string setpro );
    void attack_buff(int a) ;
    string getname() const;
    int getattack() const;
    int getoccupancy() const;
    int getcost() const;
    int getchance() const ;
    virtual void show() const;
    virtual ~Weapon() = 0;
    int wep_attack(Zombie* z);
    virtual int wep_special_attack(Zombie *z) = 0;
    static bool isWeapon(string item) ;
    static Weapon *new_wep(string name);
};

class Fork:public Weapon
{
public:
    Fork();
    void show() const;
    int wep_special_attack(Zombie* z);
};

class Knife:public Weapon
{
public:
    Knife();
    void show() const;
    int wep_special_attack(Zombie* z);
};

class Umbrella:public Weapon
{
public:
    Umbrella();
    void show() const;
    int wep_special_attack(Zombie* z);
};

class Gun:public Weapon
{
public:
    Gun();
    void show() const;
    int wep_special_attack(Zombie* z);
};

class BloodSickle:public Weapon
{
public:
    BloodSickle();
    void show() const;
    int wep_special_attack(Zombie* z);
};