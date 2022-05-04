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
    GAME_STAGE stage;//��Ϸ�׶�
    string input_box;//��ǰ���ֻ��������ı���δ�ύ��
    string msg;//��Ҹ��ύ���ı�
    
public:
    void Init();//��ʼ��

    void read();//����������ı�,������ɣ��س��������submit
    void submit();//�ӶԻ����ȡ���������ı���input_box->msg, clear input_box, call process��
    void process(string msg);//����stage������msg�ı�,��ؼ��Ĳ���
 
    bool is_end() const;//�����Ƿ������stage�Ƿ�ΪEND��
    void quit();//�˳���Ϸ

private:
    void show_prompt(string prompt) const;//������ʾ��Ϣ

};