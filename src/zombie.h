#pragma once
#include <string>
#include "player.h"
using namespace std;

class Player;

class Zombie
{
protected:
    string name;
    int  zombieaggress;//������
    int  HP;//Ѫ��

public:
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