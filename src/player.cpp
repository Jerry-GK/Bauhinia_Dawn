#include "player.h"

Player::Player()
{
    name="С��";
    aggress=10;
    HP=100;
    speed=10;
    cur_veh=NULL;
    pl_status=UNKNOWN;
    pos=NULL;
}

void Player::set_pos(Position* p)
{
    this->pos=p;
    this->pl_status=p->get_status().front();
}

void Player::set_status(PLAYER_STAGE s)
{
    this->pl_status=s;
}


Position* Player::get_pos()
{
    return this->pos;
}

PLAYER_STAGE Player::get_status()
{
    return pl_status;
}

void Player::pick(string item)
{
    cout<<"ʰȡ"<<item<<endl;
}

void Player::use(string item)
{
    cout<<"ʹ��"<<item<<endl;
}

void Player::show_state()//��ʾ�������״̬
{
    cout<<"������ԣ�"<<endl;
    cout<<"������"<<name<<endl;
    cout<<"����������"<<aggress<<endl;
    cout<<"������Ѫ������"<<HP<<endl;
    cout<<"�ƶ��ٶȣ�"<<speed<<endl;
    cout<<"���ڵص㣺"<<pos->get_name()<<endl;
}
Bag Player::get_bag()
{
    return this->mybag;
}