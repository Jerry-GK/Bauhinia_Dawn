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
    GAME_STAGE stage;//��Ϸ״̬
    string input_box;//�������������ݣ�δ�ύ��
    string msg;//���ύ����������
    
public:
    void Init();//��ʼ��

    void read();//��ȡһ����Ϣ���س�����submit
    void submit();//�ύ������Ϣ��input_box->msg, ���input_box, ����process����
    void process(string msg);//������Ϸ�����״̬�Լ�������Ϣ��������Ϣ��������Ϸ����Ҫ���߼����֣�
 
    bool is_end() const;//�ж���Ϸ�Ƿ��Ѿ����˽��
    void quit();//�˳���Ϸ
};