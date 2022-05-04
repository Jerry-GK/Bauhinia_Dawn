#include "weapon.h"


Weapon::Weapon(const string setname ,const int setattack)
{
    name = setname ;
    attack = setattack ;
}
Weapon::Weapon(const string setname)
{
    name = setname ;
    if (setname == "fork")
    {
        attack = 1 ;
        occupancy = 4;
    }
    else if (setname == "knife")
    {
        attack = 7 ;
        occupancy = 3 ;
    }
    else if (setname == "umbrella")
    {
        attack = 4 ;
        occupancy = 10 ;
    }
    else if(setname == "gun")
    {
        attack=20;
        occupancy=8;
    }
}
string Weapon::getname() const
{
    return name ;
}
int Weapon::getattack() const 
{
    return attack ;
}
int Weapon::getoccupancy() const 
{
    return occupancy ;
}
bool isWeapon(string item)
{
    string Weapon = "fork#knife#umbrella#gun" ;
    return (Weapon.find(item) < Weapon.length() );
}

