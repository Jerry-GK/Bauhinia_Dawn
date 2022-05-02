#pragma once
#include<string>
#include <iostream>
#include "game_map.h"
#include "weapon.h"
#include "bag.h"
#include "zombie.h"
#include "vehicle.h"
#include "global.h"

using namespace std;

class Zombie;

class Player
{
protected:
    string name;
    int aggress;//攻击力
    int  HP;//血量/体力
    int speed;//移动速度
    Bag mybag;//背包
    Vehicle* cur_veh;//当前乘坐的交通工具
    PLAYER_STAGE pl_status;//玩家状态
    Position* pos;//玩家当前的位置
    
public:
    Player();
    void pick(string item);//拾取背包中的某种物品
    void use(string item);//使用背包中的某种物品
    void set_pos(Position* p);
    void set_status(PLAYER_STAGE s);
    void fight(Zombie *z);
    void attack(Weapon* w, Zombie* z);//用某种武器攻击丧尸
    Position* get_pos();
    PLAYER_STAGE get_status();

    void show_state();//显示玩家属性状态
    Bag get_bag();
};