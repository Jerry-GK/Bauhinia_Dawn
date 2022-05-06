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
    Zombie();
    Zombie (const string setname , const int setaggress , const int setHP , const int setdef , const int setEXP) ;
    virtual void show();
    virtual void attack(Player* p);
    virtual ~Zombie();
    void getdamage(const int damage);//被攻击
    int getHP  () const ;
    int getEXP () const ;
    int getdef () const ;
    int getaggress() const ;
    string getname () const ;   
};

class Roll_Zombie:public Zombie
{
public:
    Roll_Zombie();
    void attack(Player* p) ;
    void special_attack(Player *p);
};

class Water_Zombie:public Zombie
{
public:
    Water_Zombie();
    void attack(Player* p) ;
    void special_attack(Player *p);
};