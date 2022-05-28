#include "game.h"
using namespace std ;

void Game::Init()
{
    cout<<info_welcome;

    this->stage=NOT_BEGIN;
    //���ߵص��ʼ��
    Position p;
    input_box.clear();
    msg.clear();
    partner_alive = true;
    enemy_alive = true;

    p.set("dormitory",20,120);//����
    p.add_status(DOR_TO_LOOK_OUTSIDE);
    p.add_status(DOR_TO_CHOOSE);
    game_map.add_pos(p);
    
    p.set("shop",22,115);//����
    p.add_status(SHOP_SEARCH);
    p.add_status(SHOP_ASK);
    game_map.add_pos(p);

    p.set("dor gate",15,115);//�����ſ�
    p.add_status(GATE_FIGHT);
    p.add_status(GATE_AFTER_FIGHT);
    game_map.add_pos(p);

    p.set("west building",20,50);//����
    p.add_status(WEST_INTO_BUILDING);
    p.add_status(WEST_MEET);
    p.add_status(WEST_FIGHT);
    p.add_status(WEST_CHECK);
    game_map.add_pos(p);

    p.set("bio lab",70,10);//����ʵ����
    p.add_status(BIO_INTO_BUILDING);
    p.add_status(BIO_MEET);
    p.add_status(BIO_LEAVE);
    game_map.add_pos(p);

    p.set("roof",25,65);//ԭ��Ժ¥��
    p.add_status(ROOF_HALL);
    p.add_status(ROOF_TOP);
    p.add_status(ROOF_LEAVE);
    p.add_status(ROOF_SUC);
    p.add_status(ROOF_TO_WHARF);
    game_map.add_pos(p);

    p.set("wharf",35,75);//ˮ����ͷ
    p.add_status(WHARF_DECIDE);
    game_map.add_pos(p);

    p.set("lake",35,75);//�����
    p.add_status(LAKE_ROW);
    p.add_status(LAKE_FIGHT);
    p.add_status(LAKE_SAVE);
    p.add_status(LAKE_SUC);
    game_map.add_pos(p);

    p.set("south gate",0,0);//���ų���
    p.add_status(SOUTH_END);
    game_map.add_pos(p);

    //֧�ߵص��ʼ��
    p.set("east building", 50, 50);//���̣�ˢ�ֿߣ�
    p.add_status(EAST_BUILDING);
    game_map.add_pos(p);

    p.set("library", 20, 5);//ҽѧͼ��ݣ����ʿ⣩
    p.add_status(LIBRARY);
    game_map.add_pos(p);

    //init player
    pl.set_pos(game_map.get_pos("dormitory"));
}

void Game::catchvalue (int beginpos , string get , stringstream & ss , int& answer)
{
    //cout << get << endl; 
    ss << get.substr(beginpos,get.size()-1) ;
    ss >> answer ;
    ss.clear() ;
    return ;
}

bool Game::Load(string filename)//��ʵ�ֵĶ�������
{
    
    //���ļ�
    //��txt�ļ��������淵��false)
    //���ζ���bag�ĳ�Ա����������bag����
    //���ζ���player��Ա����������������game������player������
    //���ζ���game��Ա����������������game���������

    //�ɹ��򷵻�true
    cout << "������ . . ." << endl;
    ifstream fin(global_save_file_name.c_str(), ios::in);
    if (!fin) { //��ʧ��
        cout << "��ȡ�浵ʱ��������(�����Ǵ浵�ļ�������)��" << endl;
        return false ;
    }
    else
    {
        string get ; 
        stringstream ss ; ss.clear() ;
        int value ;
        getline(fin,get) ;
        while(get != "Game member:")
        {
            getline(fin,get) ;
        }
        getline(fin,get) ; catchvalue(7,get,ss,value)  ; stage = GAME_STAGE ( value );  //stage
        getline(fin,get) ; catchvalue(9,get,ss,value)  ; partner_alive = value ; //partner
        getline(fin,get) ; catchvalue(8,get,ss,value)  ; enemy_alive = value ; //partner

        getline(fin,get) ;
        while(get != "Player member :")
        {
            getline(fin,get) ;
        }
        getline(fin,get) ; pl.setname( get.substr(6,get.size()-1) );
        getline(fin,get) ; catchvalue(7,get,ss,value) ; pl.setLevel( value );
        getline(fin,get) ; catchvalue(12,get,ss,value) ; pl.setcurrentEXP( value );
        getline(fin,get) ; catchvalue(11,get,ss,value) ; pl.setcurrentHP( value );
        getline(fin,get) ; catchvalue(7,get,ss,value) ; pl.setMAXHP( value );
        getline(fin,get) ; catchvalue(7,get,ss,value) ; pl.setspeed( value );
        getline(fin,get) ; catchvalue(17,get,ss,value) ; pl.setmove_capability( value );
        getline(fin,get) ; catchvalue(7,get,ss,value) ; pl.setmoney( value );
        getline(fin,get) ; get = get.substr(17,get.size()-1) ;
        if (get == "NULL") pl.setcurrent_Veh(NULL) ;
        else
        {
            Vehicle *p ;
            if (get == global_car_name){p = new Car ;}
            else if (get == global_ebike_name){p = new E_Bike ;}
            else if (get == global_bike_name){ p = new Bike ;}
            else if (get == global_boat_name){p = new Boat ;}
            pl.setcurrent_Veh(p) ;
        }
        getline(fin,get) ; get = get.substr(16,get.size()-1) ;
        if (get == "NULL") pl.setcurrent_Wep(NULL) ;
        else
        {
            Weapon *p ;
            if (get == global_fork_name ) {p = new Fork ;}
            else if (get == global_knife_name){p = new Knife ;}
            else if (get == global_umbrella_name){ p = new Umbrella ;}
            else if (get == global_gun_name){p = new Gun;}
            else if (get == global_bloodsickle_name) {p = new BloodSickle ;}
            pl.setcurrent_Wep(p) ;
        }
        getline(fin,get) ; catchvalue(16,get,ss,value) ; pl.set_status( PLAYER_STAGE (value) );
        getline(fin,get) ; get = get.substr(18,get.size()-1) ;pl.set_pos(game_map.get_pos(get)); //position
        getline(fin,get) ; catchvalue(13,get,ss,value) ; pl.set_last_status( PLAYER_STAGE (value) );
        getline(fin,get) ; get = get.substr(15,get.size()-1) ;
        if(get=="NULL")
            pl.set_pos(NULL);
        else
            pl.set_last_pos(game_map.get_pos(get)); //last position

        getline(fin,get) ;
        while(get != "Bag member:")
        {
            getline(fin,get) ;
        }
        getline(fin,get) ; catchvalue(6,get,ss,value) ; //value = size ;
        Bag p ;
        int size = value , number = 0 , occupancy = 0 ;
        string name  ;
        for (int i = 0 ; i < size ; i++)
        {

            fin >> name >> number >> occupancy ;
            decode_str(name);
            for (int j = 0 ; j < number ; j++)
            {
                p.add(name,occupancy) ;
            }
        }
        pl.setbag( p ) ;

        fin.close();
        cout << "�����ɹ���" << endl;
        return true ;
    }
}



bool Game::Save(string filename)//��ʵ�ֵĴ浵����
{
    ofstream fout(global_save_file_name.c_str()) ;
    cout << "�浵�� . . ." << endl;
    if (fout)
    {
        fout << "Game Saved Data :" << endl;

        //����Ϸ�׶ε�д��      
        fout << "Game member:" << endl;
        fout << "stage :" << stage << endl;
        fout << "partner :" << partner_alive << endl;
        fout << "enemy :" << enemy_alive << endl << "- - - - " << endl;

        //�������Ϣ��д��
        fout << "Player member :" << endl;string name;
        fout << "Name :" << pl.getname() << endl;
        fout << "Level :" << pl.getLevel() << endl;
        fout << "CurrentEXP :" << pl.getcurrentEXP() << endl;
        fout << "CurrentHP :" << pl.getcurrentHP()  << endl;
        fout << "MAXHP :" << pl.getMAXHP() << endl;
        fout << "Speed :" << pl.getspeed() << endl;
        fout << "Move_Capability :" <<pl.get_move_capability() << endl; 
        fout << "Money :" << pl.getmoney() << endl;
        fout << "Current_Vehicle :" ;
        if (pl.get_vehicle() != NULL)  fout << pl.get_vehicle()->getname() << endl;
        else { fout << "NULL" << endl;}
        fout << "Current_Weapon :" ;
        if (pl.get_weapon() != NULL)  fout << pl.get_weapon()->getname() << endl;
        else { fout << "NULL" << endl;}
        fout << "Current_Status :" << pl.get_cur_status() << endl; 
        fout << "Current_Position :" << pl.get_cur_pos()->get_name() << endl;
        fout << "Last_Status :" << pl.get_last_status() << endl;
        fout << "Last_Position :" ;
        if (pl.get_last_pos() != NULL)  fout << pl.get_last_pos()->get_name() << endl;
        else { fout << "NULL" << endl;}
        fout << "- - - - " << endl; 

        //����ҵ��ߵ�д��
        fout << "Bag member:" << endl; 
        fout << "Size :" << pl.get_bag().getbag().size() << endl;
        map<string,Info> bag_copy = pl.get_bag().getbag() ;
        for (map<string,Info>::iterator p = bag_copy.begin() ; p != bag_copy.end() ; p++)
        {
            string name = p->first;
            code_str(name);
            fout << name << " " << p->second->num << " " << p->second->size << endl;
        }
        fout << "- - - - " << endl; 


        fout.close() ;
        cout << "�浵�ɹ���" << endl;
        return true ;
    }
    else
    {
        cout << "�浵ʧ�ܣ����������ļ������ڣ�" << endl;
        return false;
    }
    
}

void Game::read()
{
    cout<<"\nPlease enter: ";
    getline(cin,input_box);
    submit();
}

void Game::submit()//�ӶԻ����ȡ���������ı�,�����ı���input_box->msg, clear input_box, call process��
{
    msg=input_box;
    //�淶��msg
    transform(msg.begin(), msg.end(), msg.begin(), ::tolower);//ת��Сд
    msg.erase(0,msg.find_first_not_of(" "));//ɾ��ͷ���ո�
    msg.erase(msg.find_last_not_of(" ") + 1);//ɾ��β���ո�

    input_box.clear();
    process(msg);
}

//--------------------------Process (out put and control the game according to input, main part)--------------------
void Game::process(string msg)//����pos������msg�ı�,��ؼ��Ĳ��֣����ݵص㣬���ֳ�С״̬
{
    //������Ϸ
    if(is_end())//��Ϸ�Ѿ������������Ƿ�����
    {
        if(msg=="load")
        {
            Load(global_save_file_name);//��ȡ�浵
            return;
        }
        else if(msg=="restart")
        {
            Init();//�½���Ϸ
            return;
        }
        else if(msg=="quit")
        {
            this->stage=QUIT;
            return;
        }
        else
        {
            cout << "�밴��ʾ����ѡ��" << endl;
            cout << info_end << endl;
            return;
        }
    }
    if(msg=="quit")
    {
        this->stage=QUIT;
        return;
    }
    if(this->stage==NOT_BEGIN)
    {
        if(msg=="start")
        {
            cout<<"����"<<global_player_name<<"�����������ϵ��һ����ͨ���ѧ�������������������Ѷ���ȥ���ˣ�ֻ�����������ᡣ���Ͼŵ㣬����"
                    "����һ��ģģ���������������Ӻܶ�������ܰ����ƺ������������е����죬��������ϴ������׼��ȥ��ѧ¥��ϰ��ͻȻ������ѧ¥����"
                    "��һ��˺���ѷεĲҽ�...... (look�鿴���)"<<endl;
            this->stage = PLAYING;
            return;
        }
        else if(msg=="load")
        {
            Load(global_save_file_name);//��ȡ�浵
            return;
        }
        else
        {
            cout<<"������start��ʼ��Ϸ��������load��ȡ�浵��"<<endl;
            return;
        }
    }
    //�κγ����¶���ִ�е�ָ��
    if(msg=="help")
    {
        cout << info_help << endl;
        return;
    }
    else if(msg=="map")
    {
        pl.showmap() ;
        return;
    }
    else if(msg=="bag")
    {
        this->pl.get_bag().show();
        return;
    }
    else if(msg=="check")
    {
        this->pl.show_state();
        return;
    }
    else if((msg.find("use")==0)&&msg.length()>=5)
    {
        this->pl.use(msg.substr(4,msg.length()-4));
        return;
    }
    else if((msg.find("drop ")==0)&&msg.length()>=6)
    {
        this->pl.drop(msg.substr(5,msg.length()-5));
        return;
    }
    else if(msg=="get off")
    {
        this->pl.get_off_vehicle();
        return;
    }
    else if(msg=="save")
    {
        Save(global_save_file_name);
        return;
    }
    else if(msg=="restart")
    {
        cout << "���¿�ʼ��Ϸ!\n" << endl;
        Init();//�½���Ϸ
        return;
    }
    else if(msg=="goto east building")//ǰ������ѧ¥��ɥʬ�ߣ�
    {
        if(pl.get_cur_pos()->get_name()=="dormitory"||pl.get_cur_pos()->get_name()=="lake"
           ||pl.get_cur_pos()->get_name()=="roof"||pl.get_cur_pos()->get_name()=="library"
           ||pl.get_cur_pos()->get_name()=="east building")
        {
            cout << "��ǰλ���޷�ֱ��ǰ������ѧ¥��" << endl;
            return;
        }
        if(!pl.move_to(game_map.get_pos("east building")))
            return;
        pl.get_off_vehicle();
        cout << "�������˶��̡�" << endl;
        return;
    }
    else if(msg=="goto library")
    {
        if(pl.get_cur_pos()->get_name()=="dormitory"||pl.get_cur_pos()->get_name()=="lake"
           ||pl.get_cur_pos()->get_name()=="roof"||pl.get_cur_pos()->get_name()=="library"
           ||pl.get_cur_pos()->get_name()=="east building")
        {
            cout << "��ǰλ���޷�ֱ��ǰ��ҽѧͼ��ݣ�" << endl;
            return;
        }
        if(!pl.move_to(game_map.get_pos("library")))
            return;
        pl.get_off_vehicle();
        cout << "��������ҽѧͼ��ݡ�" << endl;
        return;
    }
    else if(msg=="clear")
    {
        system("cls");
        return;
    }
    else if((msg.find("sudo goto")==0)&&msg.length()>=11)
    {
        this->pl.move_to(game_map.get_pos(msg.substr(10, msg.length()-10)));
        pl.get_off_vehicle();
        return;
    }
    else if((msg.find("sudo pick")==0)&&msg.length()>=11)
    {
        this->pl.pick(msg.substr(10, msg.length()-10), SUDO);
        return;
    }
    else if((msg.find("sudo take")==0)&&msg.length()>=11)
    {
        Vehicle* v = Vehicle::new_veh(msg.substr(10, msg.length()-10));
        this->pl.take_vehicle(v);
        return;
    }
    else if(msg=="sudo recover")
    {
        this->pl.changeHP(pl.getMAXHP() - pl.getcurrentHP());
        cout << "�ѻظ������������" << endl;
        return;
    }
    //���κγ���֮�¶���ִ�е�ָ��
    else if(pl.get_cur_pos()->get_name()=="dormitory")//Scene 1: Dormitory
    {
        if(pl.get_cur_status()==DOR_TO_LOOK_OUTSIDE)
        {
            if(msg=="look")
            {
                cout << "�㼱æ������ȥ���������𾪵�һĻ�����⣬һȺɥʬ���ڷ��˺ҧһ��ѧ��������ѧ����������ҽУ�����������ʧȥ��"
                        "���󣬱�ø���Ⱥɥʬһ��������ʶ����ѧУ�����˿��µ�ɥʬ���������������취�ӳ�ȥ��\n�����ѡ��\nlook���鿴������Χ���\ngoto shop: ǰ���������й۲�"
                     << endl;
                pl.set_status(DOR_TO_CHOOSE);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"����look����۲����"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==DOR_TO_CHOOSE)
        {
            if(msg=="look")
            {
                cout <<"�㱳���Լ�����������ȥ�����о���Ҫ��һЩ׼�����㿴�˿����ܣ��������ƺ�ûʲô�Եģ�Ҳûʲô��������������������ϸ����"
                       "�ƺ�ֻ��������²�(fork)���������Լ���ɡ����������ǿ��Щ��������Ҫ��Ҫ�����أ�����ֱ��ǰ�����У�(hint�鿴��ʾ)" <<endl;
                return;
            }
            else if(msg=="pick "+global_fork_name)
            {
                pl.pick(global_fork_name, PICK);
                return;
            }
            else if(msg=="pick "+global_umbrella_name)
            {
                pl.pick(global_umbrella_name, PICK);
                return;
            }
            else if(msg=="goto shop")
            {
                if(!pl.move_to(game_map.get_pos("shop")))
                    return;
                pl.get_off_vehicle();
                cout << "����������������ɥʬ�����ߣ�һ·С��������ѧ԰��ǰ�������������" << endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look:�۲�����\npick "<<global_fork_name<<"ʰȡ�²�\npick "<<global_umbrella_name
                    <<"ʰȡ��ɡ\ngoto shopǰ����������"<<endl;
                return;
            }
        }
    }
    else if(pl.get_cur_pos()->get_name()=="shop")//Scene 2: shop
    {
        if(pl.get_cur_status()==SHOP_SEARCH)
        {
            if(msg=="look")
            {
                cout<<"���ڳ������ܿ��˿������ҵ��ǣ��ۻ�Աû�б��ɥʬ��������������׷�����ʲô��ɥʬҲ�ƺ�"
                      "�Գ����������ʳ�ﲻ����Ȥ��ֻ�������治��Ѳ�ߡ��������кܶ����������ò��С�(hint�鿴��ʾ)"<<endl;
                return;
            }
            else if(msg=="pick "+global_bread_name)
            {
                pl.pick(global_bread_name, BUY);
                return;
            }
            else if(msg=="pick "+global_knife_name)
            {
                pl.pick(global_knife_name, BUY);
                return;
            }
            else if(msg=="ask")
            {
                cout << "�ۻ�Ա�����㣺����һȺɥʬͻȻϮ��������У԰�����鷢����̫ͻȻ���ܶ��˶�����Ⱦ�ˡ�"
                        "���С���л�û�б����ơ���������ѧУ�ĸ������ڴ��Ŷ���ɥʬ��Ѳ�ߣ���������ȥ��"
                        "��˵��ѧ�������Ҵ��ߡ���������ȥ����ȥ���ҿ�,˵��������һ���ӳ�ȥ��" << endl;
                return;
            }
            else if(msg=="goto dor gate")
            {
                if(!pl.move_to(game_map.get_pos("dor gate")))
                    return;
                pl.get_off_vehicle();
                cout << "���뿪���У�����������������ſڣ����ǻ��Ǳ�ɥʬ�����ˣ�ɥʬ������ɫ����ͣ�"
                        "����������... (hint�鿴��ʾ)"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look:�鿴�������\npick bread:ʰȡ���\nask:ѯ���ջ�Ա���\n"
                "use "<<global_bread_name<<":���ԳԵ�һ��ʰȡ�������������\n"
                "pick "<<global_knife_name<<": ����һ��С��\n"
                "goto dor gate:����ȥѧ԰�ſ�(����׼�������������������ѯ�ʺ���ȥ��"<<endl;
                return;
            }
        }
    }
    else if(pl.get_cur_pos()->get_name()=="dor gate")//Scene 3: Gate of the dormitory, beside the road
    {
        Zombie* z;
        z=new Zombie;
        if(pl.get_cur_status()==GATE_FIGHT)
        {
            if(msg=="look")
            {
                z->show();
                return;
            }
            else if(msg=="escape")
            {
                pl.set_pos(game_map.get_pos("shop"));
                cout<<"���Ǳ����ӻ��˽�������,����ɥʬû��׷�������������ǵ�׼�������ʲ�����ɥʬ��ս��"<<endl;
                delete z;
                return;
            }
            else if(msg=="fight")
            {
                //ս���߼�
                switch(pl.fight(z))
                {
                    case 0:
                        this->stage=DIE;
                        cout << info_end << endl;
                        break;
                    case 1: 
                        pl.set_pos(game_map.get_pos("shop"));
                        cout<<"���Ǳ����ӻ��˽�������,����ɥʬû��׷�������������ǵ�׼�������ʲ�����ɥʬ��ս��"<<endl;
                        delete z;
                        break;
                    case 2:
                        pl.set_status(GATE_AFTER_FIGHT);
                        cout <<"���þ���ȫ����ɥʬ����������ǰ�����ˣ���Ҳ��������������û�б�ҧ����������ѧ԰��ǰ��·�ԣ��������ܿ���һ�ˣ�ֻ��"
                                "Զ����Լ�м�ֻɥʬ������Ŀ�ĵ����š�����ȥ���̣��ɲ�ȷ���Լ��������ܷ�֧���Լ��ߵ���" <<endl;
                        delete z;
                }
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴ɥʬ��Ϣ\nescape:�ӻس���\nfight:ӭս\n����ʹ��use <������> ָ��䱸��������ս"<<endl;
                delete z;
                return;
            }
        }
        if(pl.get_cur_status()==GATE_AFTER_FIGHT)
        {
            if(msg=="look")
            {
                cout<<"�������ܿ��˿�������ֻ��һЩ��������Ĺ�������һ�������ŵ�С�꣬��ͣ��·�Ե�һЩ���ų��ŵ�˽�ҳ���"<<endl;
                return;
            }
            else if(msg=="take "+global_bike_name)
            {
                Vehicle* v= Vehicle::new_veh(global_bike_name);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take "+global_ebike_name)
            {   
                Vehicle* v= Vehicle::new_veh(global_ebike_name);
                pl.take_vehicle(v);
                return;               
            }
            else if(msg=="take "+global_car_name)
            {
                cout<<"��û�г�Կ��,�޷�����˽�ҳ���"<<endl;
                return;
            }
            else if(msg=="goto west building")
            {
                if(!pl.move_to(game_map.get_pos("west building")))
                    return;
                pl.get_off_vehicle();
                cout<<"�����������̣���ǰ�ľ���������һ��...... (hint�鿴��ʾ)"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴��·���\ntake "<<global_bike_name<<": �������г�\ntake "<<global_ebike_name
                    <<":����С��\ntake "<<global_car_name<<": ������\n""goto west building: ȥ����"<<endl;
                return;
            }
        }
    }
    else if(pl.get_cur_pos()->get_name()=="west building")//Scene 4: West teaching building
    {
        if(pl.get_cur_status()==WEST_INTO_BUILDING)
        {
            if(msg=="look")
            {
                cout<<"���̵�һ¥���������Ѫ���Ͳ�֫���鲼�Ĵ�������Ż�¡�¥�ϴ�������ɥʬ��˻����������ɥʬ�ƺ��հ�����ɨ��һ�ա�"
                        "������ǽ����ʾ����ռ���ʵĴ�����0%��0%��0%...�������˶��������������˾�����ͻȻ�㿴����һ���֣���1-404��ռ����1%"
                        "���ͬʱ��������¥�����˺�����������������ʮ�ּ�����ԭ�������Լ����������Ҵ��ߣ�"<<endl;
                return;
            }
            else if(msg=="search")
            {
                pl.set_status(WEST_MEET);
                cout<<"��������ŵ�����¥�ݣ�����ɥʬ���֡��ò�������������1-404�ſڣ�����ȴ�쳣��������С�������̽��ͷȥ������������һ��Ů����"
                        "����Ҳ��ȷ�����ǲ���ɥʬ���������㣬Ҳʮ�ֺ��£������ʵ����㣬��û�б���Ⱦ�ɡ�������һ������˵����û��û�У���Ҳ�Ǹ��������,"
                        "���ﵽ�׷�����ʲô�������㲻��ɥʬ�������˹�����˵������������������ϰ�����˯���ˣ�����10����ʱ����������һ���궯��"
                        "���žͳ�����һȺ���µ�ɥʬ�����˾�ҧ����������ϰ��ͬѧ�ܶ඼��...�����Ż��ˣ����˸����ң����˵ƣ�����������һֱ���ҳ�ȥ��"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴�������\nsearch: Ѱ���Ҵ���"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==WEST_MEET)
        {
            if(msg=="look")
            {
                cout<<"��ǰ�����Ů����������ʮ����������������˾��֣���������˵�ѡ��ſ���ɥʬ���ⲽ����"<<endl;
                return;
            }
            else if(msg=="give "+global_bread_name)
            {
                if(!pl.have(global_bread_name))
                {
                    cout<<"��û�������"<<endl;
                    return;
                }
                cout<<"�������ݸ����������������"<<global_player_name<<"������æ��л��˵�����ҽ�С��������Ҵ��ߣ�Ҫ��ֻʣ��һ�������治֪������ô�졣"
                        "�����������ڽ��ҵ���Ҳ���ǰ취������취�������ӳ�ȥ������̾��̾����˵��û�취��ѧУ������"
                        "���ڵı������Ѿ���ɥʬ��Ⱦ�ˣ��ſھۼ��˴���û�������ɥʬ�����ǳ���ȥ�ġ�"
                        "��˵����Ȼ���������Ǳ������һ��ɥʬ���������������ˡ�"<<endl;
                pl.drop(global_bread_name);
                return;
            }
            else if(msg=="leave")
            {
                cout<<"�����С���߳����ң���ҪѰ����������ɥʬ�ƺ���ͬ��... (look�鿴ɥʬ����)"<<endl;
                pl.set_status(WEST_FIGHT);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴�������\ngive "<<global_bread_name<<": �����������������˵��������˵Щʲô\nleave: �߳�����Ѱ������"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==WEST_FIGHT)
        {
            Zombie* z=new Roll_Zombie;
            if(msg=="look")
            {
                cout<<"һֻɥʬ��������һ���飬�������������ˣ��Ǿ���ɥʬ��"<<endl;
                z->show();
                return;
            }
            else if(msg=="fight")
            {   
                switch(pl.fight(z))
                {
                    case 0:
                        this->stage=DIE;
                        cout << info_end << endl;
                        break;
                    case 1: 
                        pl.set_status(WEST_MEET);
                        cout<<"�����һ�أ��ӻ��˽�������"<<endl;
                        delete z;
                        break;
                    case 2:
                        pl.set_status(WEST_CHECK);
                        cout<<"�Ѿ��˾�ţ����֮����������˾���ɥʬ����������¡����ŵ�����ǰ��ɥʬ�����С�������˼(look�鿴ɥʬ)"<<endl;
                        delete z;
                }
                return;
            }
            else if(msg=="escape")
            {
                pl.set_status(WEST_MEET);
                cout<<"�����һ�أ��ӻ��˽�������"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴�������\nfight:��ɥʬ��ս\nescape: �ӻص�����"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==WEST_CHECK)
        {
            if(msg=="look")
            {
                cout<<"��ǰ��ɥʬ˫ĿԲ����ͷ�����࣬���ݡ���ͷȫ����˯}�˵���ɫ��С�����Ա�˵���������������Ȼ��ù�ɥʬ��Ҫ��Ҫ���һ��"
                      "���أ�˵�������ѳ�ʲô����������ȡһЩ������(search����)"<<endl;
                return;
            }
            else if(msg=="search")
            {
                cout<<"�������������ҵ��������ֻ���ɨ��ɨ���������군�����ɥʬ̫��ɨ��������û�취��������ָ�ƽ������ֻ�"
                        "����ûʲô�ر�Ķ��������΢�ţ����Ǹ���ʦ��ʵ����ͬѧ�Ĺ��ڿ��е����죬�������Ӷ�û�У���Ȼ�ǵ����ϲ���"
                        "ͻȻ��С�����Ա߷�����һ����ߣ��㿴�Ǹ������һ����Ϣ����������9�㣬��ʦ����ȥʵ���ң�Ȼ��������û��������Ϣ�ˡ�"
                        "�������˼������ϸһ����ԭ��������ϵ���ϲ���������ʵ�����ƺ������������������ء�С��˵��Ҫ������ȥ��������ʵ����"
                        "��һ���ɣ�˵�������ҵ�������Ⱦ��������"<<endl;
                return;
            }
            else if(msg=="take "+global_bike_name)
            {
                Vehicle* v= Vehicle::new_veh(global_bike_name);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take "+global_ebike_name)
            {   
                Vehicle* v= Vehicle::new_veh(global_ebike_name);
                pl.take_vehicle(v);
                return;               
            }
            else if(msg=="goto bio lab")
            {
                if(!pl.move_to(game_map.get_pos("bio lab")))
                    return;
                pl.get_off_vehicle();
                cout<<"���С��һ������������ʵ����(look�鿴�����go inֱ�ӽ���)"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴��ȥ��ɥʬ���\nsearch:���ɥʬ\ntake "<<global_bike_name<<":����¥�£������г�\n"
                    "take "<<global_ebike_name<<":����¥�£���С��\ngoto bio lab: ǰ������ʵ����(�����ȳ�����ͨ����)"<<endl;
                return;
            }
        }
    }
    else if(pl.get_cur_pos()->get_name()=="bio lab")//Scene 5: Biology laboratory
    {
        if(pl.get_cur_status()==BIO_INTO_BUILDING)
        {
            if(msg=="look")
            {
                cout<<"����ʵ����λ���Ͻ�۶��Ͻǵ�һ����ɫ�Ĵ�¥�С��ע�⵽�����ſڲ�û�п�����ֻɥʬ�����ǵ���ȴ���������������ɥʬ��Ѫ��ӡ��������֡�"
                        "���ó�ɥʬ���ֻ����Ա������¼��û�����ĵ�ʦ�������������������ʵ���ҵ���������..."<<endl;
                return;
            }
            else if(msg=="go in")
            {
                cout<<"���ƿ�������ʵ���ҵ��ţ���ǰ�ľ�������ʮ������, ����һ����... (look�鿴���)"<<endl;
                pl.set_status(BIO_MEET);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴�ſ����\ngo in: ��������ʵ����"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==BIO_MEET)
        {
            if(msg=="look")
            {
                cout<<"��ǰ��һλ������ڣ����Ÿɾ�����Ȼû�б�ɥʬ��Ⱦ��ʵ���ҵ������ϣ��ڷ������װ������Լ����ӣ���ͷ��С"
                      "�к�ɫ�ģ�����ɫ�ģ�����С��С���ʵ���Ҫ��Ҫ��һ����ʲô����أ� (askѯ��)"<<endl;
                return;
            }
            else if(msg=="ask")
            {
                cout<<"�������ӽ���˵�Լ���Ҷ��������ѧԺ�Ľ��ڣ������ѧ����ʵ������ʵ�飬û�뵽������ʱ���Ѿ������ɥʬ������֪����ô����"
                        "��æ�������������⣬�Լ�Ҳһֱ���ҳ�ȥ��һֱ����ʵ�������з���ҩ�������룺��ҩ���ò�������Щ�������̵Ĺ��Ӱɣ�"
                        "������˵��������Ӧ��Ҳ���ȥ�ɣ���ϧ����ѧУ���ڶ���ɥʬ���أ���������ȥ���ҽ�������ȥ�ɹ���ѧԺ��¥���������������Ա���ߵ��Ǹ�����"
                        "������������¥��ȥ�Ƕ�¥��¥����ȥ��һ����������Ұ�ã����Կ�����û�г�·���������������Ҳ�ǱȽ����׷��ֵġ�С��ܼ�����ȷʵ�Ǹ������⣡"
                        "��Ҳ������һ��ȥ�ɡ�Ҷ�������ε�Ц��Ц��˵�����ˣ����ˡ���ȥ�������ͽ���������һ����з���ҩ�ɣ�˵�������ܽ�ȸ�Ⱦ��ͬѧ��"
                        "Ŷ���ˣ�����ͦԶ�ģ��ҵĳ�ͣ��¥���ˣ�����Ҫ�ÿ��Կ���˵�궪��������һ����Կ�ס�"
                        "�㿴�˿���ǰ��Ҷ���ڣ�������˵��ȷʵ�е������ܸо��ľ仰�ֵֹġ����ˣ�������ȥ�����ɡ�"<<endl;
                return;
            }
            else if(msg=="pick "+global_redtube_name)
            {
                pl.pick(global_redtube_name, PICK);
                return;
            }
            else if(msg=="pick "+global_greentube_name)
            {
                pl.pick(global_greentube_name, PICK);
                return;
            }
            else if(msg=="leave")
            {
                pl.set_status(BIO_LEAVE);
                cout<<"���С���뿪��ʵ���ң��ص������¥¥�¡�"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: ���ʵ�������\nask: ѯ�ʽ������\npick "<<global_redtube_name
                    <<": ͵͵���ߺ�ɫ�Թ�\npick "<<global_greentube_name<<": ͵͵������ɫ�Թ�\nleave: �뿪ʵ����"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==BIO_LEAVE)
        {
            if(msg=="look")
            {
                cout<<"¥�£���ɢ��ͣ�����г���С�꣬�����Ա�Ҷ���ڵ�˽�ҳ�����ȥ��Ժ̫����������������Ҳ��̫����Ҷ���ڡ�"<<endl;
                return;
            }
            else if(msg=="take "+global_ebike_name)
            {
                cout<<"С��û���ˣ�"<<endl;
                return;
            }
            else if(msg=="take "+global_bike_name)
            {
                Vehicle* v= Vehicle::new_veh(global_bike_name);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take "+global_car_name)
            {
                Vehicle*v =Vehicle::new_veh(global_car_name);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="goto roof")
            {
                if(!pl.move_to(game_map.get_pos("roof")))
                    return;
                pl.get_off_vehicle();
                cout<<"���С�������Ժһ·�����ɹ�Ժ¥����������¥����һ·�ϣ��������������µ�ɥʬ��������ǰ�ȫ�������ⶰ�߸߽�����һ¥������"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: ���·�����\ntake "<<global_bike_name<<": �������г�(������Ŀ�ĵ��е�Զ)\ntake "<<global_ebike_name<<": ��С��\n"
                        "take "<<global_car_name<<": ��Ҷ���ڵ�˽�ҳ�\ngoto roof: ǰ���ɹ�Ժ¥��"<<endl;
                return;
            }
        }
    }
    else if(pl.get_cur_pos()->get_name()=="roof")//Scene 6: The roof of the old management college
    {
        if(pl.get_cur_status()==ROOF_HALL)
        {
            if(msg=="look")
            {
                cout<<"���������ȥ���������ˡ����������м��ҵĴ򶷺ۼ���Ѫ�������׵������ǣ����ϻ���һֻ���֣������������һ��ǹ��"
                        "�������﷢������ս������ֵ������������ƺ���û��ɥʬ�Ķ�����С��˵��Ҫ�������������ݵ�¥�������ɣ�"
                        "����Ҷ����˵�ģ�������Ұ�ã��ܿ����ĸ�����ɥʬ�١��л����ӳ�ȥ��(hint�鿴��ʾ)"<<endl;
                return;
            }
            else if(msg=="pick "+global_gun_name)
            {
                pl.pick(global_gun_name, PICK);
                return;
            }
            else if(msg=="go up")
            {
                cout<<"���С��˵���������¥��"<<endl;
                pl.set_status(ROOF_TOP);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴�������\npick "<<global_gun_name<<": ����������ŵ�ǹ\ngo up: ������ȥ¥��"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==ROOF_TOP)
        {
            if(msg=="look")
            {
                cout<<"���С�������˾ɹ�Ժ��¥������������������ߵ㣬��Ұ��Ϊ������������Զ����ȥ�����ȫòһ�����ࡣ"
                        "���Կ���ѧУ������ɢ���ż����ꤵ�ɥʬ������۹�Ͷ�򶫶��ţ��������ϣ�ȫ��ɥʬ��УҽԺ���š��������Ҳ�ǡ�"
                        "��ת��ͷ������Ķ����š��������½����ϴ����ſ�Ҳ��Χ����ɥʬ��������У���ӳ�û���κ�ϣ���ˣ����С�������˾���..."
                        <<endl;
                Player::delay();
                cout<<"�㶢���������ͻȻ��ǰһ�����������֧���������������Ϸ���ȥ�������ϻ�԰��С���ƺ�����������뷨"
                        "æ˵������˵˳����������ϻ�԰������һ�����ص�ˮ·������ͨ��ѧУ�ϱߵ��ຼ���ӣ�Ҳ����˵�����ǿ���ͨ��ˮ·��У��"
                        "����ϲ�����侲������˵�����ǣ�������ô��ˮ·�����أ�������û�д���С�������룬˵����ˮ����ͷ��������ѧУ�����"
                        "ˮ���˶��ε��Ͽεص㣬��ǡ���Ϲ������������Ƥ��ͧ�����ǿ��Ի�����˳��ˮ·һ·��ȥ!"<<endl;
                return;
            }
            else if(msg=="leave")
            {
                pl.set_status(ROOF_LEAVE);
                cout<<"���С��׼���뿪��¥������ǰ��ˮ����ͷ������ȷ������һ˿���Ծ�... (look�鿴���)"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �����������۲�ѧУ���\nleave: ׼���뿪��¥������ǰ�������"<<endl;   
                return;
            }
        }
        else if(pl.get_cur_status()==ROOF_LEAVE)
        {
            vector<Zombie*> v_zom;
            Zombie *z1 = new Zombie;
            Zombie *z2 = new Roll_Zombie;
            Zombie *z3 = new Fire_Zombie;
            v_zom.push_back(z1);
            v_zom.push_back(z2);
            v_zom.push_back(z3);
            
            if(msg=="look")
            {
                cout<<"��ʱ��¥�ĵ��ݺ����ˣ���¥�ݴ������ӵ�����������ϸһ�����ƺ���ɥʬ�����������С��æ�ܻ�¥�����¿���"
                        "��ǰ�ľ�����������˸�������¥�£���Ⱥ��ɥʬ��ӿ���¥��¥���ɥʬ�ĽŲ���Խ��Խ��..."
                        "��ô����������Զ�������Ȼ��������һ����Ϥ���ˣ�������¥�µĻ�̳�ԣ����ݲ��ȵ�Ц�ţ�ɥʬ��Ҳ��ȥ��������"
                        "��������Ȼ��Ҷ���ڣ�(ask����)"<<endl;
                for (int i = 0; i < v_zom.size();i++)
                    delete v_zom[i];
                return;
            }
            else if(msg=="ask")
            {
                cout<<"���ɻ���ַ�ŭ�ش�����Ҷ����������ô���¡�Ҷ����а���Ц�ˣ�˵����ʵɥʬ���������������з������ģ�������Ⱦ����ʵ���ҵ�ѧ��"
                        "��Ϊ��һ��ʵ���������ֻ��һ���Ͼ͸�Ⱦ��ȫѧУ������Ϊ����ѧԺΨһ�о�������������ʦ��������ͨ���ı�������������ջ����������ܣ�"
                        "ȴ���ڵò������ӣ�������ѧ��Ȧ����ʷ���Ǵ����Υ�������������Ҵ�������ˣ�Ϊ�������Ǹ������ۣ�ҲΪ��������չʾ���о���ΰ��"
                        "�ɹ����Ҿ�����ɥʬϯ��ȫУ��""�����ǣ���Ŀǰ�ҷ��ֵĽ�����Ҵ��ߡ���������ʹ����������������ܿ���"
                        "ɥʬ��������������׷ɱ���ǡ����������������ĵط��ܲ���ɣ��������ڲ���ѷɿ���"<<endl;
                for (int i = 0; i < v_zom.size();i++)
                    delete v_zom[i];
                return;
            }
            else if(msg=="jump")
            {
                cout << "��ȷ��Ҫ��¥������������(����"<<global_jump_damage<<"���������� \"yes\" ȷ��):" << endl;
                string ensure;
                getline(cin, ensure);
                if(ensure!="yes")
                {
                    cout << "��¥̫���ˣ���ʵ�ڲ�������" << endl;
                    return;
                }
                pl.changeHP(-global_jump_damage);
                if(pl.getcurrentHP()==0)
                {
                    cout << "ž�����������Ǻ������Ǿ޴�ĳ�������������ǣ���ˤ���ˣ�" << endl;
                    this->stage = DIE;
                    cout << info_end << endl;
                    return;
                }
                pl.set_pos(game_map.get_pos("wharf"));

                cout<<"You jump�� I jump�����С��һ����������������޴�ĳ���������ǲ��ɥ�����ý�ʣ��һ������ƴ���ε���ˮ����ͷ��"<<endl;
                for (int i = 0; i < v_zom.size();i++)
                    delete v_zom[i];
                return;
            }
            else if(msg=="fight")
            {
                //fight success
                switch (pl.fight_many(v_zom))
                {
                    case 0:
                        this->stage = DIE;
                        cout << info_end << endl;
                        break;
                    case 1:
                        cout << "���Ƿ����򲻹���ô��ɥʬ���Ǳ������˻�ȥ" << endl;
                        break;;
                    case 2:
                        cout << "��ɹ��������һȺɥʬ��˳�Ų��¥��ɱ�˳�ȥ��������¥��Ҷ������ǰ(look�鿴)" << endl;
                        pl.set_status(ROOF_SUC);
                }
                for (int i = 0; i < v_zom.size();i++)
                    delete v_zom[i];
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴��Χ���\nask: ����Ҷ����\njump: ����С���¥���������������Σ��,����"<<global_jump_damage<< "������"
                      "����ȥˮ����ͷ\nfight: ��ɥʬӲ�գ�˳��¥��ɱ��ȥ"<<endl;
                for (int i = 0; i < v_zom.size();i++)
                    delete v_zom[i];
                return;
            }
        }
        else if(pl.get_cur_status()==ROOF_SUC)
        {
            if(msg=="look")
            {
                cout << "Ҷ����û�뵽���Ǿ���ɱ������ʮ���𾪣���¶��ɫ��С��˵��Ҫ������һ���ɡ�(hint�鿴��ʾ)" << endl;
                return;
            }
            else if(msg=="fight")
            {
                cout << "���������ʦ��������ɥʬʵ�����Ϊ�ǳ�ʹ�ޣ�������У�Ϊ�������\n�����������ǿ�ʼ˼����һ������ô���ˡ�" << endl;
                enemy_alive = false;
                pl.set_status(ROOF_TO_WHARF);
                return;
            }
            else if(msg=="forgive")
            {
                cout << "������С��Ļ�������û�ж�Ҷ����ʹ��ɱ�֡������㲻ע�⣬��������˳���ѳ������ˡ���������������ڣ�����ô���أ�" << endl;
                pl.set_status(ROOF_TO_WHARF);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �۲�Ҷ������ɫ\nfight: ����Ҷ����\nforgive: ��Ҷ����һ��"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==ROOF_TO_WHARF)
        {
            if(msg=="look")
            {
                cout << "�㿴�˿����ܣ��Ӵ�¥���¿��Կ����԰���ˮ����ͷ���ԣ���������Ҫǰ��ˮ����ͷ����ˮ·���ܣ����ǣ���ôȥ�أ�"
                     << "������Χ���˿��������г����е綯����";
                if(enemy_alive)
                    cout << "������ʱ���������Ҷ���ڿ���������, �淳��" << endl;
                else
                    cout << "��������ʱ�򿪵�Ҷ���ڵ�������" << endl;
                return;
            }
            else if(msg=="take "+global_bike_name)
            {
                Vehicle* v= Vehicle::new_veh(global_bike_name);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take "+global_ebike_name)
            {   
                Vehicle* v= Vehicle::new_veh(global_ebike_name);
                pl.take_vehicle(v);
                return;               
            }
            else if(msg=="take "+global_car_name)
            {
                if(enemy_alive)
                    cout << "Ҷ���ڸղ��Ѿ������������ˣ�" << endl;
                else
                {
                    Vehicle *v = Vehicle::new_veh(global_car_name);
                    pl.take_vehicle(v);
                }
                return;
            }
            else if(msg=="goto wharf")
            {
                if(!pl.move_to(game_map.get_pos("wharf")))
                    return;
                pl.get_off_vehicle();
                cout << "����������ˮ����ͷ" << endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴��Χ���\ntake "<<global_bike_name<<": �������г�\ntake "<<global_ebike_name
                    <<":����С��\ntake "<<global_car_name<<": ������\n""goto wharf: �˵�ǰ�ؾߣ�ȥˮ����ͷ"<<endl;
                return;
            }
        }
    }
    else if(pl.get_cur_pos()->get_name()=="wharf")
    {
        if(pl.get_cur_status()==WHARF_DECIDE)
        {
            if(msg=="look")
            {
                cout << "��������ˮ����ͷ���������ﴬֻȷʵ���٣����м������ʵ�ƻ����С������һ�ҿ������Ƚ��µĴ���";
                if(enemy_alive)
                    cout << "Զ����Ҷ�����ڶ԰��Ĵ�¥�������ܻ���";
                cout<<"�������򲨹����Ե�ˮ�棬�������������������ƺ�������ʲôΣ����׼��������"<<endl;
                return;
            }
            else if(msg=="pick "+global_apple_name)
            {
                pl.pick(global_apple_name, PICK);
                return;
            }
            else if(msg=="take "+global_boat_name)
            {
                Vehicle* v=Vehicle::new_veh(global_boat_name);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="row")
            {
                if(pl.get_move_capability()==0)
                {
                    cout<<"��ǰ�Ľ�ͨ�����޷���ˮ����ʻ��"<<endl;
                    return;
                }
                pl.set_pos(game_map.get_pos("lake"));
                cout<<"���С�������Ƥ��ͧ�����������ţ�׼�������������..."<<endl;

                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴��ͷ���\npick "<<global_apple_name<<": ����ƻ��\ntake "<<global_boat_name
                    <<": �˴�\nrow: ����ȥ����\n(������use bread����ղ���ʧ������)"<<endl;
                return;
            }
        }
    }
    else if(pl.get_cur_pos()->get_name()=="lake")
    {
        if(pl.get_cur_status()==LAKE_ROW)
        {
            if(msg=="look")
            {
                cout<<"�����ڴ����Ĵ���������ͷһ��";
                if(enemy_alive)
                    cout << "����Ҷ�����Ѿ���������Ӱ";
                cout<<"��Զ���ľɹ�Ժ¥���ϣ�Ҳ�������Ǹո��ڵĵط����Ѿ�������ɥʬ��"
                      "С�������Աߣ����˿�����˵����������ʱ��ȫ�ˣ��������㣬��Ȼ��һ���˿϶��Ӳ���ȥ����ȥ�Ժ���һ��Ҫȥ"
                      "���ҵİְ����裬����һ���ܵ����ҡ���Ҳ���������������룬������Ҫ����������ຼ���ӣ��Ͱ�ȫ�ˣ�"<<endl;
                return;
            }
            else if(msg=="goto south gate")
            {
                pl.set_status(LAKE_FIGHT);
                cout<<"���Ǿ�������ȥ�ϴ����Ե�ˮ�����������ӳ�ȥ��������ǰ�ľ���������һ��... (look�鿴���)"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴���������\ngoto south gate: ׼�������ϴ���"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==LAKE_FIGHT)
        {
            Zombie* z=new Water_Zombie;
            if(msg=="look")
            {
                cout<<"��Ҫ��ʻ���ϱߣ���Ҫ���������ţ����Ƕ���һ�����Ŷ��ﾹȻ�ε��ſ��µ�ɥʬ����ˮɥʬ��"
                    "����ϸһ����ˮɥʬ�ſ��}�˵���ɫ��ͣ������˷��Ƶ��������ι�������Ⱥˮɥʬ��������Ӿ�����ҿ������������ͣ�"<<endl;
                z->show();
                return;
            }
            else if(msg=="escape")
            {
                pl.set_pos(game_map.get_pos("wharf"));
                cout<<"���С��Ͻ���ͷ�����ٻ��򰶱ߣ��ӻ�ˮ����ͷ��"<<endl;
                return;
            }
            else if(msg=="fight")
            {
                switch(pl.fight(z))
                {
                    case 0:
                        this->stage=DIE;
                        cout << info_end << endl;
                        break;
                    case 1: 
                        pl.set_pos(game_map.get_pos("wharf"));
                        cout<<"���С��Ͻ���ͷ�����ٻ��򰶱ߣ��ӻ�ˮ����ͷ��"<<endl;
                        delete z;
                        break;
                    case 2:
                        //����ɹ����ˮɥʬ
                        cout<<"����һ����ս����������һ�������ˮɥʬ�������Աߵ�С��ȴ���Ÿ첲����Щ���Ծ�...(look�鿴С�����)"<<endl;
                        pl.set_status(LAKE_SAVE);
                        delete z;
                }
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴ˮɥʬ���\nfight: ��ˮɥʬս����ͻ�Ʒ���\nescape: ��ͷ�ӻ�ˮ����ͷ"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==LAKE_SAVE)
        {
            if(msg=="look")
            {
                cout<<"�㿴��С��������ĸ첲������һ����������ɫ�˿ڣ����ˣ��ղŵ�ս����С�ﱻˮɥʬҧ���ˣ�"
                        "С���������������۽����£�����������ԭ��ˮ�������۾���ʼ���ף����������ӣ����ͻ���ɥʬ��"
                        "��������˵�����Բ������������ˣ������Ҳ��������ӳ�ȥ�ˣ��������´��ɣ�����..."
                        "������һƬ�հף��������ںޣ��ղ�û�б�����С��������취�����ͻ���Լ�Ҳҧ�ˡ�"
                        "���㿴������ʵ�ڲ����Ľ������´���������Զ��˯��������ס������ѵ����û��ʲô�취����"<<endl;
                Player::delay();
                cout<<"ͻȻ���뵽������ʵ���������Щ�������̵�ƿ�Ӻ�Ҷ���ڵĻ����᲻���н�ҩ�����ǣ����ǣ�Ҷ�����ǻ��˰���"
                        "����Ļ��з���ҩ�𣿾���ᣬ�ǵ��׺�ɫ�Լ��ǽ�ҩ������ɫ�Լ����أ�����ô��ˣ�˵��һ���������ϱ��ɥʬ��"
                        "���Լ�ҧ���������Լ���ʱ��û��˳��һƿ�����ǵ��ˣ���һ�±�������һ�°ɣ�(hint�鿴��ʾ)"<<endl;
                return;
            }
            else if(msg=="push")
            {
                cout<<"��һ���ģ��͵ذ�С��������ȥ���㿴����������һ��һ��������ȥ����������ˮ�ף����㣬����һ�ˣ���������..."<<endl;
                partner_alive = false;
                if(!pl.move_to(game_map.get_pos("south gate")))
                    return;
                return;
            }
            else if(msg=="give "+global_redtube_name)
            {
                if(!pl.have(global_redtube_name))
                {
                    cout<<"��֮ǰ������ʵ���Ҳ�û�����ߺ�ɫ�Լ�"<<endl;
                    return;
                }
                pl.drop(global_redtube_name);
                cout<<"С����º�ɫ�Լ���������ɫ����Ѫ�Ƶģ�Ч����Ȼ�ܺá�С����˿��漣��������ˣ�����Ҳ�𽥻ظ�ƽ����"
                        "���ſ�˫�ۣ�˵����лл������ң������룺��Ҷ������Ȼ�������£���������һ�֣����н�ҩ��˵����"
                        "���Է���һ�Լ���Ⱦ���õģ����õ�ʱ�Լ����顢������һƿ������С�ﰲȫ�ˣ�����������һ������"
                        "����һ������ص�ˮ·��������"<<endl;
                if(!pl.move_to(game_map.get_pos("south gate")))
                    return;
                return;
            }
            else if(msg=="give "+global_greentube_name)
            {
                if(!pl.have(global_greentube_name))
                {
                    cout<<"��֮ǰ������ʵ���Ҳ�û��������ɫ�Լ�"<<endl;
                    return;
                }
                pl.drop(global_greentube_name);
                cout<<"С�������ɫ�Լ���ͻȻ˫Ŀ��ף��˿ڶ񻯣�ȫ��鴤����ͻȻ��ʶ������Ҷ���ڷ�����ɥʬ����ҩ������������ʹѧ�����¡������˵�һ��ɥʬ��"
                        "Ҳ����������������ȫ������ɫ������һ�ж��Ѿ����ˣ�С��˲�����˿��µ�ɥʬ��һ�ڰ���ҧס����Ҳ�����ɥʬ������������������"<<endl;
                partner_alive = false;
                this->stage=DIE;
                cout << info_end << endl;
                return;
            }
            else if(msg=="goto south gate")
            {
                cout<<"���˵�С�����ڴ����棬ʹ�ý�ҩ������������������ţ�˵��һ�������������ҵ��������㻮�������Ϳ쵽�ˡ�"
                        "�㿴�����ຼ���ӵ���ڣ������˰�ѧУ���ذ�Χ���侯���㿴����ϣ����ͻȻ���㱳��һʹ���㾪㵵ػ�ͷһ����"
                        "С����ҧ����ļ���˿�������ɫ��Һ�塣�����۾��Ѿ���ȫ�����ˣ���������һ���ᣬ������������˵���ԣ��Բ���..."
                        "������߿�ʼģ������֫�����������գ�Ҳ�����˴��ϣ������ɥʬ...����������������"<<endl;
                this->stage=DIE;
                cout << info_end << endl;
                return;
            }
            //use red/green tube��ȫ����
            else if(msg=="hint")
            {
                cout<<"look: ���С�����\npush: ��С�����´�\ngive "<<global_redtube_name<<": ��С�����Ѫ��ɫ�Լ�\n"
                       "give "<<global_greentube_name<<": ��С���������ɫ�Լ�\n"
                       "goto south gate: ǿ�д��ű�ҧ�˵�С���������\n(����������bag��һ�±�������ʲôҩ��)"<<endl;
                return;
            }
        }
    }
    else if(pl.get_cur_pos()->get_name()=="south gate")
    {
        if(pl.get_cur_status()==SOUTH_END)
        {
            if(msg=="look")
            {
                cout<<"˳����������ˮ·��Ȼ�������ϴ����Աߵ��ຼ���ӡ����������Ǹ���ѧУ������һ���ӣ���ˮ�����ֳ󣬿�����ȴʮ������";
                if(!partner_alive)//С���Ѿ�����
                    cout<<"����԰���ȥ������ѧУ���ѱ��侯��Χ�ˣ�����ȫ�Ǿ������侯������ǹ��׼���㣬��Ȼ������Ǳ�ڵ�ɥʬ��"<<endl;
                else//С�����һ���ӳ�����
                    cout<<"С��ָ��԰�������˵��������ת��ͷ��ԭ����ѧУ�������ѱ��侯���ذ�Χ�ˣ��������Ǿ������侯������ǹ"
                            "���Ż�����Ѫ�����ǣ���Ȼ�����Ǳ�����Ǳ�ڵ�ɥʬ�ˡ�С�������㣺���������������Ҫ��������������û�б���Ⱦ��"
                            "�ҿ�����ɽ�У����ǿ��Գ������������"<<endl;
                return;
            }
            else if(msg=="ashore")
            {
                pl.get_off_vehicle();
                cout<<"�侯��������Ѫ�������ǿ���ϰ���û�а취���۶��˰�����㱻��ɱ�ˡ���û�п�����ɽ���𣿣�"<<endl;
                this->stage=DIE;
                cout << info_end << endl;
                return;
            }
            else if(msg=="sing")
            {
                pl.get_off_vehicle();
                cout<<"�㳪���˸衣Զ����ѧУ��ɥʬ���У������������ɣ��ຼ������ɫ��ˮ����Ʈ�����������"
                            "�侯��������������ԥ��һ�����������ǹ��˵�������ﻹ���Ҵ��ߣ�ҽ����Ա������"
                            "���Ǳ�ȫ����װ���侯�ǳ���ȥ��ס�������Ȼ������Ȼ���Խ��ԽԶ��͸���������㿴����������Ժ��"
                            "�ϴ��ţ��㽭��ѧ�ĸ�����ϡ�ɼ������췢����һ�з·�����һ�㣬���˲������š�"<<endl;
                Player::delay();
                if(!partner_alive)//����һ���ӳ���
                {
                    cout<<"����Ȼ�ӳ����ˣ�����������Ȼ��ʧ�����ٴ�����ѧУ������������׵�С���������ƽ����"
                            "���������Լ����ں�ɥʬ��ս���б�����С����������߽�ҩ����ѡ��ҩ��С��Ҳ�����ں��׳��ߡ�"
                            "���ǣ�û����ô�����������ֻ����һ���ӳ�������ӭ�����Ͼ���������������ȴ��˯��������ĺ�ҹ..."<<endl;
                    this->stage=ALONE_SUC;
                    cout << info_end << endl;
                    return;
                }
                else//һ���ӳ�ȥ����ѽ�֣�
                {
                    cout<<"��תͷ����С������������ţ�Ҳ�����㣺˵�������������ӳ����ˣ���������Ц�ˣ���ҲЦ�ˡ�"
                            "������������ǵ��Ͼ�������"<<endl;
                    this->stage=SUC;
                    cout << info_end << endl;
                    return;
                }
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴�ܱ����\nashore: ֱ���ϰ�\nsing: ������侯����"<<endl;
                return;
            }
        }
    }
    //֧�ߵص㣨��ʱ��
    else if(pl.get_cur_pos()->get_name()=="east building")//���̣�ɥʬ��
    {
        if(msg=="look")
        {
            cout<<"�����Ƕ��̣�ԭ����ѧϰ�����ã�����ȴ����ɥʬ�ߣ������������׼����ɥʬ�������˼������"
                  "���Ǹ��������󣬶�����˵ɥʬ��ζ��Σ�գ����ǻ�������Ҳ��ζ��ս�����������������˵�����ܴ����������ѳ�Ǯ�����������ʡ�"
                  "������ú�������������״̬������ɥʬ��"<<endl;
            return;
        }
        else if(msg=="fight")
        {
            Zombie *z = NULL;
            vector<Zombie*> v_zom;
            
            //�������ɥʬ
            int res = rand() % 10;
            if(res<=1)//20%
                z = new Zombie;
            else if(res<=3)//20%
                z = new Roll_Zombie;
            else if(res<=5)//20%
                z = new Water_Zombie;
            else if(res<=7)//20%
                z = new Fire_Zombie;
            else if(res<=8)//10%
            {
                Zombie *z1 = new Zombie;
                Zombie *z2 = new Roll_Zombie;
                Zombie *z3 = new Fire_Zombie;
                v_zom.push_back(z1);
                v_zom.push_back(z2);
                v_zom.push_back(z3);
            }
            else if(res<=9)//10%
            {
                Zombie *z1 = new Zombie;
                Zombie *z2 = new Roll_Zombie;
                Zombie *z3 = new Water_Zombie;
                v_zom.push_back(z1);
                v_zom.push_back(z2);
                v_zom.push_back(z3);
            }

            if(z!=NULL)
            {
                cout << "��γ��ֵ���" << z->getname() << " !" << endl;
                switch(pl.fight(z))
                {
                    case 0:
                        this->stage=DIE;
                        cout << info_end << endl;
                        break;
                    case 1: 
                        cout<<"��Ͻ��ӻ��˶����ſ�"<<endl;
                        delete z;
                        break;
                    case 2:
                        //�ɹ����ɥʬ
                        cout << "��ɹ��������ֻɥʬ����Ҫ����ս����" << endl;
                        break;
                        delete z;
                }
            }
            else if(!v_zom.empty())
            {
                switch (pl.fight_many(v_zom))//fight many zombies
                {
                    case 0:
                        this->stage = DIE;
                        cout << info_end << endl;
                        break;
                    case 1:
                        cout << "�㷢���򲻹���ô��ɥʬ���Ǳ����ӻ��˶����ſ�" << endl;
                        break;;
                    case 2:
                        cout << "��ɹ��������һȺɥʬ����Ҫ����ս����" << endl;
                        break;
                }
                for (int i = 0; i < v_zom.size();i++)
                    delete v_zom[i];
            }
            else
                cout << "LOGIC ERROT: No zombie occurs!" << endl;
            return;
        }
        else if(msg=="return")
        {
            PLAYER_STAGE temp = pl.get_last_status();
            pl.move_to(pl.get_last_pos());
            pl.get_off_vehicle();
            pl.set_status(temp);
            return;
        }
        else if(msg=="hint")
        {
            cout << "look: �۲춫��ѧ���\nfight: ����ҵ�һֻɥʬ����֮��ս\nreturn: ����������ȥ" << endl;
            return;
        }
    }
    else if(pl.get_cur_pos()->get_name()=="library")//ҽѧͼ��ݣ����ʿ�
    {
        if(msg=="look")
        {
            cout << "����ԭ����ͼ��ݣ�ɥʬ���������������������ʿ⣬�ڷ��Ÿ��ָ�����������ʳ���Ҫ��Ǯ����" << endl;
            cout << "-------------ʳ����-------------" << endl;
            Bread b;
            b.show();
            cout << endl;
            Apple a;
            a.show();
            cout << endl;
            cout << "-------------������-------------" << endl;
            Fork f;
            f.show();
            cout << endl;
            Umbrella um;
            um.show();
            cout << endl;
            Knife kn;
            kn.show();
            cout << endl;
            Gun gun;
            gun.show();
            cout << endl;
            BloodSickle bs;
            bs.show();
            return;
        }
        else if((msg.find("pick")==0)&&msg.length()>=6)
        {
            string item = msg.substr(5, msg.length() - 5);
            if(!Food::isFood(item)&&!Weapon::isWeapon(item))
            {
                cout << "�����ڸ���Ʒ��" << endl;
                return;
            }
            if(!(item==global_bread_name||item==global_apple_name||
                item==global_fork_name||item==global_knife_name||item==global_umbrella_name||item==global_gun_name
                ||item==global_bloodsickle_name))
            {
                cout << "�޷������ﹺ�����Ʒ��" << endl;
                return;
            }
            this->pl.pick(item, BUY);
            return;
        }
        else if(msg=="return")
        {
            PLAYER_STAGE temp = pl.get_last_status();
            pl.move_to(pl.get_last_pos());
            pl.get_off_vehicle();
            pl.set_status(temp);
            return;
        }
        else if(msg=="hint")
        {
            cout << "look: �۲�ͼ������������\npick <����Ӣ����>: ����ĳ������\nreturn: ����������ȥ" << endl;
            return;
        }
    }
    cout << "�����ָ����Ч��(������help�鿴һ��Ϸ�ָ��, ����hint�鿴��ǰ������ʾ)" << endl; //����������������ʱ���ж������Ϊ�Ƿ�ָ��
}
//--------------------------------------------------------------------

bool Game::is_quit()const
{
    return this->stage==QUIT;
}

bool Game::is_end()const
{
    return this->stage == DIE || this->stage == ALONE_SUC || this->stage == SUC;
}

void Game::quit()//�˳���Ϸ
{
    cout<<"\n��Ϸ������лл���飡"<<endl;
}

//static function for code and decode string while doing save and load
void Game::code_str(string &str)
{
    for(int i =0;i<str.size();i++)
    {
        if(str[i]==' ')
        {
            str[i]='@';
        }
    }
}

void Game::decode_str(string &str)
{
    for(int i =0;i<str.size();i++)
    {
        if(str[i]=='@')
        {
            str[i]=' ';
        }
    }
}
