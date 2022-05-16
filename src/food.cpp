#include "food.h"

Food::Food(const string setname, const int setoccupancy)
{
    name = setname;
    occupancy = setoccupancy;
}

string Food::getname() const
{
    return name ;
}
int Food::getoccupancy() const 
{
    return occupancy ;
}
bool Food::isFood(string item)
{
    return global_set_foods.find(item)!=global_set_foods.end();
}
void Food::show() const
{
    cout << "ʳ����Ϣ��" << endl;
    cout << "���ƣ�" << name << endl;
    cout << "��ռ�ռ䣺" << occupancy << endl;
}
Food::~Food(){}

int Bread::geteffect() const 
{
    return effect ;
}

int Bread::getcost() const 
{
    return cost ;
}

void Bread::show() const
{
    Food::show();
    cout << "�۸�" << cost << endl;
    cout << "����������һ�����ò���������ʳ������ڳ��й���" << endl;
}

void Apple::show() const
{
    Food::show();
    cout << "�۸�" << cost << endl;
    cout << "������ƻ�����Բ���ά���أ���΢����һ��������������ˮ����ͷ�ҵ�" << endl;
}

void RedTube::show() const
{
    Food::show();
    cout << "�������Թ���װ����ֵ�Ѫ��ɫ�Լ���������Ѫһ��" << endl;
}

void GreenTube::show() const
{
    Food::show();
    cout << "�������Թ���װ������ɫ�Լ����������е�����" << endl;
}

int Apple::geteffect() const 
{
    return effect ;
}
int Apple::getcost() const 
{
    return cost;
}

Food* Food::new_food(string name)
{
    Food *ret = NULL;
    if(name==global_bread_name)
    {
        ret = new Bread;
    }
    else if(name==global_apple_name)
    {
        ret = new Apple;
    }
    else if(name==global_redtube_name)
    {
        ret = new RedTube();
    }
    else if(name==global_greentube_name)
    {
        ret = new GreenTube();
    }
    return ret;
}

Bread::Bread() : Food(global_bread_name, global_bread_occupancy) { effect = global_bread_effect; cost=global_bread_cost;};
Apple::Apple() : Food(global_apple_name, global_apple_occupancy) { effect = global_apple_effect; cost=global_apple_cost;};
RedTube::RedTube() : Food(global_redtube_name, global_redtube_occupancy){};
GreenTube::GreenTube() : Food(global_greentube_name, global_greentube_occupancy){};