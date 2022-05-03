#pragma once
#include <string>
#include "player.h"
using namespace std;

class Player;

class Zombie
{
protected:
    string name;
    int  aggress;//攻击力
    int  HP;//血量
    int frequency;//攻击速度

public:
    virtual void show();
    virtual void attack(Player* p);
    virtual ~Zombie();

};

class Roll_Zombie:public Zombie
{

};

class Security_Zombie:public Zombie
{

};


class Water_Zombie:public Zombie
{

};