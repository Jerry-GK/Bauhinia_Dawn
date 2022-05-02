#pragma once
#include <string>
#include <iostream>
#include "weapon.h"
#include "bag.h"
#include "zombie.h"
#include "vehicle.h"
#include "ui.h"
#include "game_map.h"
#include "global.h"

using namespace std;

class Weapon;
class Vehicle;
class Zombie;
class Player
{
private:
    string name;
    int level ; //�ȼ�����ʼ��1�����level��10
    int currentEXP ; //����
    int needEXP[9]; //�������辭������ 

    int aggress;//������
    int weaponaggress = 0 ;//���������� ����ʼû������ = 0 

    int currentHP;//��ǰ����
    int MAXHP ; //�����������

    int speed;//�ƶ��ٶ�
    int move_capability;//�ƶ�������Ϊ0ʱֻ����½�����ߣ�Ϊ1ʱ�������ܣ�

    Bag mybag;//����
    Vehicle* cur_veh;//��ǰ�����Ľ�ͨ����
    PLAYER_STAGE pl_status;//���״̬
    Position* pos;//��ҵ�ǰ��λ��
    
public:
    Player();
    Player(const int getcurrentHP ,const int getMAXHP, const int getspeed 
    ,const int getmove_capability , const int* getLevelEXPneed , const string getname  = "С��" );//�������ֵĳ�ʼ��

    //player property
    int getAggress() const;  
    int getMAXHP() const;
    int getcurrentHP () const;  
    int getspeed () const ;
    int getmove_capability() const ;
    void recoverHP(const int recovery); //�ָ�����ֵ
    void gainEXP(const int EXP);//��þ���ֵ
    void levelUP(const int currentlevel);//���� 
    Bag get_bag();
    void set_pos(Position* p);
    void set_status(PLAYER_STAGE s);
    Position* get_pos();
    PLAYER_STAGE get_status();
    void show_state();//��ʾ�������״̬

    //bag, item
    void pick(string item);//ʰȡ�����е�ĳ����Ʒ

    void use(string item);//ʹ�ñ����е�ĳ����Ʒ

    void drop(string item);//���������е�ĳ����Ʒ

    void equipWeapon(Weapon* a ); //װ������ �����������������ֵ = ����������

    void disequipWeapon (Weapon* a) ; //ж������ �� ���������������ֵ = 0 ��
    
    //fight
    void fight(Zombie *z);

    void attack(Weapon* w, Zombie* z);//��ĳ����������ɥʬ

    //vehicle
    Vehicle* get_veh();

    void take_vehicle (Vehicle* a); //�ϳ� ���ٶȡ��ƶ����� �� ��ͨ���� ����

    void get_off_vehicle();//�³� ���ٶȡ��ƶ����� �ָ��ɳ�ʼֵ

    void move_to(Position* p);

};



    
