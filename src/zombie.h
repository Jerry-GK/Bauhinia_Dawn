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
    int award_money; //���ܺ��õ�Ǯ
    int special_attack_chance; //���⹥���ļ���

public:
    Zombie();
    Zombie (const string setname , const int setaggress , const int setHP , const int setdef , const int setEXP, const int set_money ,const int set_chance) ;
    virtual void show();
    void attack(Player* p);
    virtual void special_attack(Player *p);
    virtual ~Zombie();

    void getdamage(const int damage);//������
    void attack_weaken(int a);//attack debuff
    void def_weaken(int b);//def debuff

    int getHP  () const ;
    int getEXP () const ;
    int getdef () const ;
    int getaggress() const ;
    int getmoney() const ;
    int getchance() const ;//���⹥�������ĸ���
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