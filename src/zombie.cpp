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
    cout << "ɥʬ��Ϣ: " << endl;
    cout<<"���ƣ�"<<name<<endl;
    cout<<"��������"<<aggress<<endl;
    cout<<"Ѫ����"<<HP<<endl;
    cout<<"���ܾ��飺"<<EXP<<endl;
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

void Zombie::attack(Player* p) // һ�㹥��
{
    int num = rand() % 100 ;
    if (num > getchance())  
    {
        cout << "\n" << getname() << "�����˹�����" << endl;
        p->getdamage (getaggress()) ;
    }
    else  special_attack(p) ;
}

void Zombie::special_attack(Player *p)
{
    cout << getname() << "��Ȼ���������⹥��,����˱�����" << endl;
    p->getdamage(2 * getaggress() + rand() % 10 - 3);
}

//fight ------------------------------
void Zombie::getdamage(const int damage)//������
{
    HP -= damage ;
    if (HP < 0)
    {
        HP = 0 ;
    }
    cout << "��ʬ�ܵ��� " << damage << "���˺� , ��ǰ����ֵΪ�� " << HP << endl; 
}

void Zombie::attack_weaken(int a)//attack debuff
{
    if (aggress > a)
    {
        aggress -= a ;
        cout << "��ʬ�Ĺ������������� " << a << " �� , ��ǰ������Ϊ��" << aggress << endl;
    }
    else
    {
        aggress = 0;
        cout << "��ʬ�Ĺ������������� " << aggress << " �� , ��ǰ������Ϊ��" << aggress << endl;
    }
}
void Zombie::def_weaken(int b)//def debuff
{
    if (def > b)
    {
        def -= b ;
        cout << "��ʬ�ķ������������� " << b << " �� , ��ǰ������Ϊ��" << def << endl;
    }
    else
    {
        def = 0;
        cout << "��ʬ�ķ������������� " << def << " �� , ��ǰ������Ϊ��" << def << endl;
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
        cout << getname() << "��Ȼ���������⹥��,ʹ�ó��Ŷ���ľ���֮����" << endl;
        cout << "�������ͻȻ���ܿ���,��������һ��Ȼ������˵���" << endl; 
        p->getdamage (getaggress() + p->getweaponaggress() / 2 ) ;
        if (p->getcurrentHP()) {p->disequipWeapon() ;} //��ֹ��ɫ�����˻�����������
    }
    else
    {
        cout << getname() << "��Ȼ���������⹥��,ʹ�ó��Ŷ���ľ���֮����" << endl;
        cout << "�������˽�������鱾��һ���������" << endl;
        p->getdamage (getaggress() + rand() % 5) ;
    }
    
}

//water  zombie  -------------------------------------------

Water_Zombie::Water_Zombie():Zombie
(global_water_name,global_water_aggress,global_water_HP,global_water_def,global_water_EXP, global_water_money , global_water_chance) {}

void Water_Zombie::special_attack(Player *p)
{
    cout << getname() << "��Ȼ���������⹥��,�����ϵ���ˮ�" << endl;
    cout << "Ȼ�����������Ӿ,��ˮ��Ҳ����һ��" << endl; 
    p->getdamage(p->getcurrentHP());
}