#include "player.h"

Player::Player()
{
    name = "С��" ;
    level = 1;
    currentEXP = 0 ;
    aggress =  initial_currentHP;
    currentHP = initial_currentHP;
    MAXHP = initial_MAXHP;
    speed = initial_speed ;
    move_capability = initial_move_capability ;
    for (int i = 0 ; i < 9 ; i++)
    {
        needEXP[i] = initial_EXP[i] ;
    }
    cur_veh = NULL ;
    pl_status = UNKNOWN;
    pos=NULL;
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

void Player::equipWeapon(Weapon* a)
{
    weaponaggress = a->getattack() ;
    cout<<"װ������"<<a->getname();
}

void Player::disequipWeapon (Weapon* a)  //ж������ �� ���������������ֵ = 0 ��
{
    weaponaggress = 0 ;
    cout<<"����������"<<a->getname();
}
void Player::take_vehicle (Vehicle* a) //�ϳ� ���ٶȡ��ƶ����� �� ��ͨ���� ����
{
    if(cur_veh!=NULL)
    {
        cout<<"���Ѿ���"<<cur_veh->getname()<<"���ˣ������뿪�ý�ͨ���ߡ�"<<endl;
    }
    speed = a->getspeed() ;
    move_capability = a->getmove_capability() ;
    cur_veh = a;
    cout<<"����"<<cur_veh->getname()<<endl;
}
void Player::get_off_vehicle()//�³� ���ٶȡ��ƶ����� �ָ��� $��ʼֵ$
{
    if(cur_veh==NULL)
    {
        cout<<"������û�г�����ͨ���ߣ�"<<endl;
        return;
    }
    speed = initial_speed ;
    move_capability = initial_move_capability;
    cout<<"�뿪"<<cur_veh->getname()<<endl;
    delete cur_veh;
    cur_veh=NULL;
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

void Player::show_state()//��ʾ�������״̬
{
    string str_veh=(cur_veh==NULL)?"��":cur_veh->getname();
    cout<<"������ԣ�"<<endl;
    cout<<"������"<<name<<endl;
    cout<<"�ȼ���"<<level<<endl;
    if (level != 10 ) {cout<<"���飺"<<currentEXP<<"  ������Ҫ��"<<needEXP[level-1] << endl;}
    else {cout << "���Ѿ��ﵽ����ߵȼ��� level 10 !" << endl;} //������� ����ʱ����Խ���bug ��Ҫ�ж��Ƿ�����
    cout<<"��������"<<aggress<<endl;
    cout<<"������������"<<weaponaggress<<endl;
    cout<<"��ǰ����/��������� "<<currentHP<<"/"<<MAXHP<<endl;
    cout<<"�ƶ��ٶȣ�"<<speed<<endl;
    cout<<"��ͨ���ߣ�"<<str_veh<<endl;
    cout<<"��ǰλ�ã�"<<pos->get_name()<<endl;
}

Bag Player::get_bag()
{
    return this->mybag;
}

Vehicle* Player::get_veh()
{
    return this->cur_veh;
}


//--------------------------------------to be implemented------------------------------------------------
void Player::move_to(Position* p)
{
    this->set_pos(p);
    //���ݵ�ǰpos��Ŀ��p�ľ���(����xy����)���Լ��ٶȣ����������仯���߼�
}

void Player::pick(string item)
{
    cout<<"ʰȡ"<<item<<endl;
}

void Player::use(string item)
{
    cout<<"ʹ��"<<item<<endl;
    /*����item�ַ���
    ʳ������bread�������ģ��ָ�����
    ������������equipweapon������Ӧ����
    */
}

void Player::drop(string item)
{
    cout<<"����"<<item<<endl;
}

void fight(Zombie *z)
{
    //��ɥʬ��ս���߼�
}