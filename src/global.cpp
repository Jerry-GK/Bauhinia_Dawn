#include "global.h"
#include <string>
#include <set>
using namespace std;

//text-------------------------------------------------------------------------------------
const string info_help =
"\n主要游戏指令帮助：\n\
-------------条件指令（需要在特定场景、按提示使用）-------------\n\
begin: 进入游戏\n\
goto <地点英文名>: 前往某个地方  (注：主线地点不能随意去。 east building(东教，丧尸窟), library(图书馆，武器库)为特殊支线地点，任何时候均可去)\n\
pick <物品名>: 拾取/购买身边的某种物品\n\
take <交通工具英文名>: 乘坐身边的交通工具\n\n\
-------------通用指令（绝大多数情况皆可使用）-------------\n\
look: 查看周边情况\n\
check: 查看自身属性状态(通用)\n\
map: 查看地图(通用)\n\
bag: 查看当前背包内容(通用)\n\
use <物品英文名>: 使用背包中的物品(通用)\n\
drop <物品英文名>: 丢弃背包中的物品(通用)\n\
get off <交通工具英文名>: 离开当前的交通工具\n\
hint: 给出当前正确操作提示(通用)\n\
quit: 退出游戏(通用)\n\n\
-------------超级指令（仅供测试使用）-------------\n\
sudo goto <地点英文名>: 强制跳转至某个地点场景\n\
sudo pick <物品英文名>: 强制获得物品\n\
sudo take <交通工具英文名>: 强制乘坐交通工具\n\
sudo recover: 回复至最大体力\n\
";

const string info_end =
"\n游戏已经结束，请输入你的选择：\n\
roll back: 回到游戏结束前的上一个地点\n\
remake: 重新开始游戏\n\
quit: 退出游戏\n";

//data-------------------------------------------------------------------------------------

//角色：
const string global_player_name = "小泽";
const int global_initial_speed = 1 ; // 初始移动速度
const int global_initial_move_capability = 0 ;// 初始移动能力
const int global_initial_agress = 1;
const int global_initial_currentHP = 800 ;// 初始当前体力
const int initial_MAXHP = 1000 ;// 初始最大体力
const int global_initial_EXP[9] = {10,30,60,150,250,350,500,750,1000} ;// 升级所需经验
const int global_initial_money = 999999;
const int global_initial_Bag_occupancy = 999999;

//武器
const string global_fork_name = "fork";
const int global_fork_attack = 5;
const int global_fork_occupancy = 4;
const int global_fork_cost = 7;
const int global_fork_chance = 50 ;
const string global_knife_name = "knife";
const int global_knife_attack = 7;
const int global_knife_occupancy = 5;
const int global_knife_cost = 12;
const int global_knife_chance = 40 ;
const string global_umbrella_name = "umbrella";
const int global_umbrella_attack = 3;
const int global_umbrella_occupancy = 7;
const int global_umbrella_cost = 6;
const int global_umbrella_chance = 50 ;
const string global_gun_name = "gun";
const int global_gun_attack = 18;
const int global_gun_occupancy = 10;
const int global_gun_cost = 50;
const int global_gun_chance = 50 ;

//载具
const string global_bike_name = "bike";
const int global_bike_speed = 5;
const int global_bike_mc = 0;
const string global_ebike_name = "e-bike";
const int global_ebike_speed = 10;
const int global_ebike_mc = 0;
const string global_car_name = "car";
const int global_car_speed = 40;
const int global_car_mc = 0;
const string global_boat_name = "boat";
const int global_boat_speed = 12;
const int global_boat_mc = 1;

//食物
const string global_bread_name = "bread";
const int global_bread_occupancy = 2;
const int global_bread_effect = 5;
const int global_bread_cost = 4;
const string global_apple_name = "apple";
const int global_apple_occupancy = 1;
const int global_apple_effect = 2;
const int global_apple_cost = 2;
const string global_redtube_name = "red tube";
const int global_redtube_occupancy = 8;
const string global_greentube_name = "green tube";
const int global_greentube_occupancy = 8;

//丧尸
const string global_ordinary_name = "ordinary zombie";
const int global_ordinary_aggress = 7;
const int global_ordinary_HP = 30;
const int global_ordinary_def = 8;
const int global_ordinary_EXP = 80;
const int global_ordinary_money = 10;
const int global_ordinary_chance = 50 ;
const string global_roll_name = "roll zombie";
const int global_roll_aggress = 10;
const int global_roll_HP = 40;
const int global_roll_def = 18;
const int global_roll_EXP = 100;
const int global_roll_money = 15;
const int global_roll_chance = 15 ;
const string global_water_name = "water zombie";
const int global_water_aggress = 15;
const int global_water_HP = 50;
const int global_water_def = 12;
const int global_water_EXP = 150;
const int global_water_money = 30;
const int global_water_chance = 2;

//游戏
const int global_jump_damage = 40;
const double global_move_const = 0.04 ;
const string global_map_open_cmd = "start ../doc/zjg_map.png";

//物件字符串集合
set<string> global_set_weapons={global_fork_name,global_knife_name,global_umbrella_name,global_gun_name};
set<string> global_set_vehicles={global_bike_name,global_ebike_name,global_car_name,global_boat_name};
set<string> global_set_foods={global_bread_name,global_apple_name,global_redtube_name,global_greentube_name};