#pragma once
#include <string>
#include <iostream>
#include "weapon.h"
#include "bag.h"
#include "zombie.h"
#include "vehicle.h"
#include "game_map.h"
#include "global.h"
#include "food.h"
#include <sstream>
#include <stdlib.h> 
#include <math.h>

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
    int aggress;//������

    int currentHP;//��ǰ����
    int MAXHP ; //�����������

    int speed;//�ƶ��ٶ�
    int move_capability;//�ƶ�������Ϊ0ʱֻ����½�����ߣ�Ϊ1ʱ�������ܣ�

    int money;//����Ǯ������

    Bag mybag;//����
    Vehicle* cur_veh;//��ǰ�����Ľ�ͨ���ߣ�NULL��ʾ˫�ţ�
    Weapon* cur_wep;//��ǰ��������NULL��ʾ˫�֣�
    PLAYER_STAGE pl_cur_status;//���״̬
    PLAYER_STAGE pl_last_status;//�����һ��״̬
    Position* cur_pos;//��ҵ�ǰ��λ��
    Position *last_pos;//�����һ��λ�ã���ʼΪNULL��

public:
    Player();
    Player(const int getcurrentHP ,const int getMAXHP, const int getspeed 
    ,const int getmove_capability , const int* getLevelEXPneed , const string getname  = "С��" );//�������ֵĳ�ʼ��

    //player property
    string getname() const ; 
    int getLevel() const ;
    int getcurrentEXP() const ; 
    int getAggress() const;  
    int getMAXHP() const;
    int getcurrentHP () const;  
    int getspeed () const ;
    int get_move_capability() const ;
    int getmoney() const;
    int getweaponaggress() const; 
    Vehicle* get_vehicle() const;
    Weapon* get_weapon() const;
    Bag get_bag() const;
    Position* get_cur_pos() const;
    Position *get_last_pos() const;
    PLAYER_STAGE get_cur_status() const;
    PLAYER_STAGE get_last_status() const;


    void changeHP(const int recovery); //�ָ�����ֵ
    void gainEXP(const int EXP);//��þ���ֵ
    void levelUP(const int currentlevel);//����
    void change_money(const int m);//money=money+m����Ϊ������
    


    void set_pos(Position* p);
    void set_last_pos(Position *p);
    void set_status(const PLAYER_STAGE s);
    void set_last_status(const PLAYER_STAGE s);
    void setname(const string ) ;
    void setLevel(const int ) ;
    void setcurrentEXP (const int) ;
    void setAggress(const int) ;
    void setMAXHP (const int) ;
    void setcurrentHP (const int) ;
    void setspeed(const int) ;
    void setmove_capability(const int) ;
    void setweaponaggress(const int) ;
    void setmoney(const int) ;
    void setcurrent_Veh(Vehicle * );
    void setcurrent_Wep(Weapon * );
    void setbag(const Bag ) ;


    void show_state();//��ʾ�������״̬

    //map
    void showmap() const ;

    //bag, item
    void pick(string item, PICK_MODE mode);//ʰȡ�����е�ĳ����Ʒ

    void use(string item);//ʹ�ñ����е�ĳ����Ʒ

    void drop(string item);//���������е�ĳ����Ʒ

    bool have(string item);//�ж��Լ��Ƿ񱳰�����ĳ����Ʒ

    void equipWeapon(Weapon* a ); //װ������ �����������������ֵ = ����������

    void disequipWeapon () ; //ж�µ�ǰ���� �� ���������������ֵ = 0 ��
    
    //fight
    int  fight(Zombie *z); //��Ӯ�˷���2 ���ܷ���1 �����ܷ���0

    void attack(Zombie* z);//�õ�ǰ��������ɥʬ

    void getdamage(const int damage);//������

    int fight_many(vector <Zombie*> v_zome ) ; //��һȺ��ʬ������ֵ : ��Ӯ�˷���2 ���ܷ���1 �����ܷ���0

    int special_attack (Weapon* w,Zombie * z) ;

    //vehicle
    Vehicle* get_veh();

    void take_vehicle (Vehicle* a); //�ϳ� ���ٶȡ��ƶ����� �� ��ͨ���� ����

    void get_off_vehicle();//�³� ���ٶȡ��ƶ����� �ָ��ɳ�ʼֵ

    bool move_to(Position* p);

    int get_HPcost(Position *p);
};



    
