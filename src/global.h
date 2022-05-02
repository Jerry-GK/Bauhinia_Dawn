#pragma once
#include<string>
using namespace std;

static const string info_help=
"主要游戏指令帮助：\n\
look: 查看周边情况\n\
goto <地点英文名>: 前往某个地方\n\
check: 查看自身属性状态(通用)\n\
map: 查看地图(通用)\n\
bag: 查看当前背包内容(通用)\n\
use <物品英文名>: 使用背包中的物品(通用)\n\
hint: 给出当前正确操作提示(通用)\n\
quit: 退出游戏(通用)";

static const string info_invalid="输入的指令无效！(可输入-help查看通用合法指令)";
static const string info_welcome="欢迎来到《紫荆黎明》! (输入begin开始游戏)";
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


enum GAME_STAGE//游戏当前状态的枚举类型
{
    BEGIN,
    DIE,
    PASS,
    END
};

enum PLAYER_STAGE
{
    //dormitory
    UNKNOWN,
    DOR_WAKE_UP,
    DOR_TO_LOOK_OUTSIDE,
    DOR_TO_CHOOSE,
    MARKET_SEARCH,
    MARKET_ASK
};