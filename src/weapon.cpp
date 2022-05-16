#include "weapon.h"
#include "global.h"
using namespace std;
Weapon::Weapon(const string setname ,const int setattack,int setoccupancy, int setcost , int setchance)
{
    name = setname ;
    attack = setattack ;
    occupancy = setoccupancy;
    cost = setcost;
    special_attack_chance = setchance ;
}

Weapon::~Weapon(){}

void Weapon::attack_buff(int a)
{
    attack += a ;
    cout << "���" << this->getname() << "�Ĺ�����������" << a << "��"  << "����ǰ����������Ϊ" << attack << endl ;
}

string Weapon::getname() const
{
    return name ;
}
int Weapon::getattack() const 
{
    return attack ;
}
int Weapon::getoccupancy() const 
{
    return occupancy ;
}
int Weapon::getcost() const 
{
    return cost ;
}
int Weapon::getchance() const
{
    return special_attack_chance ;
}

void Weapon::show() const 
{
    cout << "������Ϣ��" << endl;
    cout << "���ƣ�" << name << endl;
    cout << "��������" << attack << endl;
    cout << "�۸�" << cost << endl;
    cout << "��ռ�ռ䣺" << occupancy << endl;
}
void Fork::show() const
{
    Weapon::show();
}
void Knife::show() const
{
    Weapon::show();
    cout << "�ۻ�Ա����ʾ�����ֵ��߿�������ɥʬ�Ĺ�������" << endl;
}
void Umbrella::show() const
{
    Weapon::show();
    cout << "���ԣ�����һ��ˮ�������������ԶԻ�����ɥʬ��ɶ���Ч����δʵ�֣�" << endl;
}
void Gun::show() const
{
    Weapon::show();
    cout << "���ԣ�����һ�ֻ������������м��ʱ�ͷ�����Զ�ˮɥʬ��ɶ����˺�Ч��" << endl;
}

int Weapon::wep_attack(Zombie* z)
{
    int num = rand() % 100 ;
    if (num > getchance())  
    {
        //special case
        if(this->name==global_gun_name && z->getname()==global_water_name)
        {
            cout << "��Ļ�����ǹ��ˮɥʬ�����˫���˺���" << endl;
            return 2*getattack();
        }
        return getattack();
    }
    else
        return wep_special_attack(z) ;
} 

int Fork::wep_special_attack(Zombie* z) 
{
    cout << "���׼���㣬�ò��Ӷ�ɥʬ�����˸���׼�Ĺ�����" << endl;
    return getattack() * (1.0 + (rand() % 10) / 10.0);
}

int Knife::wep_special_attack(Zombie* z) 
{
    cout << "˵ʱ����ʱ�죬��Ѹ�͵���С�����׵ؿ�����ɥʬһ���ֵ�����" << endl;
    z->attack_weaken(z->getaggress() * 0.5 ) ;
    return getattack() + rand() % 8;
}

int Umbrella::wep_special_attack(Zombie* z) 
{
    cout << "����ɡ�ݺݵش���ɥʬ��ͷ������о�����Ĺ����𽥱�������!" << endl;
    attack_buff(1) ;
    return getattack() + rand() % 5;
}

int Gun::wep_special_attack(Zombie* z) 
{
    cout << "����ϸ����׼��"<<z->getname()<<"ɥʬ��ͷ��������������������ǹ, ��ͷ��" << endl;
    return z->getHP();
}

bool Weapon::isWeapon(string item)
{
    return global_set_weapons.find(item)!=global_set_weapons.end();
}

Weapon* Weapon::new_wep(string name)
{
    Weapon *ret = NULL;
    if(name==global_fork_name)
    {
        ret = new Fork();
    }
    else if(name==global_knife_name)
    {
        ret = new Knife();
    }
    else if(name==global_umbrella_name)
    {
        ret = new Umbrella();
    }
    else if(name==global_gun_name)
    {
        ret = new Gun();
    }
    return ret;
}

Fork::Fork() : Weapon(global_fork_name, global_fork_attack, global_fork_occupancy, global_fork_cost , global_fork_chance){};

Knife::Knife() : Weapon(global_knife_name,global_knife_attack,global_knife_occupancy, global_knife_cost ,global_knife_chance){};

Umbrella::Umbrella() : Weapon(global_umbrella_name,global_umbrella_attack,global_umbrella_occupancy, global_umbrella_cost , global_umbrella_chance){};

Gun::Gun() : Weapon(global_gun_name,global_gun_attack,global_gun_occupancy, global_gun_cost, global_gun_chance){};
