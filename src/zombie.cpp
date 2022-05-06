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

string Zombie::getname () const 
{
    return name ;
}

void Zombie::attack(Player* p) // һ�㹥��
{
    cout << name << "�����˹�����" << endl;
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
Roll_Zombie::Roll_Zombie():Zombie("roll",5,50,10,200) {}

void Roll_Zombie::attack(Player* p)
{
    int num = rand() % 20 ;
    if (num < 15)  //���⹥������Ϊ5/20 = 25%
    {
        cout << getname() << "�����˹�����" << endl;
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

Water_Zombie::Water_Zombie():Zombie("water",10,20,12,150) {}

void Water_Zombie::attack(Player* p)
{
    int num = rand() % 20 ;
    if (num < 19)  //�������Ϊ1/20 = 5%
    {
        cout << getname() << "�����˹�����" << endl;
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