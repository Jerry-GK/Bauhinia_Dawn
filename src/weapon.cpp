#include "weapon.h"
#include "global.h"

Weapon::Weapon(const string setname ,const int setattack,int setoccupancy, int setcost)
{
    name = setname ;
    attack = setattack ;
    occupancy = setoccupancy;
    cost = setcost;
}

Weapon::~Weapon(){}

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
int Weapon::getcost() const 
{
    return cost ;
}
void Weapon::show() const 
{
    cout << "武器信息：" << endl;
    cout << "名称：" << name << endl;
    cout << "攻击力：" << attack << endl;
    cout << "价格：" << cost << endl;
    cout << "所占空间：" << occupancy << endl;
}
void Fork::show() const
{
    Weapon::show();
}
void Knife::show() const
{
    Weapon::show();
}
void Umbrella::show() const
{
    Weapon::show();
}
void Gun::show() const
{
    Weapon::show();
}

bool Weapon::isWeapon(string item)
{
    return global_set_weapons.find(item)!=global_set_weapons.end();
}

Weapon* Weapon::new_wep(string name)
{
    Weapon *ret = NULL;
    if(name==global_fork_name)
    {
        ret = new Fork();
    }
    else if(name==global_knife_name)
    {
        ret = new Knife();
    }
    else if(name==global_umbrella_name)
    {
        ret = new Umbrella();
    }
    else if(name==global_gun_name)
    {
        ret = new Gun();
    }
    return ret;
}

Fork::Fork() : Weapon(global_fork_name, global_fork_attack, global_fork_occupancy, global_fork_cost){};

Knife::Knife() : Weapon(global_knife_name,global_knife_attack,global_knife_occupancy, global_knife_cost){};

Umbrella::Umbrella() : Weapon(global_umbrella_name,global_umbrella_attack,global_umbrella_occupancy, global_umbrella_cost){};

Gun::Gun() : Weapon(global_gun_name,global_gun_attack,global_gun_occupancy, global_gun_cost){};