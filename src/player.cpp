#include "player.h"

Player::Player()
{
    name = "小泽" ;
    level = 1;
    currentEXP = 0 ;
    aggress =  initial_currentHP;
    currentHP = initial_currentHP;
    MAXHP = initial_MAXHP;
    speed = initial_speed ;
    move_capability = initial_move_capability ;
    for (int i = 0 ; i < 9 ; i++)
    {
        needEXP[i] = initial_EXP[i] ;
    }
    cur_veh = NULL ;
    pl_status = UNKNOWN;
    pos=NULL;
}

int Player::getAggress() const
{
    return aggress ;
}

int Player::getMAXHP() const
{
    return MAXHP ;
}

int Player::getcurrentHP () const
{
    return currentHP ;
}

int Player::getspeed () const
{
    return speed ;
}

int Player::getmove_capability() const
{
    return move_capability ;
}

void Player::equipWeapon(Weapon* a)
{
    weaponaggress = a->getattack() ;
    cout<<"装备武器"<<a->getname();
}

void Player::disequipWeapon (Weapon* a)  //卸下武器 ， 人物的武器攻击力值 = 0 ；
{
    weaponaggress = 0 ;
    cout<<"丢下武器："<<a->getname();
}
void Player::take_vehicle (Vehicle* a) //上车 ，速度、移动能力 被 交通工具 设置
{
    if(cur_veh!=NULL)
    {
        cout<<"你已经在"<<cur_veh->getname()<<"上了，请先离开该交通工具。"<<endl;
    }
    speed = a->getspeed() ;
    move_capability = a->getmove_capability() ;
    cur_veh = a;
    cout<<"乘坐"<<cur_veh->getname()<<endl;
}
void Player::get_off_vehicle()//下车 ，速度、移动能力 恢复成 $初始值$
{
    if(cur_veh==NULL)
    {
        cout<<"你现在没有乘坐交通工具！"<<endl;
        return;
    }
    speed = initial_speed ;
    move_capability = initial_move_capability;
    cout<<"离开"<<cur_veh->getname()<<endl;
    delete cur_veh;
    cur_veh=NULL;
}
void Player::recoverHP(const int recovery)//恢复生命值
{
    currentHP += recovery ;
    if (currentHP > MAXHP)
    {
        currentHP = MAXHP ;
    }
}

void Player::gainEXP(const int EXP) //获得经验值
{
    currentEXP += EXP ;
    while(currentEXP >= needEXP[level-1])
    {
        levelUP(level) ;
    }
}

void Player::levelUP(int currentlevel)//升级 
{
    currentEXP -= needEXP[level - 1] ;
    MAXHP += needEXP[level-1] / 10 ;
    recoverHP(0.1 * MAXHP) ;
    level ++ ;
    aggress += 1 ;
    //升级会使得最大体力值提升 ，同时恢复10%最大体力值的体力 ， 攻击力 + 1
    show_info("levelUP::something need to be writed");
}

//new:

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

void Player::show_state()//显示玩家属性状态
{
    string str_veh=(cur_veh==NULL)?"脚":cur_veh->getname();
    cout<<"玩家属性："<<endl;
    cout<<"姓名："<<name<<endl;
    cout<<"等级："<<level<<endl;
    if (level != 10 ) {cout<<"经验："<<currentEXP<<"  升级需要："<<needEXP[level-1] << endl;}
    else {cout << "你已经达到了最高等级： level 10 !" << endl;} //这里存在 满级时数组越界的bug 需要判断是否满级
    cout<<"攻击力："<<aggress<<endl;
    cout<<"武器攻击力："<<weaponaggress<<endl;
    cout<<"当前体力/最大体力： "<<currentHP<<"/"<<MAXHP<<endl;
    cout<<"移动速度："<<speed<<endl;
    cout<<"交通工具："<<str_veh<<endl;
    cout<<"当前位置："<<pos->get_name()<<endl;
}

Bag Player::get_bag()
{
    return this->mybag;
}

Vehicle* Player::get_veh()
{
    return this->cur_veh;
}


//--------------------------------------to be implemented------------------------------------------------
void Player::move_to(Position* p)
{
    this->set_pos(p);
    //根据当前pos与目标p的距离(根据xy坐标)，以及速度，计算体力变化的逻辑
}

void Player::pick(string item)
{
    cout<<"拾取"<<item<<endl;
}

void Player::use(string item)
{
    cout<<"使用"<<item<<endl;
    /*分析item字符串
    食物名（bread）：消耗，恢复体力
    武器名：调用equipweapon拿起相应武器
    */
}

void Player::drop(string item)
{
    cout<<"丢弃"<<item<<endl;
}

void fight(Zombie *z)
{
    //与丧尸的战斗逻辑
}