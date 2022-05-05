#pragma once
#include <string>
#include "player.h"
using namespace std;

class Player;

class Zombie
{
private:
    string name;
    int  aggress;//������
    int  HP;//Ѫ��
    int def;//����
    int EXP;//�����ܵľ���ֵ

public:
    Zombie (const string setname) ;
    virtual void show();
    virtual void attack(Player* p);
    virtual ~Zombie();
    void getdamage(const int damage);//������
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