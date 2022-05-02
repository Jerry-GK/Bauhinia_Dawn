#include "weapon.h"


    Weapon::Weapon(const string setname ,const int setattack)
    {
        name = setname ;
        attack = setattack ;
    }
    string Weapon::getname() const
    {
        return name ;
    }
    int Weapon::getattack() const 
    {
        return attack ;
    }


