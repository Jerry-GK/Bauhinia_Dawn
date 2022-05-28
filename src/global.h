#pragma once
#include <set>
#include <string>
using namespace std;

extern const string info_help;
extern const string info_end;
extern const string info_welcome;

//角色：
extern const string global_player_name;
extern const int global_initial_speed;
extern const int global_initial_move_capability;
extern const int global_initial_agress;
extern const int global_initial_currentHP;
extern const int initial_MAXHP;
extern const int global_initial_EXP[9];
extern const int global_initial_money;
extern const int global_initial_Bag_occupancy;

//武器
extern const string global_fork_name;
extern const int global_fork_attack;
extern const int global_fork_occupancy;
extern const int global_fork_cost;
extern const int global_fork_chance;

extern const string global_knife_name;
extern const int global_knife_attack;
extern const int global_knife_occupancy;
extern const int global_knife_cost;
extern const int global_knife_chance;

extern const string global_umbrella_name;
extern const int global_umbrella_attack;
extern const int global_umbrella_occupancy;
extern const int global_umbrella_cost;
extern const int global_umbrella_chance;
extern const string global_umbrella_property;

extern const string global_gun_name;
extern const int global_gun_attack;
extern const int global_gun_occupancy;
extern const int global_gun_cost;
extern const int global_gun_chance;
extern const string global_gun_property;

extern const string global_bloodsickle_name;
extern const int global_bloodsickle_attack;
extern const int global_bloodsickle_occupancy;
extern const int global_bloodsickle_cost;
extern const int global_bloodsickle_chance;
extern const string global_bloodsickle_property;

//载具
extern const string global_bike_name;
extern const int global_bike_speed;
extern const int global_bike_mc;
extern const string global_ebike_name;
extern const int global_ebike_speed;
extern const int global_ebike_mc;
extern const string global_car_name;
extern const int global_car_speed;
extern const int global_car_mc;
extern const string global_boat_name;
extern const int global_boat_speed;
extern const int global_boat_mc;

//食物
extern const string global_bread_name;
extern const int global_bread_occupancy;
extern const int global_bread_effect;
extern const int global_bread_cost;
extern const string global_apple_name;
extern const int global_apple_occupancy;
extern const int global_apple_effect;
extern const int global_apple_cost;
extern const string global_redtube_name;
extern const int global_redtube_occupancy;
extern const string global_greentube_name;
extern const int global_greentube_occupancy;

//丧尸
extern const string global_ordinary_name;
extern const int global_ordinary_aggress;
extern const int global_ordinary_HP;
extern const int global_ordinary_def;
extern const int global_ordinary_EXP;
extern const int global_ordinary_money;
extern const int global_ordinary_chance;
extern const string global_roll_name;
extern const int global_roll_aggress;
extern const int global_roll_HP;
extern const int global_roll_def;
extern const int global_roll_EXP;
extern const int global_roll_money;
extern const int global_roll_chance;
extern const string global_water_name;
extern const int global_water_aggress;
extern const int global_water_HP;
extern const int global_water_def;
extern const int global_water_EXP;
extern const int global_water_money;
extern const int global_water_chance;
extern const string global_water_property;
extern const string global_fire_name;
extern const int global_fire_aggress;
extern const int global_fire_HP;
extern const int global_fire_def;
extern const int global_fire_EXP;
extern const int global_fire_money;
extern const int global_fire_chance;
extern const string global_fire_property;
extern const double global_fire_damage_return_rate;

//游戏
extern const int global_jump_damage;
extern const double global_move_const;
extern const string global_map_open_cmd;
extern const string global_save_file_name;
extern const double global_stop_time;

//物件字符串集合
extern set<string> global_set_weapons;
extern set<string> global_set_vehicles;
extern set<string> global_set_foods;
enum GAME_STAGE//游戏当前状态的枚举类型
{
    NOT_BEGIN,//游戏尚未开始
    PLAYING,//正常游戏状态
    DIE,//结局：死去
    ALONE_SUC,//结局：一人独自成功逃生
    SUC,//结局：成功带伙伴一起逃生
    QUIT//结局：非正常退出
};

enum PLAYER_STAGE
{
    UNKNOWN,
    //dormitory
    DOR_TO_LOOK_OUTSIDE,
    DOR_TO_CHOOSE,
    //shop
    SHOP_SEARCH,
    SHOP_ASK,
    //dor gate
    GATE_FIGHT,
    GATE_AFTER_FIGHT,
    //west building
    WEST_INTO_BUILDING,
    WEST_MEET,
    WEST_FIGHT,
    WEST_CHECK,
    //bio lab
    BIO_INTO_BUILDING,
    BIO_MEET,
    BIO_LEAVE,
    //roof
    ROOF_HALL,
    ROOF_TOP,
    ROOF_LEAVE,
    ROOF_SUC,
    ROOF_TO_WHARF,
    //wharf
    WHARF_DECIDE,
    //lake
    LAKE_ROW,
    LAKE_FIGHT,
    LAKE_SAVE,
    LAKE_SUC,
    //south gate
    SOUTH_END,
    //east building
    EAST_BUILDING,
    //library
    LIBRARY
};

enum PICK_MODE //普通捡起,购买,或sudo拾取
{
    PICK,
    BUY,
    SUDO
};