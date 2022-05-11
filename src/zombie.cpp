#include "zombie.h"

Zombie::Zombie()
{
    name=global_ordinary_name;
    aggress=global_ordinary_aggress;
    HP=global_ordinary_HP;
    def=global_ordinary_def;
    EXP=global_ordinary_EXP;
    award_money = global_ordinary_money;
}
Zombie::Zombie (const string setname , const int setaggress , const int setHP , const int setdef , const int setEXP, const int setmoney) 
{
    name = setname ;
    aggress = setaggress ;
    HP = setHP ;
    def = setdef ;
    EXP  = setEXP ;
    award_money = setmoney;
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

string Zombie::getname () const 
{
    return name ;
}

void Zombie::attack(Player* p) // һ�㹥��
{
    cout <<"\n"<< name << "�����˹�����" << endl;
    //_sleep(0.4*1000);
    p->getdamage (aggress) ;
}

void Zombie::getdamage(const int damage)//������
{
    HP -= damage ;
    if (HP < 0)
    {
        HP = 0 ;
    }
    cout << "��ʬ�ܵ��� " << damage << "���˺� , ��ǰ����ֵΪ�� " << HP << endl; 
}

Zombie::~Zombie()
{

}

//roll zombie  -------------------------------------------
Roll_Zombie::Roll_Zombie():Zombie
(global_roll_name,global_roll_aggress,global_roll_HP,global_roll_def,global_roll_EXP, global_roll_money) {}

void Roll_Zombie::attack(Player* p)
{
    int num = rand() % 20 ;
    if (num < 15)  //���⹥������Ϊ5/20 = 25%
    {
        cout << "\n" << getname() << "�����˹�����" << endl;
        p->getdamage (getaggress()) ;
    }
    else  special_attack(p) ;
}

void Roll_Zombie::special_attack(Player *p)
{
    cout << getname() << "��Ȼ���������⹥��,ʹ�ó��Ŷ���ľ���֮����" << endl;
    cout << "�������ͻȻ���ܿ���,������һ��Ȼ������˵���" << endl; 
    p->getdamage (getaggress() + p->getweaponaggress() / 2 ) ;
    if (p->getcurrentHP()) {p->disequipWeapon() ;} //��ֹ��ɫ�����˻�����������
}

//water  zombie  -------------------------------------------

Water_Zombie::Water_Zombie():Zombie
(global_water_name,global_water_aggress,global_water_HP,global_water_def,global_water_EXP, global_water_money) {}

void Water_Zombie::attack(Player* p)
{
    int num = rand() % 20 ;
    if (num < 19)  //�������Ϊ1/20 = 5%
    {
        cout << "\n" << getname() << "�����˹�����" << endl;
        p->getdamage (getaggress()) ;
    }
    else  special_attack(p) ;
}

void Water_Zombie::special_attack(Player *p)
{
    cout << getname() << "��Ȼ���������⹥��,�����ϵ���ˮ�" << endl;
    cout << "Ȼ�����������Ӿ,��ˮ��Ҳ����һ��" << endl; 
    p->getdamage(999);
}