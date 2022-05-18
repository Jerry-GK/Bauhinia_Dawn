#include "weapon.h"
#include "global.h"
using namespace std;
Weapon::Weapon(const string setname ,const int setattack,const int setoccupancy,const int setcost ,const int setchance , const string setpro = "")
{
    name = setname ;
    attack = setattack ;
    occupancy = setoccupancy;
    cost = setcost;
    special_attack_chance = setchance ;
    property = setpro ;
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
    else if(name==global_bloodsickle_name)
    {
        ret = new BloodSickle();
    }
    return ret;
}
void Weapon::show() const 
{
    cout << "武器信息：" << endl;
    cout << "名称：" << name << endl;
    cout << "攻击力：" << attack << endl;
    cout << "价格：" << cost << endl;
    cout << "所占空间：" << occupancy << endl;
    cout << "属性: " ; if (property == "") {cout << "无属性" << endl;} else {cout << property << endl;}
}
bool Weapon::isWeapon(string item)
{
    return global_set_weapons.find(item)!=global_set_weapons.end();
}

int Weapon::wep_attack(Zombie* z)
{
    //counter relation
    if (property == "water" )
    {
        if (z->getpro() == "fire")
        {
            return wep_special_attack(z);
        } // water to fire
        else if (z->getpro() == "water")
        {
            cout << "你的水属性武器对水属性丧尸的攻击收效甚微, 只造成了一小部分伤害！" << endl;
            return 0.3*getattack();
        } //water to water
    }
    else if (property == "fire")
    {
        if (z->getpro() == "water")
        {
            return wep_special_attack(z);
        } //fire to water
        else if (z->getpro() == "fire")
        {
            cout << "你的火属性武器对火属性丧尸的攻击收效甚微，只造成了一小部分伤害！" << endl;
            return 0.3*getattack();
        } //fire to fire
    }

    //no counter relation
    int num = rand() % 100 ;
    if (num > getchance())  
    {
        return getattack() ;
    }
    else
        return wep_special_attack(z) ;
} 



// fork ---------------------------------------
Fork::Fork() : Weapon(global_fork_name, global_fork_attack, global_fork_occupancy, global_fork_cost , global_fork_chance ){};
void Fork::show() const
{
    Weapon::show();
    cout << "特性：<精准>这是一种较弱的武器，但是容易命中敌人要害" << endl;
}
int Fork::wep_special_attack(Zombie* z) 
{
    cout << "你瞅准弱点，用叉子对丧尸发起了更精准的攻击！" << endl;
    return getattack() * (1.0 + (rand() % 10) / 10.0);
}

// knife  ---------------------------------------
Knife::Knife() : Weapon(global_knife_name,global_knife_attack,global_knife_occupancy, global_knife_cost ,global_knife_chance){};
void Knife::show() const
{
    Weapon::show();
    cout << "特性：<致残>售货员的提示：这种刀具可以通过割伤丧尸，降低其攻击能力" << endl;
}
int Knife::wep_special_attack(Zombie* z) 
{
    cout << "说时迟那时快，你迅猛地用小刀轻易地砍下了丧尸一部分的身躯" << endl;
    z->attack_weaken(z->getaggress() * 0.5 ) ;
    return getattack() + rand() % 8;
}

// umbrella ---------------------------------------
Umbrella::Umbrella() : Weapon(global_umbrella_name,global_umbrella_attack,global_umbrella_occupancy, global_umbrella_cost , global_umbrella_chance ,global_umbrella_property){};
void Umbrella::show() const
{
    Weapon::show();
    cout << "特性：<甘露>这是一种水属性武器，可以对火属性丧尸造成强大的额外效果，对水丧尸伤害很小" << endl;
}
int Umbrella::wep_special_attack(Zombie* z) 
{
    if(z->getpro()==global_fire_property)
    {
        cout << "水属性的伞对火属性丧尸造成了特殊效果，它似乎被扑灭了不少，瞬间损失了一半多的生命值！" << endl;
        return z->getHP() / 2 + global_fire_HP / 10;
    }
    cout << "你用伞狠狠地戳了丧尸的头部，你感觉到你的攻击逐渐变得娴熟了!" << endl;
    attack_buff(1) ;
    return getattack() + rand() % 5;
}

// gun  ---------------------------------------
Gun::Gun() : Weapon(global_gun_name,global_gun_attack,global_gun_occupancy, global_gun_cost, global_gun_chance ,global_gun_property){};
void Gun::show() const
{
    Weapon::show();
    cout << "特性：<爆头>这是一种火属性武器，有几率爆头绝杀。可以对水丧尸造成额外伤害效果，对火丧尸威胁不大" << endl;
}
int Gun::wep_special_attack(Zombie* z) 
{
    if(z->getpro()==global_water_property)
    {
        cout << "虽然对水丧尸爆头似乎不起作用，但火药的威力险些让水丧尸蒸发掉，造成了双倍伤害，它看起来大受创伤！" << endl;
        return 2 * getattack();
    }
    cout << "你仔细地瞄准了"<<z->getname()<<"丧尸的头部……屏气…………开枪, 爆头！" << endl;
    return z->getHP();
}

//bloodsickle ---------------------------------
BloodSickle::BloodSickle() : Weapon(global_bloodsickle_name,global_bloodsickle_attack,global_bloodsickle_occupancy, global_bloodsickle_cost, global_bloodsickle_chance ){};
void BloodSickle::show() const
{
    Weapon::show();
    cout << "特性：<狂热>血镰会在连续攻击的状态中陷入狂热状态，每次攻击后有机会吸取对方的血液转化为攻击力, 更换武器后失效..." << endl;
}
int BloodSickle::wep_special_attack(Zombie* z) 
{
    int damage =  getattack() * 1.5  + rand() % 5;
    attack_buff(damage * 0.35) ;
    cout << "血镰越来越狂热，吸取了丧尸的血液，变得更加强大了。血镰攻击力增至"<< getattack()<< endl;
    return damage ;
}



