#include "player.h"

Player::Player()
{
    name = "С��" ;
    level = 1;
    currentEXP = 0 ;
    aggress =  global_initial_agress;
    currentHP = global_initial_currentHP;
    MAXHP = initial_MAXHP;
    speed = global_initial_speed ;
    move_capability = global_initial_move_capability ;
    for (int i = 0 ; i < 9 ; i++)
    {
        needEXP[i] = global_initial_EXP[i] ;
    }
    cur_veh = NULL ;
    cur_wep=NULL;
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

int Player::get_move_capability() const
{
    return move_capability ;
}

Vehicle* Player::get_vehicle() const
{
    return cur_veh;    
}

Weapon* Player::get_weapon() const
{
    return cur_wep;
}

int Player::getweaponaggress() const
{
    return (cur_wep==NULL)?0:cur_wep->getattack();
}

void Player::equipWeapon(Weapon* a ) //װ������
{
    cur_wep =  a ;
    cout << "װ����������" << a->getname() << " ,����������Ϊ��" << a->getattack() << endl << endl; 
}

void Player::disequipWeapon () //װ������
{
    if(cur_wep==NULL)
    {
        cout<<"��ǰδװ������"<<endl;
        return;
    }
    cout << "ж����������" << cur_wep->getname() << " ,����������Ϊ��" << cur_wep->getattack() << endl << endl; 
    delete cur_wep ;
    cur_wep = NULL ;
}
void Player::take_vehicle (Vehicle* a) //�ϳ� ���ٶȡ��ƶ����� �� ��ͨ���� ����
{
    if(cur_veh!=NULL)
    {
        cout<<"���Ѿ���"<<cur_veh->getname()<<"���ˣ������뿪�ý�ͨ���ߡ�"<<endl;
        return;
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
    speed = global_initial_speed ;
    move_capability = global_initial_move_capability;
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
    string str_wep=(cur_wep==NULL)?"���ֿ�ȭ":cur_wep->getname();
    cout<<"������ԣ�"<<endl;
    cout<<"������"<<name<<endl;
    cout<<"�ȼ���"<<level<<endl;
    if (level != 10 ) {cout<<"���飺"<<currentEXP<<"  ������Ҫ��"<<needEXP[level-1] << endl;}
    else {cout << "���Ѿ��ﵽ����ߵȼ��� level 10 !" << endl;} //������� ����ʱ����Խ���bug ��Ҫ�ж��Ƿ�����
    cout<<"��������"<<aggress<<endl;
    cout<<"������������"<<this->getweaponaggress()<<endl;
    cout<<"��ǰ����/��������� "<<currentHP<<"/"<<MAXHP<<endl;
    cout<<"�ƶ��ٶȣ�"<<speed<<endl;
    cout<<"��ͨ���ߣ�"<<str_veh<<endl;
    cout<<"��ǰ������"<<str_wep<<endl;
    cout<<"��ǰλ�ã�"<<pos->get_name()<<endl;
}

Bag Player::get_bag() const
{
    return this->mybag;
}

Vehicle* Player::get_veh()
{
    return this->cur_veh;
}

void Player::pick(string item)
{
    if (isFood(item) )
    {
        Food a(item) ;
        if (mybag.add(item,a.getoccupancy() ) )
        {
            cout << "ʰȡ�� " << item << " ���ÿռ䣺" << mybag.getcurcapacity() << endl;
        }
        else
        {
            cout << "ʰȡʧ�� ��Ҫ�ռ䣺" << a.getoccupancy() 
            << "  ����ǰ���пռ䣺 " <<  mybag.getmaxcapacity() - mybag.getcurcapacity() ;
        }
    }
    else if (isWeapon (item))
    {
        Weapon a(item) ;
        if (mybag.add(item,a.getoccupancy() ) )
        {
            cout << "ʰȡ�� " << item << " ���ÿռ䣺" << mybag.getcurcapacity() << endl;
        }
        else 
        {
            cout << "ʰȡʧ�� ��Ҫ�ռ䣺" << a.getoccupancy() 
            << "  ����ǰ���пռ䣺 " <<  mybag.getmaxcapacity()- mybag.getcurcapacity() ;
        }
    }
    else
    {
        cout<<"��Чָ������ڸ�����Ʒ��"<<endl;
    }
}

void Player::use(string item)
{
    if ( isFood(item) )
    {
        if (mybag.find(item))
        {
            Food a(item) ;
            recoverHP(a.geteffect());
            mybag.det(item);
            cout << "ʹ���� " << item << " �ظ���������" << currentHP << endl;
            //ʹ��ʳ�� �ָ����� ʳ����ʧ
        }
        else
        {
            cout << "ʹ��ʧ�ܣ������ڲ����������Ʒ" << endl;
        }
    }
    else if (isWeapon (item ) )
    {
        if (mybag.find(item ))
        {
            disequipWeapon();
            Weapon* p =  new Weapon (item) ;
            equipWeapon(p);
        }
        else 
        {
            cout << "ʹ��ʧ�ܣ������ڲ����������Ʒ" << endl;
        }
    }
    else
    {
        cout<<"��Чָ������ڸ�����Ʒ��"<<endl;
    }
}

void Player::drop(string item)
{
    if (mybag.find(item))
    {
        if (isFood(item))
        {
            mybag.det(item);
        }
        else if (isWeapon(item))
        {
            if (cur_wep!=NULL && item == cur_wep->getname())
            {
                disequipWeapon();
            }
            mybag.det(item);
        }
        cout << "����/������ " << item << " ����ǰ����ʣ��������" <<mybag.getmaxcapacity() - mybag.getcurcapacity() << endl;
    }
    else
    {
        cout << "����/����ʧ�ܣ������ڲ����������Ʒ" << endl;
    }
}

bool Player::have(string item)
{
    return mybag.find(item);
}

//--------------------------------------to be implemented------------------------------------------------
void Player::move_to(Position* p)
{
    if(p==NULL)
    {
        cout<<"�����ڸõص㣡"<<endl;
        return;
    }
    this->set_pos(p);
    cout<<"������"<<p->get_name()<<endl;
    //���ݵ�ǰpos��Ŀ��p�ľ���(����xy����)���Լ��ٶȣ����������仯���߼�
}

int Player::fight(Zombie *z) //��Ӯ�˷���2 ���ܷ���1 �����ܷ���0
{
    int round = 1 ;
    string msg = "" ;
    cout << "\n��ʼս�� , ��Ҫ���ܵ��ǣ� " << z->getname() << endl; 
    z->show();
    cout << "�㵱ǰ״̬��" << endl; 
    cout << "HP/MAX = " << currentHP << "/" << MAXHP << "  ��ǰ����/���������� = " << aggress 
         << "/" << this->getweaponaggress() << endl;
    while (1)
    {
        cout << "\nRound" << round << endl << "���ѡ�������(fighting״ֻ̬�ܰ���ʾ����):" << endl 
             <<  "hit: ����ɥʬ\nuse <������>: ��������/ʹ��ʳ��(Ҳ�ᱻ������)\nescape: ����"  << endl << "\n<fighting> Please Enter: " ;
        getline(cin,msg);
        if (msg == "escape")
        {
            cout << "\n��о���Щ���Ծ� , �������ˣ�������ɽ��,����û����" << endl;
            return 1 ;
        }
        else if((msg.find("use")==0)&&msg.length()>=5)
        {
            this->use(msg.substr(4,msg.length()-4));
            msg.clear();
        }
        else if (msg == "hit")
        {
            attack(cur_wep,z) ;
            if (! z->getHP()) //����˽�ʬ
            {
                cout << "\n��˷�����,���ڻ�����ɥʬ��" << endl;
                this->gainEXP(z->getEXP());
                return 2;
            }
        }
        else
        {
            cout << endl << "ָ����Ч, �밴��ʾ������" << endl;
            msg.clear();
            continue;
        }

        z->attack(this);
        if ( !getcurrentHP() )//����ʬ���
        {
            cout << "\n���ź�,�����һ�У���ɥʬ������" << endl;
            return 0 ;
        }
        round++;
    }
}

void Player::getdamage(const int damage)//������
{
    currentHP -= damage ;
    if (currentHP < 0)
    {
        currentHP = 0 ;
    }
    cout << "���ܵ��� " << damage << "���˺� , ��ǰ����Ϊ�� " << currentHP << endl; 
}

void Player::attack(Weapon *a,Zombie *z)
{
    cout  << "�㷢���˹�����" << endl;
    //rand(20) + aggress > def can dealt damage to zombie by your weapon + 1;
    if ( rand()*20 + aggress > z->getdef())
    {
        z->getdamage (aggress*0.3+this->getweaponaggress() + 1) ;
    }
    else 
    {
        cout << "��δ�ܻ���ɥʬ�Ļ��� , ��Ҫ�������ԣ�" << endl;
    }

}