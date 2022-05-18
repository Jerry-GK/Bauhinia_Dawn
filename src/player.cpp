#include "player.h"

Player::Player()
{
    name = global_player_name ;
    level = 1;
    currentEXP = 0 ;
    aggress =  global_initial_agress;
    currentHP = global_initial_currentHP;
    MAXHP = initial_MAXHP;
    speed = global_initial_speed ;
    move_capability = global_initial_move_capability ;
    money = global_initial_money;

    cur_veh = NULL ;
    cur_wep=NULL;
    pl_cur_status = UNKNOWN;
    pl_last_status = UNKNOWN;
    cur_pos=NULL;
    last_pos = NULL;
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

int Player::getmoney() const
{
    return money;
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
    if(a==NULL)
    {
        cout << "�����ڸý�ͨ���ߣ�" << endl;
        return;
    }
    if(cur_veh!=NULL)
    {
        cout<<"���Ѿ���"<<cur_veh->getname()<<"���ˣ������뿪�ý�ͨ���ߡ�"<<endl;
        return;
    }
    a->show();
    speed = a->getspeed() ;
    move_capability = a->getmove_capability() ;
    cur_veh = a;
    cout<<"����"<<cur_veh->getname()<<endl;
}
void Player::get_off_vehicle()//�³� ���ٶȡ��ƶ����� �ָ��� $��ʼֵ$
{
    if(cur_veh==NULL)
    {
        return;
    }
    speed = global_initial_speed ;
    move_capability = global_initial_move_capability;
    cout<<"�뿪"<<cur_veh->getname()<<endl;
    delete cur_veh;
    cur_veh=NULL;
}
void Player::changeHP(const int change)//�ָ�/��ʧ����ֵ
{
    currentHP += change ;
    if (currentHP > MAXHP)
    {
        currentHP = MAXHP ;
    }
    if(currentHP<0)
        currentHP = 0;
}

void Player::gainEXP(const int EXP) //��þ���ֵ
{
    currentEXP += EXP ;
    while(currentEXP >= global_initial_EXP[level-1])
    {
        levelUP(level) ;
    }
}

void Player::levelUP(int currentlevel)//���� 
{
    currentEXP -= global_initial_EXP[level - 1] ;
    MAXHP += global_initial_EXP[level-1] / 10 ;
    changeHP(0.1 * MAXHP) ;
    level ++ ;
    aggress += 1 ;
    //������ʹ���������ֵ���� ��ͬʱ�ָ�10%�������ֵ������ �� ������ + 1
    cout << "�����������˾���ֵ��������"<<level<<"����" << endl;
}

void Player::change_money(const int m)
{
    string str = m >= 0 ? "���" : "����";
    cout << "��"<<str<<"�ˣ�" << m << endl;
    money = money + m;
}
//new:

void Player::set_pos(Position* p)
{
    this->last_pos = this->cur_pos;
    this->cur_pos=p;
    this->pl_last_status = pl_cur_status;
    this->pl_cur_status=p->get_status().front();
}

void Player::set_status(PLAYER_STAGE s)
{
    this->pl_cur_status=s;
}


Position* Player::get_cur_pos()
{
    return this->cur_pos;
}

Position* Player::get_last_pos()
{
    return this->last_pos;
}

PLAYER_STAGE Player::get_cur_status()
{
    return pl_cur_status;
}

PLAYER_STAGE Player::get_last_status()
{
    return pl_last_status;
}

void Player::show_state()//��ʾ�������״̬
{
    string str_veh=(cur_veh==NULL)?"��":cur_veh->getname();
    string str_wep=(cur_wep==NULL)?"���ֿ�ȭ":cur_wep->getname();
    cout<<"������ԣ�"<<endl;
    cout<<"������"<<name<<endl;
    cout<<"�ȼ���"<<level<<endl;
    if (level != 10 ) {cout<<"���飺"<<currentEXP<<"  ������Ҫ��"<<global_initial_EXP[level-1] << endl;}
    else {cout << "���Ѿ��ﵽ����ߵȼ��� level 10 !" << endl;} //������� ����ʱ����Խ���bug ��Ҫ�ж��Ƿ�����
    cout<<"��ҹ�������"<<aggress<<endl;
    cout<<"������������"<<this->getweaponaggress()<<endl;
    cout<<"��ǰ����/��������� "<<currentHP<<"/"<<MAXHP<<endl;
    cout << "�ֽ���������" << money << endl;
    cout<<"�ƶ��ٶȣ�"<<speed<<endl;
    cout<<"��ͨ���ߣ�"<<str_veh<<endl;
    cout<<"��ǰ������"<<str_wep<<endl;
    cout<<"��ǰλ�ã�"<<cur_pos->get_name()<<endl;
}

void Player::showmap() const 
{
    cout << "��ǰλ���ǣ�" << cur_pos->get_name () << "(" << cur_pos->getX() <<  "," << cur_pos->getY() << ")" << endl;
    cout << "Loading map, please wait..." << endl;
    system(global_map_open_cmd.c_str());
}

Bag Player::get_bag() const
{
    return this->mybag;
}

Vehicle* Player::get_veh()
{
    return this->cur_veh;
}

void Player::pick(string item, PICK_MODE mode)//mode==0: pick ,mode==1: buy
{
    string pick_str;
    if(mode==PICK)
        pick_str = "ʰȡ";
    else if(mode==BUY)
        pick_str = "����";
    else if(mode==SUDO)
        pick_str = "ǿ�ƻ��";
    if (Food::isFood(item) )
    {
        Food *a = Food::new_food(item);
        a->show();

        if(mode==BUY)
        {
            if(a->getname()==global_bread_name)
            {
                Bread *b = dynamic_cast<Bread *> (a);
                if(getmoney()<b->getcost())
                {
                    cout << "����ʧ�ܣ����軨�ѣ�" << b->getcost() <<", ʣ�ࣤ"<<getmoney() << endl;
                    delete a;
                    return;
                }
            }
            else if(a->getname()==global_apple_name)
            {
                Apple *b = dynamic_cast<Apple *> (a);
                if(getmoney()<b->getcost())
                {
                    cout << "����ʧ�ܣ����軨�ѣ�" << b->getcost() <<", ʣ�ࣤ"<<getmoney() << endl;
                    delete a;
                    return;
                }
            }
        }
        if (mybag.add(item,a->getoccupancy() ) )
        {
            if(mode==BUY)
            {
                if(a->getname()==global_bread_name)
                {
                    Bread *b = dynamic_cast<Bread *> (a);
                    change_money(-b->getcost());
                    cout << "���ѣ�" << b->getcost() <<", ʣ�ࣤ"<<getmoney() << endl;
                }
                else if(a->getname()==global_apple_name)
                {
                    Apple *b = dynamic_cast<Apple *> (a);
                    change_money(-b->getcost());
                    cout << "���ѣ�" << b->getcost() <<", ʣ�ࣤ"<<getmoney() << endl;
                }
            }

            cout << pick_str <<"�� " << item << " ����ʣ��ռ䣺" << mybag.getmaxcapacity()-mybag.getcurcapacity() << endl;
        }
        else
        {
            cout <<pick_str << "ʧ�� ��Ҫ�ռ䣺" << a->getoccupancy() 
            << "  ����ǰ���пռ䣺 " <<  mybag.getmaxcapacity() - mybag.getcurcapacity() ;
        }
        delete a;
        return;
    }
    else if (Weapon::isWeapon (item))
    {
        Weapon *a = Weapon::new_wep(item);
        a->show();
        if(mode==BUY)
        {
            if(getmoney()<a->getcost())
            {
                cout << "����ʧ�ܣ����軨�ѣ�" << a->getcost() <<", ʣ�ࣤ"<<getmoney() << endl;
                delete a;
                return;
            }
        }
        if (mybag.add(item,a->getoccupancy()))
        {
            if(mode==BUY)
            {
                change_money(-a->getcost());
                cout << "���ѣ�" << a->getcost() <<", ʣ�ࣤ"<<getmoney() << endl;
            }
            cout << pick_str <<"�� " << item << " ����ʣ��ռ䣺" << mybag.getmaxcapacity()-mybag.getcurcapacity() << endl;
            cout << "ʹ��use <����Ӣ����> ����װ��������" << endl;
        }
        else 
        {
            cout << pick_str <<"ʧ��, ��Ҫ�ռ䣺" << a->getoccupancy() 
            << "  ����ǰ���пռ䣺 " <<  mybag.getmaxcapacity()- mybag.getcurcapacity() ;
        }
        delete a;
        return;
    }
    else
    {
        cout<<"��Чָ������ڸ�����Ʒ��"<<endl;
        return;
    }
}

void Player::use(string item)
{
    if(!mybag.find(item))
    {
        cout << "ʹ��ʧ�ܣ������ڲ����������Ʒ" << endl;
        return;
    }
    if ( Food::isFood(item) )
    {
        Food *a = Food::new_food(item);
        if(a->getname()==global_bread_name)
        {
            Bread *b = dynamic_cast<Bread *> (a);
            changeHP(b->geteffect());
            mybag.det(item);
            cout << "ʹ���� " << item << " �ظ���������" << currentHP << endl;
            //ʹ��ʳ�� �ָ����� ʳ����ʧ
        }
        else if(a->getname()==global_apple_name)
        {
            Apple *b = dynamic_cast<Apple *> (a);
            changeHP(b->geteffect());
            mybag.det(item);
            cout << "ʹ���� " << item << " �ظ���������" << currentHP << endl;
            //ʹ��ʳ�� �ָ����� ʳ����ʧ           
        }
        else 
        {
            cout << "��ǰ�޷�ʹ�ø���Ʒ��" << endl;
        }
        delete a;
    }
    else if (Weapon::isWeapon (item ) )
    {
        disequipWeapon();
        Weapon* p =  Weapon::new_wep (item) ;
        equipWeapon(p);
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
        if (Food::isFood(item))
        {
            mybag.det(item);
        }
        else if (Weapon::isWeapon(item))
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
bool Player::move_to(Position* p)
{
    if(p==NULL)
    {
        cout<<"�����ڸõص㣡"<<endl;
        return false; 
    }
    if(get_HPcost(p)!=0)
    {
        cout << "��ǰ״̬��ǰ��" << p->get_name() << "��Ҫ��������: " << get_HPcost(p) << "���Ƿ�ȷ��ǰ���������� \"yes\" ȷ�ϣ�" << endl;
        string ensure;
        getline(cin, ensure);
        if(ensure!="yes")
        {
            cout << "��û��ѡ��ǰ��" << p->get_name() << endl;
            return false;
        }
        if (getcurrentHP() < get_HPcost(p))
        {
            cout << "��ǰ�ؾ��£������޷�֧����ǰ���õص㣡" << endl;
            return false;
        }
    }

    //�����������ĺ���
    this->currentHP -= get_HPcost(p);
    cout<<"������"<<p->get_name()<<", ��������:"<<get_HPcost(p)<<", ��ǰ����:"<<getcurrentHP()<<endl;
    this->set_pos(p);
    return true;
}

int Player::get_HPcost(Position *p)//�õ���ǰλ��ȥp����������ֵ
{
    int distance = ( p->getX() - this->get_cur_pos()->getX() )*( p->getX() - this->get_cur_pos()->getX() )
    + ( p->getY() - this->get_cur_pos()->getY() ) * ( p->getY() - this->get_cur_pos()->getY() ) ;
    distance = sqrt(distance) ;
    return distance * global_move_const / speed ;
}

int Player::fight(Zombie *z) //��Ӯ�˷���2 ���ܷ���1 �����ܷ���0
{
    int round = 1 ;
    string msg = "" ;
    cout << "\n��ʼս�� , ��Ҫ���ܵ��ǣ� " << z->getname() << endl; 
    z->show();
    cout << "\n�㵱ǰ״̬��" << endl; 
    cout << "HP/MAX = " << currentHP << "/" << MAXHP << "  ��ǰ����/���������� = " << aggress 
         << "/" << this->getweaponaggress() << endl;
    while (1)
    {
        cout << "\nRound"<< round << "------------" << endl  << "���ѡ�������(fighting״ֻ̬�ܰ���ʾ����):" << endl 
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
            attack(z) ;
            if (! z->getHP()) //�����ɥʬ
            {
                cout << "\n��˷�����,���ڻ�����ɥʬ��" << endl;
                this->gainEXP(z->getEXP());
                this->change_money(z->getmoney());//���ܻ�ý�Ǯ
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
        if ( !getcurrentHP() )//��ɥʬ���
        {
            cout << "\n���ź�,�����һ�У���ɥʬ������" << endl;
            return 0 ;
        }
        round++;
    }
}

//��һȺɥʬ������ֵ : ��Ӯ�˷���2 ���ܷ���1 �����ܷ���0 ������bug ����-1��
int Player::fight_many(vector <Zombie*> v_zome )   
{
    int num_z = v_zome.size() ;
    if (!num_z) {return -1 ;}

    //before fight 
    int round = 1 ;
    string msg = "" ;
    cout << "\n��ʼս�� , ��Ҫ���ܵ��У� "  << endl; 
    for (int i = 0 ; i < v_zome.size() ; i++)
    {
        cout << i+1 << ".  " << v_zome[i]->getname() << " ������" << v_zome[i]->getaggress() <<
        " Ѫ����" << v_zome[i]->getHP() << " ������" << v_zome[i]->getdef() << endl;
    }
    cout << "\n�㵱ǰ״̬��" << endl; 
    cout << "HP/MAX = " << currentHP << "/" << MAXHP << "  ��ǰ����/���������� = " << aggress 
         << "/" << this->getweaponaggress() << endl;

    while (1)
    {
        cout << "\nRound" << round << "------------" << endl << "���ѡ�������(fighting״ֻ̬�ܰ���ʾ����):" << endl 
             <<  "hit: ����ɥʬ\nuse <������>: ��������/ʹ��ʳ��(Ҳ�ᱻ������)\nescape: ����"  << endl << "\n<fighting> Please Enter: " ;
        getline(cin,msg);
        if (msg == "escape")
        {
            if (num_z == 1 ) cout << "\n��о���Щ���Ծ� , �������ˣ�������ɽ��,����û����" << endl;
            else {cout << "\n�׻�˵˫ȭ�ѵ����� , �������ˣ�������ɽ��,����û����" << endl;} //Ϊ���պ�fight_many���Ը���fight
            return 1 ;
        }
        else if((msg.find("use")==0)&&msg.length()>=5)
        {
            this->use(msg.substr(4,msg.length()-4));
            msg.clear();
        }
        else if (msg == "hit" && v_zome.size() > 1)
        {
            cout << "\n��Ҫѡ�񹥻���ɥʬ��:(�������)"  << endl ;
            int i =  0;
            for (vector<Zombie*>::iterator p = v_zome.begin() ; p != v_zome.end() ; p++ )
            {
                cout << i+1 << ". " << (*p)->getname() << "��ǰ����ֵ��" << (*p)->getHP() << endl;
                i ++ ;
            } 
            cout << "\n<fighting> Please Enter: " ;
            getline(cin,msg); //�õ��ַ��� ת��������int

            int choose = atoi(msg.c_str());
            if(choose<=v_zome.size())
            {
                attack(v_zome[choose-1]) ;
                if ( (v_zome[choose-1]) ->getHP() == 0) //ɱ�������ɥʬ
                {
                    cout << "\n��˷�����,�����" << (v_zome[choose-1])->getname() << endl;
                    this->gainEXP((v_zome[choose-1])->getEXP());
                    this->change_money((v_zome[choose-1])->getmoney());
                    v_zome.erase(v_zome.begin()+choose-1);
                }
            }
            else //���������� , �������һ��
            {
                cout << "\n(��������) ����æ���ң�����˼��Ҫ�����ĸ�������㹥��������һ��" << endl;
                choose = rand() % v_zome.size() + 1 ;
                attack(v_zome[choose-1]) ;
                if ( (v_zome[choose-1]) ->getHP() == 0) //ɱ�������ɥʬ
                {
                    cout << "\n��˷�����,�����" << (v_zome[choose-1])->getname() << endl;
                    this->gainEXP((v_zome[choose-1])->getEXP());
                    this->change_money((v_zome[choose-1])->getmoney());
                    v_zome.erase(v_zome.begin()+choose-1);
                }
            }

            //�����׶ν����� �춨�Ƿ�ȫ������
            if (v_zome.empty()) //��������е�ɥʬ
            {
                cout << "���������ѣ����������е�ɥʬ������ɹ��������ˡ���" << endl;
                return 2 ;
            }

        }

        else if (msg == "hit" && v_zome.size() == 1)
        {
            attack(v_zome[0]) ;
            if (!v_zome[0]->getHP()) //�����ɥʬ
            {
                cout << "\n��˷�����,���ڻ��������һֻɥʬ��" << endl;
                this->gainEXP(v_zome[0]->getEXP());
                this->change_money(v_zome[0]->getmoney());
                return 2;
            }
        }
        
        else
        {
            cout << endl << "(ָ����Ч) �㲻֪������ʲô����ɥʬ���񲢲�Ը��ȴ�����" << endl;
            msg.clear();
            continue;
        }
        //��Ҳ�������
        //��ұ����л��ŵ�ɥʬ��������
        for (vector<Zombie*>::iterator p = v_zome.begin() ; p != v_zome.end() ; p++ )
        {
            (*p)->attack(this) ;
            if ( !getcurrentHP() )//��ɥʬ���
            {
                cout << "\n���ź�,�����һ�У���ɥʬ������" << endl;
                return 0 ;
            }
        } //������ɥʬ�Զ���delete ;
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

void Player::attack(Zombie *z)
{
    cout  << "�㷢���˹�����" << endl;
    int damage = rand()%30 + aggress + (cur_wep==NULL?0:cur_wep->getattack()) - z->getdef();
    if ( damage>0 ) 
    {
        if(cur_wep!=NULL)
            damage += cur_wep->wep_attack(z) - cur_wep->getattack();
        z->getdamage(damage);
        if(z->getname()==global_fire_name && (cur_wep==NULL || cur_wep->getname()!=global_umbrella_name))//�÷�ɡ����������ɥʬ������Ҳ�յ��˺�
        {
            cout << "�㹥���˻�ɥʬ������û����ˮ���Ե�ɡ������Ҳ�������ˣ�" << endl;
            getdamage(damage * global_fire_damage_return_rate);
        }
    }
    else 
    {
        cout << "�������������㣬δ�ܻ���ɥʬ�Ļ��� , ��Ҫ�������ԣ�" << endl;
    }

}