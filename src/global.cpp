#include "global.h"
#include <string>
#include <set>
using namespace std;

//text-------------------------------------------------------------------------------------
const string info_help=
"��Ҫ��Ϸָ�������\n\
-------------����ָ���Ҫ���ض�����������ʾʹ�ã�-------------\n\
begin: ������Ϸ\n\
goto <�ص�Ӣ����>: ǰ��ĳ���ط�\n\
pick <��Ʒ��>: ʰȡ/������ߵ�ĳ����Ʒ\n\
take <��ͨ����Ӣ����>: ������ߵĽ�ͨ����\n\n\
-------------ͨ��ָ������������Կ�ʹ�ã�-------------\n\
look: �鿴�ܱ����\n\
check: �鿴��������״̬(ͨ��)\n\
map: �鿴��ͼ(ͨ��)\n\
bag: �鿴��ǰ��������(ͨ��)\n\
use <��ƷӢ����>: ʹ�ñ����е���Ʒ(ͨ��)\n\
drop <��ƷӢ����>: ���������е���Ʒ(ͨ��)\n\
get off <��ͨ����Ӣ����>: �뿪��ǰ�Ľ�ͨ����\n\
hint: ������ǰ��ȷ������ʾ(ͨ��)\n\
quit: �˳���Ϸ(ͨ��)\n\n\
-------------����ָ���������ʹ�ã�-------------\n\
sudo goto <�ص�Ӣ����>: ǿ����ת��ĳ���ص㳡��\n\
sudo pick <��ƷӢ����>: ǿ��ʰȡ��Ʒ\n\
sudo take <��ͨ����Ӣ����>: ǿ�Ƴ�����ͨ����\n\
";

//data-------------------------------------------------------------------------------------

//��ɫ��
const string global_player_name = "С��";
const int global_initial_speed = 1 ; // ��ʼ�ƶ��ٶ�
const int global_initial_move_capability = 0 ;// ��ʼ�ƶ�����
const int global_initial_agress = 20;
const int global_initial_currentHP = 80 ;// ��ʼ��ǰ����
const int initial_MAXHP = 100 ;// ��ʼ�������
const int global_initial_EXP[9] = {10,30,60,150,250,350,500,750,1000} ;// �������辭��
const int global_initial_money = 999999;
const int global_initial_Bag_occupancy = 999999;

//����
const string global_fork_name = "fork";
const int global_fork_attack = 5;
const int global_fork_occupancy = 4;
const int global_fork_cost = 7;
const string global_knife_name = "knife";
const int global_knife_attack = 7;
const int global_knife_occupancy = 5;
const int global_knife_cost = 12;
const string global_umbrella_name = "umbrella";
const int global_umbrella_attack = 3;
const int global_umbrella_occupancy = 7;
const int global_umbrella_cost = 6;
const string global_gun_name = "gun";
const int global_gun_attack = 18;
const int global_gun_occupancy = 10;
const int global_gun_cost = 85;

//�ؾ�
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

//ʳ��
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

//ɥʬ
const string global_ordinary_name = "ordinary zombie";
const int global_ordinary_aggress = 7;
const int global_ordinary_HP = 30;
const int global_ordinary_def = 2;
const int global_ordinary_EXP = 80;
const string global_roll_name = "roll zombie";
const int global_roll_aggress = 10;
const int global_roll_HP = 40;
const int global_roll_def = 5;
const int global_roll_EXP = 100;
const string global_water_name = "water zombie";
const int global_water_aggress = 15;
const int global_water_HP = 50;
const int global_water_def = 6;
const int global_water_EXP = 150;

//��Ϸ
const int global_jump_damage = 40;

//����ַ�������
set<string> global_set_weapons={global_fork_name,global_knife_name,global_umbrella_name,global_gun_name};
set<string> global_set_vehicles={global_bike_name,global_ebike_name,global_car_name,global_boat_name};
set<string> global_set_foods={global_bread_name,global_apple_name,global_redtube_name,global_greentube_name};