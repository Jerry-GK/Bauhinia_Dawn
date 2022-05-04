#pragma once
#include <string>
#include <set>
using namespace std;

static const string info_help=
"主要游戏指令帮助：\n\
-------------条件指令（需要在特定场景、按提示使用）-------------\n\n\
begin: 进入游戏\n\
goto <地点英文名>: 前往某个地方\n\
pick <物品名>: 拾取身边的某种物品\n\
take <交通工具英文名>: 乘坐身边的交通工具\n\
-------------通用指令（绝大多数情况皆可使用）-------------\n\n\
look: 查看周边情况\n\
check: 查看自身属性状态(通用)\n\
map: 查看地图(通用)\n\
bag: 查看当前背包内容(通用)\n\
use <物品英文名>: 使用背包中的物品(通用)\n\
drop <物品英文名>: 丢弃背包中的物品(通用)\n\
get off <交通工具英文名>: 离开当前的交通工具\n\
hint: 给出当前正确操作提示(通用)\n\
quit: 退出游戏(通用)\n\
-------------超级指令（仅供测试使用）-------------\n\n\
sudo goto <地点英文名>: 强制跳转至某个地点场景\n\
sudo pick <物品英文名>: 强制拾取物品\n\
sudo take <交通工具英文名>: 强制乘坐交通工具\n\
";

static const string info_welcome="欢迎来到《紫荆黎明》! (输入begin开始游戏，游戏过程中建议输入help查看指令说明，可输入hint查看提示)";
static const string info_invalid="输入的指令无效！(可输入help查看一般合法指令, 输入hint查看当前操作提示)";
static const string info_bye="谢谢体验！";
static const string info_wake_up="你是小泽，是浙大计算机系的一名普通大二学生，住在碧峰。昨晚是周六，室友都出去玩了，只留下你在宿舍。早上九点，你像\
往常一样模模糊糊地醒来，肚子很饿。窗外很暗，似乎又是沆州特有的阴天，你简单完成了洗漱，正准备去教学楼自习，突然听到教学楼外面\
有一声惨叫......";
static const string info_look_outside="你急忙向窗外望去，看到了震惊的一幕：窗外，一群丧尸正在疯狂撕咬一名学生，这名学生发出阵阵惨叫，渐渐的眼神失去了\
光泽，变得跟那群丧尸一样。你意识到，学校爆发了可怕的丧尸病毒，而你必须想办法逃出去。\n你可以选择：\nlook：查看周围情况\ngoto market: 前往教育超市观察";

static const string info_look_around="你背上自己的书包，想出去，但感觉需要做一些准备。你看了看四周，宿舍里似乎没什么吃的，也没什么武器可以用来防身，再仔细看看\
似乎只有宿舍的衣叉(fork)，或者是自己的伞，看起来勉强有些攻击力，要不要捡起呢？或者直接前往超市？";

static const string info_to_market="你从宿舍出来，躲着丧尸的视线，一路小跑来到了学园门前的启真教育超市";
static const string info_look_market="你在超市四周看了看，庆幸的是，售货员没有变成丧尸，你很想问她到底发生了什么。丧尸也似乎\
对超市里人类的食物不感兴趣，只是在外面不断巡逻。超市里有很多面包，你饿得不行。";

static const string info_saleman="售货员告诉你：可以去西教看看有没有幸存者。";
static const string info_to_gate="你离开超市，悄悄来到门口，可是还是被丧尸发现了，一只丧尸向你扑来，你似乎无处可逃了......";

static const string info_fight_suc="你用尽了全力，丧尸总算在你眼前倒下了，你也气喘吁吁，还好没有被咬到。你来到学园门前的路旁，发现四周空无一人，只有\
远处隐约有几只丧尸在漫无目的的走着。你想去西教，可不确定自己的体力能否支撑自己走到。";
static const string info_goto_west="你来到了西教，眼前的景象让你大吃一惊......";

enum GAME_STAGE//游戏当前状态的枚举类型
{
    PLAYING,//正常游戏状态
    PARTNER_DIE,//伙伴已经死去
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
    //market
    MARKET_SEARCH,
    MARKET_ASK,
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
    //wharf
    WHARF_DECIDE,
    //lake
    LAKE_ROW,
    LAKE_FIGHT,
    LAKE_SAVE,
    LAKE_SUC,
    //south gate
    SOUTH_END
};


//角色：
static const int global_initial_speed = 1 ; // 初始移动速度
static const int global_initial_move_capability = 0 ;// 初始移动能力
static const int global_initial_currentHP = 20 ;// 初始当前体力
static const int initial_MAXHP = 40 ;// 初始最大体力
static const int global_initial_EXP[9] = {10,30,60,150,250,350,500,750,1000} ;// 升级所需经验
static const int global_initial_Bag_occupancy = 999999;

//物件字符串集合
static set<string> global_set_weapons={"fork","umbrella","knife","gun"};
static set<string> global_set_vehicles={"bike","e-bike","car","boat"};
static set<string> global_set_foods={"bread","apple","red tube","green tube"};