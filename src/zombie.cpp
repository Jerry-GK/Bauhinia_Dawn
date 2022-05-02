#include "zombie.h"

void Zombie::show()
{
    cout<<"丧尸信息："<<endl;
    cout<<"名称："<<name<<endl;
    cout<<"攻击力："<<aggress<<endl;
    cout<<"攻击速度："<<frequency<<endl;
    cout<<"血量："<<HP<<endl;
}

void Zombie::attack(Player* p)
{

}
Zombie::~Zombie()
{

}