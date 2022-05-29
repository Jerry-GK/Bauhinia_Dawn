#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "player.h"


class Game
{
private:

    Player pl;
    GameMap game_map;
    GAME_STAGE stage;//游戏状态
    string input_box;//输入框输入的内容（未提交）
    string msg;//已提交的输入内容
    bool partner_alive;//同伴是否活着
    bool enemy_alive;//敌人（叶教授）是否活着

    static void code_str(string &str);

    static void decode_str(string &str);

public:
    void Init();//初始化
    bool Load(string filename);//读取存档
    inline void catchvalue (int beginpos , string get , stringstream & ss , int& answer) ;

    bool Save(string filename);//存档

    void read();  //读取一条信息，回车将回submit
    void submit();//提交输入信息：input_box->msg, 清空input_box, 调用process函数
    void process(string msg);//根据游戏、玩家状态以及输入信息，做出信息反馈（游戏最重要的逻辑部分）
 
    bool is_end() const;//判断游戏是否已经到了结局
    bool is_quit() const;//判断游戏是否已经退出
    void quit();//退出游戏
};