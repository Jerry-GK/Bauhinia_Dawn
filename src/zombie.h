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
    int award_money; //击败后获得的钱
    int special_attack_chance; //特殊攻击的几率
    string property;//属性，默认为无属性

public:
    Zombie();
    Zombie (const string setname , const int setaggress , const int setHP , const int setdef , const int setEXP, const int set_money ,const int set_chance , const string setpro) ;
    virtual void show();
    void attack(Player* p);
    virtual void special_attack(Player *p);
    virtual ~Zombie();

    void getdamage(const int damage);//被攻击
    void attack_weaken(int a);//attack debuff
    void def_weaken(int b);//def debuff

    int getHP  () const ;
    int getEXP () const ;
    int getdef () const ;
    int getaggress() const ;
    int getmoney() const ;
    int getchance() const ;//特殊攻击发动的概率
    string getpro() const ;
    string getname () const ;   
};

class Roll_Zombie:public Zombie
{
public:
    Roll_Zombie();
    void attack(Player* p) ;
    void special_attack(Player *p);
    void show();
};

class Water_Zombie:public Zombie
{
public:
    Water_Zombie();
    void attack(Player* p) ;
    void special_attack(Player *p);
    void show();
};

class Fire_Zombie:public Zombie
{
public:
    Fire_Zombie();
    void attack(Player* p) ;
    void special_attack(Player *p);
    void show();
};