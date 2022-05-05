#include "zombie.h"

Zombie::Zombie (const string setname)
{
    name = setname ;
    if (setname == "roll")
    {
        aggress = 5;
        HP = 50 ;
        def = 10 ;
        EXP = 200;
    }
    else if (setname == "water")
    {
        aggress = 10 ;
        HP = 20 ;
        def = 12 ;
        EXP = 150 ;
    }
    else if (setname == "normal")
    {
        aggress = 3 ;
        HP = 30 ;
        def = 4 ;
        EXP = 20 ;
    }
}
void Zombie::show()
{
    cout<<"丧尸信息："<<endl;
    cout<<"名称："<<name<<endl;
    cout<<"攻击力："<<aggress<<endl;
    cout<<"血量："<<HP<<endl;
    cout<<"击败经验："<<EXP<<endl;
}

int Zombie::getHP  () const 
{
    return HP  ;
}
int Zombie::getEXP () const 
{
    return EXP ;
}
int Zombie::getdef () const 
{
    return def ;
}
string Zombie::getname () const 
{
    return name ;
}

void Zombie::attack(Player* p)
{
    cout << name << "发动了攻击！" << endl;
    p->getdamage (aggress) ;
}

void Zombie::getdamage(const int damage)//被攻击
{
    HP -= damage ;
    if (HP < 0)
    {
        HP = 0 ;
    }
    cout << "僵尸受到了 " << damage << "点伤害 , 当前生命值为： " << HP << endl; 
}
Zombie::~Zombie()
{

}