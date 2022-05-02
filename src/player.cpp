#include "player.h"

Player::Player()
{
    name="小泽";
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
    cout<<"拾取"<<item<<endl;
}

void Player::use(string item)
{
    cout<<"使用"<<item<<endl;
}

void Player::show_state()//显示玩家属性状态
{
    cout<<"玩家属性："<<endl;
    cout<<"姓名："<<name<<endl;
    cout<<"净攻击力："<<aggress<<endl;
    cout<<"体力（血量）："<<HP<<endl;
    cout<<"移动速度："<<speed<<endl;
    cout<<"所在地点："<<pos->get_name()<<endl;
}
Bag Player::get_bag()
{
    return this->mybag;
}