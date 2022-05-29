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
    GAME_STAGE stage;//��Ϸ״̬
    string input_box;//�������������ݣ�δ�ύ��
    string msg;//���ύ����������
    bool partner_alive;//ͬ���Ƿ����
    bool enemy_alive;//���ˣ�Ҷ���ڣ��Ƿ����

    static void code_str(string &str);

    static void decode_str(string &str);

public:
    void Init();//��ʼ��
    bool Load(string filename);//��ȡ�浵
    inline void catchvalue (int beginpos , string get , stringstream & ss , int& answer) ;

    bool Save(string filename);//�浵

    void read();  //��ȡһ����Ϣ���س�����submit
    void submit();//�ύ������Ϣ��input_box->msg, ���input_box, ����process����
    void process(string msg);//������Ϸ�����״̬�Լ�������Ϣ��������Ϣ��������Ϸ����Ҫ���߼����֣�
 
    bool is_end() const;//�ж���Ϸ�Ƿ��Ѿ����˽��
    bool is_quit() const;//�ж���Ϸ�Ƿ��Ѿ��˳�
    void quit();//�˳���Ϸ
};