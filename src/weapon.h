#pragma once
#include <string>
using namespace std;

class Weapon
{
private:
    string name ;
    int attack ;
    int occupancy ;
public:
    Weapon(const string setname);
    Weapon(const string setname ,const int setattack);
    string getname()const ;
    int getattack()const ;
    int getoccupancy()const ;
};

bool isWeapon(string item) ;