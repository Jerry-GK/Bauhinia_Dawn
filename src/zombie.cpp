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
    cout<<"ɥʬ��Ϣ��"<<endl;
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
string Zombie::getname () const 
{
    return name ;
}

void Zombie::attack(Player* p)
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