#pragma once
#include <string>
#include "player.h"
using namespace std;

class Player;

class Zombie
{
private:
    string name;
    int  aggress;//攻击力
    int  HP;//血量
    int def;//防御
    int EXP;//被击败的经验值

public:
    Zombie (const string setname) ;
    virtual void show();
    virtual void attack(Player* p);
    virtual ~Zombie();
    void getdamage(const int damage);//被攻击
    int getHP  () const ;
    int getEXP () const ;
    int getdef () const ;
    string getname () const ;   
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