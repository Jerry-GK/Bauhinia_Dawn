#pragma once
#include <string>
using namespace std;

class Weapon
{
protected:
    string name;
    int aggress;//攻击力
    int frequency;//攻击频率
public:
    virtual ~Weapon()=0;
};

class cloth_fork:public Weapon//衣叉
{

};

class Umbrella:public Weapon//雨伞
{

};