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

    void Player::disequipWeapon (const Weapon a)  //ж������ �� ���������������ֵ = 0 ��
    {
        weaponaggress = 0 ;
        show_info("disequipWeapon::something ");
    }
    void Player::get_in_transport (const Vehicle a) //�ϳ� ���ٶȡ��ƶ����� �� ��ͨ���� ����
    {
        speed = a.getspeed() ;
        move_capability = a.getmove_capability() ;
        show_info("get_in_transport::something ");
    }
    void Player::get_out_transport(const Vehicle a )//�³� ���ٶȡ��ƶ����� �ָ��� $��ʼֵ$
    {
        speed = initial_speed ;
        move_capability = initial_move_capability ;
        show_info("get_out_transport::something ");
    }
    void Player::recoverHP(const int recovery)//�ָ�����ֵ
    {
        currentHP += recovery ;
        if (currentHP > MAXHP)
        {
            currentHP = MAXHP ;
        }
    }

    void Player::gainEXP(const int EXP) //��þ���ֵ
    {
        currentEXP += EXP ;
        while(currentEXP >= needEXP[level-1])
        {
            levelUP(level) ;
        }
    }

    void Player::levelUP(int currentlevel)//���� 
    {
        currentEXP -= needEXP[level - 1] ;
        MAXHP += needEXP[level-1] / 10 ;
        recoverHP(0.1 * MAXHP) ;
        level ++ ;
        aggress += 1 ;
        //������ʹ���������ֵ���� ��ͬʱ�ָ�10%�������ֵ������ �� ������ + 1
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
        cout<<"ʰȡ"<<item<<endl;
    }

    void Player::use(string item)
    {
        cout<<"ʹ��"<<item<<endl;
    }

    void Player::show_state()//��ʾ�������״̬
    {
        cout<<"������ԣ�"<<endl;
        cout<<"������"<<name<<endl;
        cout<<"����������"<<aggress<<endl;
        cout<<"������Ѫ������"<<currentHP<<endl;
        cout<<"�ƶ��ٶȣ�"<<speed<<endl;
        cout<<"���ڵص㣺"<<pos->get_name()<<endl;
    }
    Bag Player::get_bag()
    {
        return this->mybag;
    }
    


