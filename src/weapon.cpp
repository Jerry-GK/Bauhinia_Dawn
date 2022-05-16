#include "weapon.h"
#include "global.h"
using namespace std;
Weapon::Weapon(const string setname ,const int setattack,int setoccupancy, int setcost , int setchance)
{
    name = setname ;
    attack = setattack ;
    occupancy = setoccupancy;
    cost = setcost;
    special_attack_chance = setchance ;
}

Weapon::~Weapon(){}

void Weapon::attack_buff(int a)
{
    attack += a ;
    cout << "你的" << this->getname() << "的攻击力提升了" << a << "点"  << "，当前武器攻击力为" << attack << endl ;
}

string Weapon::getname() const
{
    return name ;
}
int Weapon::getattack() const 
{
    return attack ;
}
int Weapon::getoccupancy() const 
{
    return occupancy ;
}
int Weapon::getcost() const 
{
    return cost ;
}
int Weapon::getchance() const
{
    return special_attack_chance ;
}

void Weapon::show() const 
{
    cout << "武器信息：" << endl;
    cout << "名称：" << name << endl;
    cout << "攻击力：" << attack << endl;
    cout << "价格：" << cost << endl;
    cout << "所占空间：" << occupancy << endl;
}
void Fork::show() const
{
    Weapon::show();
}
void Knife::show() const
{
    Weapon::show();
    cout << "售货员的提示：这种刀具可以削弱丧尸的攻击能力" << endl;
}
void Umbrella::show() const
{
    Weapon::show();
    cout << "特性：这是一种水属性武器，可以对火属性丧尸造成额外效果（未实现）" << endl;
}
void Gun::show() const
{
    Weapon::show();
    cout << "特性：这是一种火属性武器，有几率爆头，可以对水丧尸造成额外伤害效果" << endl;
}

int Weapon::wep_attack(Zombie* z)
{
    int num = rand() % 100 ;
    if (num > getchance())  
    {
        //special case
        if(this->name==global_gun_name && z->getname()==global_water_name)
        {
            cout << "你的火属性枪对水丧尸造成了双倍伤害！" << endl;
            return 2*getattack();
        }
        return getattack();
    }
    else
        return wep_special_attack(z) ;
} 

int Fork::wep_special_attack(Zombie* z) 
{
    cout << "你瞅准弱点，用叉子对丧尸发起了更精准的攻击！" << endl;
    return getattack() * (1.0 + (rand() % 10) / 10.0);
}

int Knife::wep_special_attack(Zombie* z) 
{
    cout << "说时迟那时快，你迅猛地用小刀轻易地砍下了丧尸一部分的身躯" << endl;
    z->attack_weaken(z->getaggress() * 0.5 ) ;
    return getattack() + rand() % 8;
}

int Umbrella::wep_special_attack(Zombie* z) 
{
    cout << "你用伞狠狠地戳了丧尸的头部，你感觉到你的攻击逐渐变得娴熟了!" << endl;
    attack_buff(1) ;
    return getattack() + rand() % 5;
}

int Gun::wep_special_attack(Zombie* z) 
{
    cout << "你仔细地瞄准了"<<z->getname()<<"丧尸的头部……屏气…………开枪, 爆头！" << endl;
    return z->getHP();
}

bool Weapon::isWeapon(string item)
{
    return global_set_weapons.find(item)!=global_set_weapons.end();
}

Weapon* Weapon::new_wep(string name)
{
    Weapon *ret = NULL;
    if(name==global_fork_name)
    {
        ret = new Fork();
    }
    else if(name==global_knife_name)
    {
        ret = new Knife();
    }
    else if(name==global_umbrella_name)
    {
        ret = new Umbrella();
    }
    else if(name==global_gun_name)
    {
        ret = new Gun();
    }
    return ret;
}

Fork::Fork() : Weapon(global_fork_name, global_fork_attack, global_fork_occupancy, global_fork_cost , global_fork_chance){};

Knife::Knife() : Weapon(global_knife_name,global_knife_attack,global_knife_occupancy, global_knife_cost ,global_knife_chance){};

Umbrella::Umbrella() : Weapon(global_umbrella_name,global_umbrella_attack,global_umbrella_occupancy, global_umbrella_cost , global_umbrella_chance){};

Gun::Gun() : Weapon(global_gun_name,global_gun_attack,global_gun_occupancy, global_gun_cost, global_gun_chance){};
