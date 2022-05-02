#pragma once
#include <string>
#include <iostream>
#include "weapon.h"
#include "bag.h"
#include "zombie.h"
#include "vehicle.h"
#include "ui.h"
#include "game_map.h"
#include "global.h"

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
    int needEXP[9]; //升级所需经验数组 

    int aggress;//攻击力
    int weaponaggress = 0 ;//武器攻击力 ，初始没有武器 = 0 

    int currentHP;//当前体力
    int MAXHP ; //最大体力上限

    int speed;//移动速度
    int move_capability;//移动能力（为0时只能在陆地行走，为1时可以两栖）

    Bag mybag;//背包
    Vehicle* cur_veh;//当前乘坐的交通工具
    PLAYER_STAGE pl_status;//玩家状态
    Position* pos;//玩家当前的位置
    
public:
    Player();
    Player(const int getcurrentHP ,const int getMAXHP, const int getspeed 
    ,const int getmove_capability , const int* getLevelEXPneed , const string getname  = "小泽" );//输入名字的初始化

    //player property
    int getAggress() const;  
    int getMAXHP() const;
    int getcurrentHP () const;  
    int getspeed () const ;
    int getmove_capability() const ;
    void recoverHP(const int recovery); //恢复生命值
    void gainEXP(const int EXP);//获得经验值
    void levelUP(const int currentlevel);//升级 
    Bag get_bag();
    void set_pos(Position* p);
    void set_status(PLAYER_STAGE s);
    Position* get_pos();
    PLAYER_STAGE get_status();
    void show_state();//显示玩家属性状态

    //bag, item
    void pick(string item);//拾取背包中的某种物品

    void use(string item);//使用背包中的某种物品

    void drop(string item);//丢弃背包中的某种物品

    void equipWeapon(Weapon* a ); //装备武器 ，人物的武器攻击力值 = 武器攻击力

    void disequipWeapon (Weapon* a) ; //卸下武器 ， 人物的武器攻击力值 = 0 ；
    
    //fight
    void fight(Zombie *z);

    void attack(Weapon* w, Zombie* z);//用某种武器攻击丧尸

    //vehicle
    Vehicle* get_veh();

    void take_vehicle (Vehicle* a); //上车 ，速度、移动能力 被 交通工具 设置

    void get_off_vehicle();//下车 ，速度、移动能力 恢复成初始值

    void move_to(Position* p);

};



    
