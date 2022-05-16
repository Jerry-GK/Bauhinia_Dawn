#include "zombie.h"

Zombie::Zombie()
{
    name=global_ordinary_name;
    aggress=global_ordinary_aggress;
    HP=global_ordinary_HP;
    def=global_ordinary_def;
    EXP=global_ordinary_EXP;
    award_money = global_ordinary_money;
    special_attack_chance=global_ordinary_chance;
}
Zombie::Zombie (const string setname , const int setaggress , const int setHP , const int setdef , const int setEXP, const int setmoney ,const int setchance) 
{
    name = setname ;
    aggress = setaggress ;
    HP = setHP ;
    def = setdef ;
    EXP  = setEXP ;
    award_money = setmoney;
    special_attack_chance = setchance ;
}
void Zombie::show()
{
    cout << "丧尸信息: " << endl;
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

int Zombie::getmoney() const 
{
    return award_money;
}

int Zombie::getchance() const
{
    return special_attack_chance ;
}

string Zombie::getname () const 
{
    return name ;
}

void Zombie::attack(Player* p) // 一般攻击
{
    int num = rand() % 100 ;
    if (num > getchance())  
    {
        cout << "\n" << getname() << "发动了攻击！" << endl;
        p->getdamage (getaggress()) ;
    }
    else  special_attack(p) ;
}

void Zombie::special_attack(Player *p)
{
    cout << getname() << "竟然发动了特殊攻击,造成了暴击！" << endl;
    p->getdamage(2 * getaggress() + rand() % 10 - 3);
}

//fight ------------------------------
void Zombie::getdamage(const int damage)//被攻击
{
    HP -= damage ;
    if (HP < 0)
    {
        HP = 0 ;
    }
    cout << "僵尸受到了 " << damage << "点伤害 , 当前生命值为： " << HP << endl; 
}

void Zombie::attack_weaken(int a)//attack debuff
{
    if (aggress > a)
    {
        aggress -= a ;
        cout << "僵尸的攻击力被削弱了 " << a << " 点 , 当前攻击力为：" << aggress << endl;
    }
    else
    {
        aggress = 0;
        cout << "僵尸的攻击力被削弱了 " << aggress << " 点 , 当前攻击力为：" << aggress << endl;
    }
}
void Zombie::def_weaken(int b)//def debuff
{
    if (def > b)
    {
        def -= b ;
        cout << "僵尸的防御力被削弱了 " << b << " 点 , 当前防御力为：" << def << endl;
    }
    else
    {
        def = 0;
        cout << "僵尸的防御力被削弱了 " << def << " 点 , 当前防御力为：" << def << endl;
    }
}


Zombie::~Zombie()
{

}

//roll zombie  -------------------------------------------
Roll_Zombie::Roll_Zombie():Zombie
(global_roll_name,global_roll_aggress,global_roll_HP,global_roll_def,global_roll_EXP, global_roll_money , global_roll_chance) {}

void Roll_Zombie::special_attack(Player *p)
{
    if (p->get_weapon() != NULL)
    {   
        cout << getname() << "竟然发动了特殊攻击,使用沉寂多年的卷王之力！" << endl;
        cout << "你的武器突然不受控制,攻击了你一下然后掉在了地上" << endl; 
        p->getdamage (getaggress() + p->getweaponaggress() / 2 ) ;
        if (p->getcurrentHP()) {p->disequipWeapon() ;} //防止角色死亡了还丢弃武器！
    }
    else
    {
        cout << getname() << "竟然发动了特殊攻击,使用沉寂多年的卷王之力！" << endl;
        cout << "它控制了教室里的书本，一齐向你飞来" << endl;
        p->getdamage (getaggress() + rand() % 5) ;
    }
    
}

//water  zombie  -------------------------------------------

Water_Zombie::Water_Zombie():Zombie
(global_water_name,global_water_aggress,global_water_HP,global_water_def,global_water_EXP, global_water_money , global_water_chance) {}

void Water_Zombie::special_attack(Player *p)
{
    cout << getname() << "竟然发动了特殊攻击,将你拖到了水里！" << endl;
    cout << "然而哪怕你会游泳,在水里也难逃一死" << endl; 
    p->getdamage(p->getcurrentHP());
}