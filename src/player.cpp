#include "player.h"

Player::Player()
{
    name = global_player_name ;
    level = 1;
    currentEXP = 0 ;
    aggress =  global_initial_agress;
    currentHP = global_initial_currentHP;
    MAXHP = initial_MAXHP;
    speed = global_initial_speed ;
    move_capability = global_initial_move_capability ;
    money = global_initial_money;
    for (int i = 0 ; i < 9 ; i++)
    {
        needEXP[i] = global_initial_EXP[i] ;
    }
    cur_veh = NULL ;
    cur_wep=NULL;
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

int Player::get_move_capability() const
{
    return move_capability ;
}

Vehicle* Player::get_vehicle() const
{
    return cur_veh;    
}

Weapon* Player::get_weapon() const
{
    return cur_wep;
}

int Player::getweaponaggress() const
{
    return (cur_wep==NULL)?0:cur_wep->getattack();
}

int Player::getmoney() const
{
    return money;
}

void Player::equipWeapon(Weapon* a ) //装备武器
{
    cur_wep =  a ;
    cout << "装备了武器：" << a->getname() << " ,武器攻击力为：" << a->getattack() << endl << endl; 
}

void Player::disequipWeapon () //装备武器
{
    if(cur_wep==NULL)
    {
        cout<<"当前未装备武器"<<endl;
        return;
    }
    cout << "卸下了武器：" << cur_wep->getname() << " ,武器攻击力为：" << cur_wep->getattack() << endl << endl; 
    delete cur_wep ;
    cur_wep = NULL ;
}
void Player::take_vehicle (Vehicle* a) //上车 ，速度、移动能力 被 交通工具 设置
{
    if(a==NULL)
    {
        cout << "不存在该交通工具！" << endl;
        return;
    }
    if(cur_veh!=NULL)
    {
        cout<<"你已经在"<<cur_veh->getname()<<"上了，请先离开该交通工具。"<<endl;
        return;
    }
    a->show();
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
    speed = global_initial_speed ;
    move_capability = global_initial_move_capability;
    cout<<"离开"<<cur_veh->getname()<<endl;
    delete cur_veh;
    cur_veh=NULL;
}
void Player::changeHP(const int change)//恢复/损失生命值
{
    currentHP += change ;
    if (currentHP > MAXHP)
    {
        currentHP = MAXHP ;
    }
    if(currentHP<0)
        currentHP = 0;
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
    changeHP(0.1 * MAXHP) ;
    level ++ ;
    aggress += 1 ;
    //升级会使得最大体力值提升 ，同时恢复10%最大体力值的体力 ， 攻击力 + 1
    cout << "升级：你获得了经验值并升到了"<<level<<"级！" << endl;
}

void Player::change_money(const int m)
{
    money = money + m;
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
    string str_wep=(cur_wep==NULL)?"赤手空拳":cur_wep->getname();
    cout<<"玩家属性："<<endl;
    cout<<"姓名："<<name<<endl;
    cout<<"等级："<<level<<endl;
    if (level != 10 ) {cout<<"经验："<<currentEXP<<"  升级需要："<<needEXP[level-1] << endl;}
    else {cout << "你已经达到了最高等级： level 10 !" << endl;} //这里存在 满级时数组越界的bug 需要判断是否满级
    cout<<"攻击力："<<aggress<<endl;
    cout<<"武器攻击力："<<this->getweaponaggress()<<endl;
    cout<<"当前体力/最大体力： "<<currentHP<<"/"<<MAXHP<<endl;
    cout << "现金数量：￥" << money << endl;
    cout<<"移动速度："<<speed<<endl;
    cout<<"交通工具："<<str_veh<<endl;
    cout<<"当前武器："<<str_wep<<endl;
    cout<<"当前位置："<<pos->get_name()<<endl;
}

Bag Player::get_bag() const
{
    return this->mybag;
}

Vehicle* Player::get_veh()
{
    return this->cur_veh;
}

void Player::pick(string item, PICK_MODE mode)//mode==0: pick ,mode==1: buy
{
    if (Food::isFood(item) )
    {
        Food *a = Food::new_food(item);
        a->show();

        if (mybag.add(item,a->getoccupancy() ) )
        {
            if(a->getname()==global_bread_name && mode==BUY)
            {
                Bread *b = dynamic_cast<Bread *> (a);
                if(getmoney()<b->getcost())
                {
                    cout << "购买失败！所需花费￥" << b->getcost() <<", 剩余￥"<<getmoney() << endl;
                    delete a;
                    return;
                }
                change_money(-b->getcost());
                cout << "花费￥" << b->getcost() <<", 剩余￥"<<getmoney() << endl;
            }
            cout << "拾取/购买了 " << item << " 背包剩余空间：" << mybag.getmaxcapacity()-mybag.getcurcapacity() << endl;
        }
        else
        {
            cout << "拾取/购买失败 需要空间：" << a->getoccupancy() 
            << "  ，当前空闲空间： " <<  mybag.getmaxcapacity() - mybag.getcurcapacity() ;
        }
        delete a;
    }
    else if (Weapon::isWeapon (item))
    {
        Weapon *a = Weapon::new_wep(item);
        a->show();
       if (mybag.add(item,a->getoccupancy() ) )
        {
            if(mode==BUY)
            {
                if(getmoney()<a->getcost())
                {
                    cout << "购买失败！所需花费￥" << a->getcost() <<", 剩余￥"<<getmoney() << endl;
                    delete a;
                    return;
                }
                change_money(-a->getcost());
                cout << "花费￥" << a->getcost() <<", 剩余￥"<<getmoney() << endl;
            }
            cout << "拾取/购买了 " << item << " 背包剩余空间：" << mybag.getmaxcapacity()-mybag.getcurcapacity() << endl;
        }
        else 
        {
            cout << "拾取失败 需要空间：" << a->getoccupancy() 
            << "  ，当前空闲空间： " <<  mybag.getmaxcapacity()- mybag.getcurcapacity() ;
        }
        delete a;
    }
    else
    {
        cout<<"无效指令：不存在该类物品！"<<endl;
    }
}

void Player::use(string item)
{
    if(!mybag.find(item))
    {
        cout << "使用失败！背包内不存在这个物品" << endl;
        return;
    }
    if ( Food::isFood(item) )
    {
        Food *a = Food::new_food(item);
        if(a->getname()==global_bread_name)
        {
            Bread *b = dynamic_cast<Bread *> (a);
            changeHP(b->geteffect());
            mybag.det(item);
            cout << "使用了 " << item << " 回复体力至：" << currentHP << endl;
            //使用食物 恢复体力 食物消失
        }
        else if(a->getname()==global_apple_name)
        {
            Apple *b = dynamic_cast<Apple *> (a);
            changeHP(b->geteffect());
            mybag.det(item);
            cout << "使用了 " << item << " 回复体力至：" << currentHP << endl;
            //使用食物 恢复体力 食物消失           
        }
        else 
        {
            cout << "当前无法使用该物品！" << endl;
        }
        delete a;
    }
    else if (Weapon::isWeapon (item ) )
    {
        disequipWeapon();
        Weapon* p =  Weapon::new_wep (item) ;
        equipWeapon(p);
    }
    else
    {
        cout<<"无效指令：不存在该类物品！"<<endl;
    }
}

void Player::drop(string item)
{
    if (mybag.find(item))
    {
        if (Food::isFood(item))
        {
            mybag.det(item);
        }
        else if (Weapon::isWeapon(item))
        {
            if (cur_wep!=NULL && item == cur_wep->getname())
            {
                disequipWeapon();
            }
            mybag.det(item);
        }
        cout << "丢弃/赠予了 " << item << " ，当前背包剩余容量：" <<mybag.getmaxcapacity() - mybag.getcurcapacity() << endl;
    }
    else
    {
        cout << "丢弃/赠予失败！背包内不存在这个物品" << endl;
    }
}

bool Player::have(string item)
{
    return mybag.find(item);
}

//--------------------------------------to be implemented------------------------------------------------
bool Player::move_to(Position* p)
{
    if(p==NULL)
    {
        cout<<"不存在该地点！"<<endl;
        return false; 
    }
    cout << "当前状态下前往" << p->get_name() << "需要消耗体力: " << get_HPcost(p) << "，是否确认前往？（输入 \"yes\" 确认）" << endl;
    string ensure;
    getline(cin, ensure);
    if(ensure!="yes")
    {
        cout << "你没有选择前往" << p->get_name() << endl;
        return false;
    }
    if (getcurrentHP() < get_HPcost(p))
    {
        cout << "当前载具下，体力无法支撑你前往该地点！" << endl;
        return false;
    }
    this->set_pos(p);
    cout<<"来到："<<p->get_name()<<endl;
    //调用体力消耗函数
    this->currentHP -= get_HPcost(p);
    return true;
}

int Player::get_HPcost(Position *p)//得到当前位置去p的体力消耗值
{
    //to be fill!!!!!!!
    return 0;
}

int Player::fight(Zombie *z) //打赢了返回2 逃跑返回1 被击败返回0
{
    int round = 1 ;
    string msg = "" ;
    cout << "\n开始战斗 , 你要击败的是： " << z->getname() << endl; 
    z->show();
    cout << "\n你当前状态：" << endl; 
    cout << "HP/MAX = " << currentHP << "/" << MAXHP << "  当前力量/武器攻击力 = " << aggress 
         << "/" << this->getweaponaggress() << endl;
    while (1)
    {
        cout << "\nRound" << round << endl << "你的选择操作是(fighting状态只能按提示操作):" << endl 
             <<  "hit: 攻击丧尸\nuse <武器名>: 更换武器/使用食物(也会被攻击！)\nescape: 逃跑"  << endl << "\n<fighting> Please Enter: " ;
        getline(cin,msg);
        if (msg == "escape")
        {
            cout << "\n你感觉有些不对劲 , 你逃跑了！留得青山在,不怕没柴烧" << endl;
            return 1 ;
        }
        else if((msg.find("use")==0)&&msg.length()>=5)
        {
            this->use(msg.substr(4,msg.length()-4));
            msg.clear();
        }
        else if (msg == "hit")
        {
            attack(cur_wep,z) ;
            if (! z->getHP()) //打败了僵尸
            {
                cout << "\n你克服困难,终于击败了丧尸！" << endl;
                this->gainEXP(z->getEXP());
                return 2;
            }
        }
        else
        {
            cout << endl << "指令无效, 请按提示操作！" << endl;
            msg.clear();
            continue;
        }

        z->attack(this);
        if ( !getcurrentHP() )//被僵尸打败
        {
            cout << "\n很遗憾,你棋差一招，被丧尸击败了" << endl;
            return 0 ;
        }
        round++;
    }
}

void Player::getdamage(const int damage)//被攻击
{
    currentHP -= damage ;
    if (currentHP < 0)
    {
        currentHP = 0 ;
    }
    cout << "你受到了 " << damage << "点伤害 , 当前体力为： " << currentHP << endl; 
}

void Player::attack(Weapon *a,Zombie *z)
{
    cout  << "你发动了攻击！" << endl;
    //rand(20) + aggress > def can dealt damage to zombie by your weapon + 1;
    if ( rand()*20 + aggress > z->getdef())
    {
        z->getdamage (aggress*0.3+this->getweaponaggress() + 1) ;
    }
    else 
    {
        cout << "你未能击穿丧尸的护甲 , 不要放弃尝试！" << endl;
    }

}