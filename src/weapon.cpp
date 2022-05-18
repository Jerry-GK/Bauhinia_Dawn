#include "weapon.h"
#include "global.h"
using namespace std;
Weapon::Weapon(const string setname ,const int setattack,const int setoccupancy,const int setcost ,const int setchance , const string setpro = "")
{
    name = setname ;
    attack = setattack ;
    occupancy = setoccupancy;
    cost = setcost;
    special_attack_chance = setchance ;
    property = setpro ;
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
    else if(name==global_bloodsickle_name)
    {
        ret = new BloodSickle();
    }
    return ret;
}
void Weapon::show() const 
{
    cout << "������Ϣ��" << endl;
    cout << "���ƣ�" << name << endl;
    cout << "��������" << attack << endl;
    cout << "�۸�" << cost << endl;
    cout << "��ռ�ռ䣺" << occupancy << endl;
    cout << "����: " ; if (property == "") {cout << "������" << endl;} else {cout << property << endl;}
}
bool Weapon::isWeapon(string item)
{
    return global_set_weapons.find(item)!=global_set_weapons.end();
}

int Weapon::wep_attack(Zombie* z)
{
    //counter relation
    if (property == "water" )
    {
        if (z->getpro() == "fire")
        {
            return wep_special_attack(z);
        } // water to fire
        else if (z->getpro() == "water")
        {
            cout << "���ˮ����������ˮ����ɥʬ�Ĺ�����Ч��΢, ֻ�����һС�����˺���" << endl;
            return 0.3*getattack();
        } //water to water
    }
    else if (property == "fire")
    {
        if (z->getpro() == "water")
        {
            return wep_special_attack(z);
        } //fire to water
        else if (z->getpro() == "fire")
        {
            cout << "��Ļ����������Ի�����ɥʬ�Ĺ�����Ч��΢��ֻ�����һС�����˺���" << endl;
            return 0.3*getattack();
        } //fire to fire
    }

    //no counter relation
    int num = rand() % 100 ;
    if (num > getchance())  
    {
        return getattack() ;
    }
    else
        return wep_special_attack(z) ;
} 



// fork ---------------------------------------
Fork::Fork() : Weapon(global_fork_name, global_fork_attack, global_fork_occupancy, global_fork_cost , global_fork_chance ){};
void Fork::show() const
{
    Weapon::show();
    cout << "���ԣ�<��׼>����һ�ֽ����������������������е���Ҫ��" << endl;
}
int Fork::wep_special_attack(Zombie* z) 
{
    cout << "���׼���㣬�ò��Ӷ�ɥʬ�����˸���׼�Ĺ�����" << endl;
    return getattack() * (1.0 + (rand() % 10) / 10.0);
}

// knife  ---------------------------------------
Knife::Knife() : Weapon(global_knife_name,global_knife_attack,global_knife_occupancy, global_knife_cost ,global_knife_chance){};
void Knife::show() const
{
    Weapon::show();
    cout << "���ԣ�<�²�>�ۻ�Ա����ʾ�����ֵ��߿���ͨ������ɥʬ�������乥������" << endl;
}
int Knife::wep_special_attack(Zombie* z) 
{
    cout << "˵ʱ����ʱ�죬��Ѹ�͵���С�����׵ؿ�����ɥʬһ���ֵ�����" << endl;
    z->attack_weaken(z->getaggress() * 0.5 ) ;
    return getattack() + rand() % 8;
}

// umbrella ---------------------------------------
Umbrella::Umbrella() : Weapon(global_umbrella_name,global_umbrella_attack,global_umbrella_occupancy, global_umbrella_cost , global_umbrella_chance ,global_umbrella_property){};
void Umbrella::show() const
{
    Weapon::show();
    cout << "���ԣ�<��¶>����һ��ˮ�������������ԶԻ�����ɥʬ���ǿ��Ķ���Ч������ˮɥʬ�˺���С" << endl;
}
int Umbrella::wep_special_attack(Zombie* z) 
{
    if(z->getpro()==global_fire_property)
    {
        cout << "ˮ���Ե�ɡ�Ի�����ɥʬ���������Ч�������ƺ��������˲��٣�˲����ʧ��һ��������ֵ��" << endl;
        return z->getHP() / 2 + global_fire_HP / 10;
    }
    cout << "����ɡ�ݺݵش���ɥʬ��ͷ������о�����Ĺ����𽥱�������!" << endl;
    attack_buff(1) ;
    return getattack() + rand() % 5;
}

// gun  ---------------------------------------
Gun::Gun() : Weapon(global_gun_name,global_gun_attack,global_gun_occupancy, global_gun_cost, global_gun_chance ,global_gun_property){};
void Gun::show() const
{
    Weapon::show();
    cout << "���ԣ�<��ͷ>����һ�ֻ������������м��ʱ�ͷ��ɱ�����Զ�ˮɥʬ��ɶ����˺�Ч�����Ի�ɥʬ��в����" << endl;
}
int Gun::wep_special_attack(Zombie* z) 
{
    if(z->getpro()==global_water_property)
    {
        cout << "��Ȼ��ˮɥʬ��ͷ�ƺ��������ã�����ҩ��������Щ��ˮɥʬ�������������˫���˺��������������ܴ��ˣ�" << endl;
        return 2 * getattack();
    }
    cout << "����ϸ����׼��"<<z->getname()<<"ɥʬ��ͷ��������������������ǹ, ��ͷ��" << endl;
    return z->getHP();
}

//bloodsickle ---------------------------------
BloodSickle::BloodSickle() : Weapon(global_bloodsickle_name,global_bloodsickle_attack,global_bloodsickle_occupancy, global_bloodsickle_cost, global_bloodsickle_chance ){};
void BloodSickle::show() const
{
    Weapon::show();
    cout << "���ԣ�<����>Ѫ����������������״̬���������״̬��ÿ�ι������л�����ȡ�Է���ѪҺת��Ϊ������, ����������ʧЧ..." << endl;
}
int BloodSickle::wep_special_attack(Zombie* z) 
{
    int damage =  getattack() * 1.5  + rand() % 5;
    attack_buff(damage * 0.35) ;
    cout << "Ѫ��Խ��Խ���ȣ���ȡ��ɥʬ��ѪҺ����ø���ǿ���ˡ�Ѫ������������"<< getattack()<< endl;
    return damage ;
}



