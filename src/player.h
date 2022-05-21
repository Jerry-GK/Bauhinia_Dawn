#pragma once
#include <string>
#include <iostream>
#include "weapon.h"
#include "bag.h"
#include "zombie.h"
#include "vehicle.h"
#include "game_map.h"
#include "global.h"
#include "food.h"
#include <sstream>
#include <stdlib.h> 
#include <math.h>

using namespace std;

class Weapon;
class Vehicle;
class Zombie;
class Player
{
private:
    string name;
    int level ; //等级，初始：1，最高level：10
    int currentEXP ; //经验
    int aggress;//攻击力

    int currentHP;//当前体力
    int MAXHP ; //最大体力上限

    int speed;//移动速度
    int move_capability;//移动能力（为0时只能在陆地行走，为1时可以两栖）

    int money;//手里钱的数量

    Bag mybag;//背包
    Vehicle* cur_veh;//当前乘坐的交通工具（NULL表示双脚）
    Weapon* cur_wep;//当前的武器（NULL表示双手）
    PLAYER_STAGE pl_cur_status;//玩家状态
    PLAYER_STAGE pl_last_status;//玩家上一个状态
    Position* cur_pos;//玩家当前的位置
    Position *last_pos;//玩家上一个位置（开始为NULL）

public:
    Player();
    Player(const int getcurrentHP ,const int getMAXHP, const int getspeed 
    ,const int getmove_capability , const int* getLevelEXPneed , const string getname  = "小泽" );//输入名字的初始化

    //player property
    string getname() const ; 
    int getLevel() const ;
    int getcurrentEXP() const ; 
    int getAggress() const;  
    int getMAXHP() const;
    int getcurrentHP () const;  
    int getspeed () const ;
    int get_move_capability() const ;
    int getmoney() const;
    int getweaponaggress() const; 
    Vehicle* get_vehicle() const;
    Weapon* get_weapon() const;
    Bag get_bag() const;
    Position* get_cur_pos() const;
    Position *get_last_pos() const;
    PLAYER_STAGE get_cur_status() const;
    PLAYER_STAGE get_last_status() const;


    void changeHP(const int recovery); //恢复生命值
    void gainEXP(const int EXP);//获得经验值
    void levelUP(const int currentlevel);//升级
    void change_money(const int m);//money=money+m（可为负数）
    


    void set_pos(Position* p);
    void set_last_pos(Position *p);
    void set_status(const PLAYER_STAGE s);
    void set_last_status(const PLAYER_STAGE s);
    void setname(const string ) ;
    void setLevel(const int ) ;
    void setcurrentEXP (const int) ;
    void setAggress(const int) ;
    void setMAXHP (const int) ;
    void setcurrentHP (const int) ;
    void setspeed(const int) ;
    void setmove_capability(const int) ;
    void setweaponaggress(const int) ;
    void setmoney(const int) ;
    void setcurrent_Veh(Vehicle * );
    void setcurrent_Wep(Weapon * );
    void setbag(const Bag ) ;


    void show_state();//显示玩家属性状态

    //map
    void showmap() const ;

    //bag, item
    void pick(string item, PICK_MODE mode);//拾取背包中的某种物品

    void use(string item);//使用背包中的某种物品

    void drop(string item);//丢弃背包中的某种物品

    bool have(string item);//判断自己是否背包里有某种物品

    void equipWeapon(Weapon* a ); //装备武器 ，人物的武器攻击力值 = 武器攻击力

    void disequipWeapon () ; //卸下当前武器 ， 人物的武器攻击力值 = 0 ；
    
    //fight
    int  fight(Zombie *z); //打赢了返回2 逃跑返回1 被击败返回0

    void attack(Zombie* z);//用当前武器攻击丧尸

    void getdamage(const int damage);//被攻击

    int fight_many(vector <Zombie*> v_zome ) ; //打一群僵尸，返回值 : 打赢了返回2 逃跑返回1 被击败返回0

    int special_attack (Weapon* w,Zombie * z) ;

    //vehicle
    Vehicle* get_veh();

    void take_vehicle (Vehicle* a); //上车 ，速度、移动能力 被 交通工具 设置

    void get_off_vehicle();//下车 ，速度、移动能力 恢复成初始值

    bool move_to(Position* p);

    int get_HPcost(Position *p);
};



    
