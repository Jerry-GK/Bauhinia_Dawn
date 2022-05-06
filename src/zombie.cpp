#include "zombie.h"

Zombie::Zombie()
{
    name="normal";
    aggress=7;
    HP=30;
    def=2;
    EXP=80;
}
Zombie::Zombie (const string setname , const int setaggress , const int setHP , const int setdef , const int setEXP) 
{
    name = setname ;
    aggress = setaggress ;
    HP = setHP ;
    def = setdef ;
    EXP  = setEXP ;
}
void Zombie::show()
{
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

int Zombie::getaggress () const 
{
    return aggress ;
}

string Zombie::getname () const 
{
    return name ;
}

void Zombie::attack(Player* p) // 一般攻击
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

//roll zombie  -------------------------------------------
Roll_Zombie::Roll_Zombie():Zombie("roll",5,50,10,200) {}

void Roll_Zombie::attack(Player* p)
{
    int num = rand() % 20 ;
    if (num < 15)  //特殊攻击概率为5/20 = 25%
    {
        cout << getname() << "发动了攻击！" << endl;
        p->getdamage (getaggress()) ;
    }
    else  special_attack(p) ;
}

void Roll_Zombie::special_attack(Player *p)
{
    cout << getname() << "竟然发动了特殊攻击,使用沉寂多年的卷王之力！" << endl;
    cout << "你的武器突然不受控制,扎了你一下然后掉在了地上" << endl; 
    p->getdamage (getaggress() + p->getweaponaggress() / 2 ) ;
    if (p->getcurrentHP()) {p->disequipWeapon() ;} //防止角色死亡了还丢弃武器！
}

//water  zombie  -------------------------------------------

Water_Zombie::Water_Zombie():Zombie("water",10,20,12,150) {}

void Water_Zombie::attack(Player* p)
{
    int num = rand() % 20 ;
    if (num < 19)  //特殊概率为1/20 = 5%
    {
        cout << getname() << "发动了攻击！" << endl;
        p->getdamage (getaggress()) ;
    }
    else  special_attack(p) ;
}

void Water_Zombie::special_attack(Player *p)
{
    cout << getname() << "竟然发动了特殊攻击,将你拖到了水里！" << endl;
    cout << "然而哪怕你会游泳,在水里也难逃一死" << endl; 
    p->getdamage(999);
}