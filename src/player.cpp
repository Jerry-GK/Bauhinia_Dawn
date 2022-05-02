#include "player.h"
#include "init.h"

    Player::Player()
    {
        name = "xiaoze" ;
    }
    Player::Player(const int getcurrentHP ,const int getMAXHP, const int getspeed ,const int getmove_capability , const int* getLevelEXPneed , const string getname )
    {
        level = 1;
        currentEXP = 0 ;
        name = getname ;
        aggress =  getcurrentHP / 5 ;
        currentHP = getcurrentHP ;
        MAXHP = getMAXHP ;
        speed = getspeed ;
        move_capability = getmove_capability ;
        for (int i = 0 ; i < 9 ; i++)
        {
            needEXP[i] = getLevelEXPneed[i] ;
        }
        cur_veh = NULL ;
        pl_status = UNKNOWN ;
        pos = NULL ;
    }

    int Player::getAggress() const
    {
        return aggress ;
    }
    
    int Player::getMAXHP() const
    {
        return MAXHP ;
    }

    int Player::getcurrentHP () const
    {
        return currentHP ;
    }
    
    int Player::getspeed () const
    {
        return speed ;
    }

    int Player::getmove_capability() const
    {
        return move_capability ;
    }

    void Player::equipWeapon(const Weapon a )
    {
        weaponaggress = a.getattack() ;
        show_info("equipWeapon::something need to be cover");
    }

    void Player::disequipWeapon (const Weapon a)  //卸下武器 ， 人物的武器攻击力值 = 0 ；
    {
        weaponaggress = 0 ;
        show_info("disequipWeapon::something ");
    }
    void Player::get_in_transport (const Vehicle a) //上车 ，速度、移动能力 被 交通工具 设置
    {
        speed = a.getspeed() ;
        move_capability = a.getmove_capability() ;
        show_info("get_in_transport::something ");
    }
    void Player::get_out_transport(const Vehicle a )//下车 ，速度、移动能力 恢复成 $初始值$
    {
        speed = initial_speed ;
        move_capability = initial_move_capability ;
        show_info("get_out_transport::something ");
    }
    void Player::recoverHP(const int recovery)//恢复生命值
    {
        currentHP += recovery ;
        if (currentHP > MAXHP)
        {
            currentHP = MAXHP ;
        }
    }

    void Player::gainEXP(const int EXP) //获得经验值
    {
        currentEXP += EXP ;
        while(currentEXP >= needEXP[level-1])
        {
            levelUP(level) ;
        }
    }

    void Player::levelUP(int currentlevel)//升级 
    {
        currentEXP -= needEXP[level - 1] ;
        MAXHP += needEXP[level-1] / 10 ;
        recoverHP(0.1 * MAXHP) ;
        level ++ ;
        aggress += 1 ;
        //升级会使得最大体力值提升 ，同时恢复10%最大体力值的体力 ， 攻击力 + 1
        show_info("levelUP::something need to be writed");
    }

    //new:

    void Player::set_pos(Position* p)
    {
        this->pos=p;
        this->pl_status=p->get_status().front();
    }

    void Player::set_status(PLAYER_STAGE s)
    {
        this->pl_status=s;
    }


    Position* Player::get_pos()
    {
        return this->pos;
    }

    PLAYER_STAGE Player::get_status()
    {
        return pl_status;
    }

    void Player::pick(string item)
    {
        cout<<"拾取"<<item<<endl;
    }

    void Player::use(string item)
    {
        cout<<"使用"<<item<<endl;
    }

    void Player::show_state()//显示玩家属性状态
    {
        cout<<"玩家属性："<<endl;
        cout<<"姓名："<<name<<endl;
        cout<<"净攻击力："<<aggress<<endl;
        cout<<"体力（血量）："<<currentHP<<endl;
        cout<<"移动速度："<<speed<<endl;
        cout<<"所在地点："<<pos->get_name()<<endl;
    }
    Bag Player::get_bag()
    {
        return this->mybag;
    }
    


