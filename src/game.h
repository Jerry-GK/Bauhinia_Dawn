#pragma once
#include <iostream>
#include <vector>
#include "ui.h"
#include "game_map.h"
#include "player.h"
#include "vehicle.h"
#include "zombie.h"
#include "global.h"

class Game
{
private:
    Player pl;
    GameMap game_map;
    GAME_STAGE stage;//游戏阶段
    string input_box;//当前玩家只在输入的文本（未提交）
    string msg;//玩家刚提交的文本

public:
    void Init();//初始化

    void read();//让玩家输入文本,输入完成（回车）后调用submit
    void submit();//从对话框读取玩家输入的文本（input_box->msg, clear input_box, call process）
    void process(string msg);//根据stage，处理msg文本,最关键的部分
 
    bool is_end() const;//返回是否结束（stage是否为END）
    void quit();//退出游戏

private:
    void show_prompt(string prompt) const;//生成提示信息

};