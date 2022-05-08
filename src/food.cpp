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
    cout << "食物信息：" << endl;
    cout << "名称：" << name << endl;
    cout << "所占空间：" << occupancy << endl;
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
    cout << "价格：" << cost << endl;
    cout << "描述：这是一种能让补充体力的食物，可以在超市购买" << endl;
}

void Apple::show() const
{
    Food::show();
    cout << "价格：" << cost << endl;
    cout << "描述：苹果可以补充维生素，稍微补充一下体力，可以在水上码头找到" << endl;
}

void RedTube::show() const
{
    Food::show();
    cout << "描述：试管里装着奇怪的血红色试剂，就像鲜血一般" << endl;
}

void GreenTube::show() const
{
    Food::show();
    cout << "描述：试管里装着深绿色试剂，看起来有点眼熟" << endl;
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
        ret = new Bread(global_bread_effect, global_bread_cost);
    }
    else if(name==global_apple_name)
    {
        ret = new Apple(global_apple_effect, global_apple_cost);
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

Bread::Bread(int seteffect, int setcost) : Food(global_bread_name, global_bread_occupancy) { effect = seteffect; cost=setcost;};
Apple::Apple(int seteffect, int setcost) : Food(global_apple_name, global_apple_occupancy) { effect = seteffect; cost = setcost;};
RedTube::RedTube() : Food(global_redtube_name, global_redtube_occupancy){};
GreenTube::GreenTube() : Food(global_greentube_name, global_greentube_occupancy){};