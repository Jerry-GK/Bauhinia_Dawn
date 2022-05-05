#include "game.h"

void Game::Init()
{
    show_welcome();
    this->stage=PLAYING;
    //init positions in game map
    Position p;
    p.set("dormitory",0,0);//����
    p.add_status(DOR_TO_LOOK_OUTSIDE);
    //
    game_map.add_pos(p);
    
    p.set("shop",0,0);//����
    p.add_status(SHOP_SEARCH);
    //
    game_map.add_pos(p);

    p.set("dor gate",0,0);//�����ſ�
    p.add_status(GATE_FIGHT);
    //
    game_map.add_pos(p);

    p.set("west building",0,0);//����
    p.add_status(WEST_INTO_BUILDING);
    //
    game_map.add_pos(p);

    p.set("bio lab",0,0);//����ʵ����
    p.add_status(BIO_INTO_BUILDING);
    //
    game_map.add_pos(p);
    
    p.set("roof",0,0);//ԭ��Ժ¥��
    p.add_status(ROOF_HALL);
    //
    game_map.add_pos(p);

    p.set("wharf",0,0);//ˮ����ͷ
    p.add_status(WHARF_DECIDE);
    //
    game_map.add_pos(p);

    p.set("lake",0,0);//�����
    p.add_status(LAKE_ROW);
    //
    game_map.add_pos(p);

    p.set("south gate",0,0);//���ų���
    p.add_status(SOUTH_END);
    //
    game_map.add_pos(p);

    //init player
}

void Game::read()
{
    cout<<"\nPlease enter: ";
    getline(cin,input_box);
    submit();
}

void Game::submit()//�ӶԻ����ȡ���������ı���input_box->msg, clear input_box, call process��
{
    msg=input_box;
    input_box.clear();
    process(msg);
}

//--------------------------Process-----------------------------------
void Game::process(string msg)//����pos������msg�ı�,��ؼ��Ĳ��֣����ݵص㣬���ֳ�С״̬
{
    //������Ϸ
    if(msg=="quit")
    {
        this->stage=QUIT;
        return;
    }
    if(pl.get_status()==UNKNOWN)
    {
        if(msg=="begin")
        {
            show_info(info_wake_up);    
            pl.move_to(game_map.get_pos("dormitory"));
            return;
        }
        else
        {
            cout<<"������begin��ʼ��Ϸ��"<<endl;
            return;
        }
    }
    //�κγ����¶���ִ�е�ָ��
    if(msg=="help")
    {
        show_info(info_help);
        return;
    }
    else if(msg=="map")
    {
        this->game_map.show();
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
    else if((msg.find("sudo goto")==0)&&msg.length()>=11)
    {
        this->pl.move_to(game_map.get_pos(msg.substr(10, msg.length()-10)));
        return;
    }
    else if((msg.find("sudo pick")==0)&&msg.length()>=11)
    {
        this->pl.pick(msg.substr(10, msg.length()-10));
        return;
    }
    else if((msg.find("sudo take")==0)&&msg.length()>=11)
    {
        Vehicle* v = new Vehicle(msg.substr(10, msg.length()-10));
        this->pl.take_vehicle(v);
        return;
    }
    //���κγ���֮�¶���ִ�е�ָ��
    else if(pl.get_pos()->get_name()=="dormitory")//Scene 1: Dormitory
    {
        if(pl.get_status()==DOR_TO_LOOK_OUTSIDE)
        {
            if(msg=="look")
            {
                show_info(info_look_outside);
                pl.set_status(DOR_TO_CHOOSE);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"����look����۲����"<<endl;
                return;
            }
        }
        else if(pl.get_status()==DOR_TO_CHOOSE)
        {
            if(msg=="look")
            {
                show_info(info_look_around);
                return;
            }
            else if(msg=="pick fork")
            {
                pl.pick("fork");
                return;
            }
            else if(msg=="pick umbrella")
            {
                pl.pick("umbrella");
                return;
            }
            else if(msg=="goto shop")
            {
                pl.move_to(game_map.get_pos("shop"));
                show_info(info_to_shop);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look:�۲�����\npick forkʰȡ�²�\npick umbrellaʰȡ��ɡ\ngoto shopǰ����������"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="shop")//Scene 2: shop
    {
        if(pl.get_status()==SHOP_SEARCH)
        {
            if(msg=="look")
            {
                show_info(info_look_shop);
                return;
            }
            else if(msg=="pick bread")
            {
                pl.pick("bread");
                return;
            }
            else if(msg=="pick knife")
            {
                pl.pick("knife");
                return;
            }
            else if(msg=="ask")
            {
                show_info(info_saleman);
                return;
            }
            else if(msg=="goto dor gate")
            {
                pl.move_to(game_map.get_pos("dor gate"));
                show_info(info_to_gate);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look:�鿴�������\npick bread:ʰȡ���\nask:ѯ���ջ�Ա���\n"
                "use bread:���ԳԵ�һ��ʰȡ�������������\n"
                "pick knife: ����һ��С��\ngoto dor gate:����ȥѧ԰�ſڣ�������������ѯ�ʺ���ȥ��"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="dor gate")//Scene 3: Gate of the dormitory, beside the road
    {
        Zombie* z;
        z=new Zombie("water");
        if(pl.get_status()==GATE_FIGHT)
        {
            if(msg=="look")
            {
                z->show();
                return;
            }
            else if(msg=="escape")
            {
                pl.move_to(game_map.get_pos("shop"));
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
                        break;
                    case 1: 
                        pl.move_to(game_map.get_pos("shop"));
                        cout<<"���Ǳ����ӻ��˽�������,����ɥʬû��׷�������������ǵ�׼�������ʲ�����ɥʬ��ս��"<<endl;
                        delete z;
                        break;
                    case 2:
                        pl.set_status(GATE_AFTER_FIGHT);
                        show_info(info_fight_suc);
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
        if(pl.get_status()==GATE_AFTER_FIGHT)
        {
            if(msg=="look")
            {
                cout<<"�������ܿ��˿�������ֻ��һЩ��������Ĺ�������һ�������ŵ�С�꣬��ͣ��·�Ե�һЩ���ų��ŵ�˽�ҳ���"<<endl;
                return;
            }
            else if(msg=="take bike")
            {
                Vehicle* v= new Vehicle("bike");
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take e-bike")
            {   
                Vehicle* v= new Vehicle("e-bike");
                pl.take_vehicle(v);
                return;               
            }
            else if(msg=="take car")
            {
                cout<<"��û�г�Կ��,�޷�����˽�ҳ���"<<endl;
                return;
            }
            else if(msg=="goto west building")
            {
                pl.move_to(game_map.get_pos("west building"));
                pl.get_off_vehicle();
                show_info(info_goto_west);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴��·���\ntake bike: �������г�\ntake e-bike:����С��\ntake car: ������\n"
                "goto west building: ȥ����"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="west building")//Scene 4: West teaching building
    {
        if(pl.get_status()==WEST_INTO_BUILDING)
        {
            if(msg=="look")
            {
                cout<<"���̵�һ¥���������Ѫ���Ͳ�֫���鲼�Ĵ�������Ż�¡�¥�ϴ�������ɥʬ��˻����������ɥʬ�ƺ��հ�����ɨ��һ�ա�"
                        "������ǽ����ʾ����ռ���ʵĴ�����0%��0%��0%...�������˶��������������˾�����ͻȻ�㿴����һ���֣���1-404��ռ����1%"
                        "���ͬʱ��������¥�����˺�����������������ʮ�ּ�����ԭ�������Լ����������Ҵ��ߣ���������¥��ɥʬ����˻����"
                        "��������ԥ..."<<endl;
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
        else if(pl.get_status()==WEST_MEET)
        {
            if(msg=="look")
            {
                cout<<"��ǰ�����Ů����������ʮ�����������£���������˵�ѡ��ſ���ɥʬ���ⲽ����"<<endl;
                return;
            }
            else if(msg=="give bread")
            {
                cout<<"�������ݸ����������������С������æ��л��˵�����ҽ�С��������Ҵ��ߣ�Ҫ��ֻʣ��һ�������治֪������ô�졣"
                        "�����������ڽ��ҵ���Ҳ���ǰ취������취�������ӳ�ȥ������̾��̾����˵��û�취��ѧУ������"
                        "���ڵı������Ѿ���ɥʬ��Ⱦ�ˣ��ſھۼ��˴���û�������ɥʬ�����ǳ���ȥ�ġ�"
                        "��˵����Ȼ���������Ǳ������һ��ɥʬ���������������ˡ�"<<endl;
                pl.drop("bread");
                return;
            }
            else if(msg=="leave")
            {
                cout<<"�����С���߳����ң���ҪѰ����������ɥʬ�ƺ���ͬ��..."<<endl;
                pl.set_status(WEST_FIGHT);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴�������\ngive bread: �����������������˵��������˵Щʲô\nleave: �߳�����Ѱ������"<<endl;
                return;
            }
        }
        else if(pl.get_status()==WEST_FIGHT)
        {
            Zombie* z=new Zombie("roll");
            if(msg=="look")
            {
                cout<<"һֻɥʬ��������һ���飬�������������ˣ��Ǿ���ɥʬ��"<<endl;
                return;
            }
            else if(msg=="fight")
            {   
                pl.fight(z);
                pl.set_status(WEST_CHECK);
                cout<<"�Ѿ��˾�ţ����֮����������˾���ɥʬ����������¡����ŵ�����ǰ��ɥʬ�����С�������˼"<<endl;
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
        else if(pl.get_status()==WEST_CHECK)
        {
            if(msg=="look")
            {
                cout<<"��ǰ��ɥʬ˫ĿԲ����ͷ�����࣬���ݡ���ͷȫ����˯}�˵���ɫ��С�����Ա�˵���������������ɥʬ����������ϲ�,Ҫ��Ҫ�����һ���أ�"<<endl;
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
            else if(msg=="take bike")
            {
                Vehicle* v= new Vehicle("bike");
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take e-bike")
            {   
                Vehicle* v= new Vehicle("bike");
                pl.take_vehicle(v);
                return;               
            }
            else if(msg=="goto bio lab")
            {
                pl.move_to(game_map.get_pos("bio lab"));
                pl.get_off_vehicle();
                cout<<"���С��һ������������ʵ����"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴��ȥ��ɥʬ���\nsearch:���ɥʬ\ntake bike:����¥�£������г�\n"
                    "take e-bike:����¥�£���С��\ngoto bio lab: ǰ������ʵ����(�����ȳ�����ͨ����)"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="bio lab")//Scene 5: Biology laboratory
    {
        if(pl.get_status()==BIO_INTO_BUILDING)
        {
            if(msg=="look")
            {
                cout<<"����ʵ�������Ͻ�۶�����һ����¥�С��ע�⵽�����ſڲ�û�п�����ֻɥʬ�����ǵ���ȴ���������������ɥʬ��Ѫ��ӡ��������֡�"
                        "���ó�ɥʬ���ֻ����Ա������¼��û�����ĵ�ʦ�������������������ʵ���ҵ���������..."<<endl;
                return;
            }
            else if(msg=="go in")
            {
                cout<<"���ƿ�������ʵ���ҵ��ţ���ǰ�ľ�������ʮ������..."<<endl;
                pl.set_status(BIO_MEET);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴�ſ����\ngo in: ��������ʵ����"<<endl;
                return;
            }
        }
        else if(pl.get_status()==BIO_MEET)
        {
            if(msg=="look")
            {
                cout<<"��ǰ��һλ������ڣ����Ÿɾ�����Ȼû�б�ɥʬ��Ⱦ��ʵ���ҵ������ϣ��ڷ������װ������Լ����ӣ���ͷ��С"
                      "�к�ɫ�ģ�����ɫ�ģ�����С��С���ʵ���Ҫ��Ҫ��һ����ʲô����أ�"<<endl;
                return;
            }
            else if(msg=="ask")
            {
                cout<<"�������ӽ���˵�Լ���Ҷ��������ѧԺ�Ľ��ڣ������ѧ����ʵ���������⣬û�뵽����ʱ���Ѿ������ɥʬ������֪����ô����"
                        "��æ�������������⣬�Լ�Ҳһֱ���ҳ�ȥ��һֱ����ʵ�������з���ҩ�������룺��ҩ���ò�������Щ�������̵Ĺ��Ӱɣ�"
                        "������˵��������Ӧ��Ҳ���ȥ�ɣ���ϧ����ѧУ���ڶ���ɥʬ���أ��ҽ�������ȥ�ɹ���ѧԺ¥���������������Ա���ߵ��Ǹ�����"
                        "����¥����ȥ��һ����������Ұ�ã����Կ�����û�г�·���������������Ҳ�ǱȽ����׷��ֵġ�С��ܼ�����ȷʵ�Ǹ������⣡"
                        "��Ҳ������һ��ȥ�ɡ�Ҷ�������ε�Ц��Ц��˵�����ˣ����ˡ���ȥ��������������һ����з���ҩ�ɣ�˵�������ܽ�ȸ�Ⱦ��ͬѧ��"
                        "Ŷ���ˣ�����ͦԶ�ģ��ҵĳ�ͣ��¥���ˣ�����Ҫ�ÿ��Կ���˵�궪��������һ����Կ�ס�"
                        "�㿴�˿���ǰ��Ҷ���ڣ�������˵��ȷʵ�е������ܸо�����ֵֹġ����ˣ�������ȥ�����ɡ�"<<endl;
                return;
            }
            else if(msg=="pick red tube")
            {
                pl.pick("red tube");
                return;
            }
            else if(msg=="pick green tube")
            {
                pl.pick("green tube");
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
                cout<<"look: ���ʵ�������\nask: ѯ�ʽ������\npick red tube: ͵͵���ߺ�ɫ�Թ�\npick green tube: ͵͵������ɫ�Թ�\n"
                        "leave: �뿪ʵ����"<<endl;
                return;
            }
        }
        else if(pl.get_status()==BIO_LEAVE)
        {
            if(msg=="look")
            {
                cout<<"¥�£���ɢ��ͣ�����г���С�꣬�����Ա�Ҷ���ڵ�˽�ҳ�����ȥ��Ժ̫����������������Ҳ��̫����Ҷ���ڡ�"<<endl;
                return;
            }
            else if(msg=="take e-bike")
            {
                cout<<"С��û���ˣ�"<<endl;
                return;
            }
            else if(msg=="take bike")
            {
                Vehicle* v= new Vehicle("bike");
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take car")
            {
                Vehicle*v =new Vehicle("car");
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="goto roof")
            {
                pl.move_to(game_map.get_pos("roof"));
                pl.get_off_vehicle();
                cout<<"���С�������Ժһ·�����ɹ�Ժ¥����������¥����һ·�ϣ��������������µ�ɥʬ��������ǰ�ȫ�������ⶰ�߸߽�����һ¥������"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: ���·�����\ntake bike: �������г�(������Ŀ�ĵ��е�Զ)\ntake e-bike: ��С��\n"
                        "take car: ��Ҷ���ڵ�˽�ҳ�\ngoto roof: ǰ���ɹ�Ժ¥��"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="roof")//Scene 6: The roof of the old management college
    {
        if(pl.get_status()==ROOF_HALL)
        {
            if(msg=="look")
            {
                cout<<"���������ȥ���������ˡ����������м��ҵĴ򶷺ۼ���Ѫ�������׵������ǣ����ϻ���һֻ���֣������������һ��ǹ��"
                        "�������﷢������ս������ֵ������������ƺ���û��ɥʬ�Ķ�����С��˵��Ҫ�������������ݵ�¥�������ɣ�"
                        "����Ҷ����˵�ģ�������Ұ�ã��ܿ����ĸ�����ɥʬ�١��л����ӳ�ȥ��";
                return;
            }
            else if(msg=="pick gun")
            {
                pl.pick("gun");
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
                cout<<"look: �鿴�������\npick gun: ��������е�ǹ\ngo up: ������ȥ¥��"<<endl;
                return;
            }
        }
        else if(pl.get_status()==ROOF_TOP)
        {
            if(msg=="look")
            {
                cout<<"���С�������˾ɹ�Ժ��¥������������������ߵ㣬��Ұ��Ϊ������������Զ����ȥ�����ȫòһ�����ࡣ"
                        "���Կ���ѧУ������ɢ���ż����ꤵ�ɥʬ������۹�Ͷ�򶫶��ţ��������ϣ�ȫ��ɥʬ��УҽԺ���š��������Ҳ�ǡ�"
                        "��ת��ͷ������Ķ����š��������½����ϴ����ſ�Ҳ��Χ����ɥʬ��������У���ӳ�û���κ�ϣ���ˣ����С�������˾�����"
                        "�㶢���������ͻȻ��ǰһ�����������֧���������������Ϸ���ȥ�������ϻ�԰��С���ƺ�����������뷨"
                        "æ˵������˵˳����������ϻ�԰������һ�����ص�ˮ·������ͨ��ѧУ�ϱߵ��ຼ���ӣ�Ҳ����˵�����ǿ���ͨ��ˮ·��У��"
                        "����ϲ�����侲������˵�����ǣ�������ô��ˮ·�����أ�������û�д���С�������룬˵����ˮ����ͷ��������ѧУ�����"
                        "ˮ���˶��ε��Ͽεص㣬��ǡ���Ϲ������������Ƥ��ͧ��"<<endl;
                return;
            }
            else if(msg=="leave")
            {
                pl.set_status(ROOF_LEAVE);
                cout<<"���С��׼���뿪��¥������ǰ��ˮ����ͷ������ȷ������һ˿���Ծ�..."<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �����������۲�ѧУ���\nleave: ׼���뿪��¥������ǰ�������"<<endl;   
                return;
            }
        }
        else if(pl.get_status()==ROOF_LEAVE)
        {
            if(msg=="look")
            {
                cout<<"��ʱ��¥�ĵ��ݺ����ˣ�¥�ݴ������ӵ�����������ϸһ�����ƺ���ɥʬ�����������С��æ�ܻ�¥�����¿���"
                        "��ǰ�ľ�����������˸�������¥�£���Ⱥ��ɥʬ��ӿ���¥��¥���ɥʬ�ĽŲ���Խ��Խ��..."
                        "��ô����������Զ�������Ȼ��������һ����Ϥ���ˣ�������¥�µĻ�̳�ԣ����ݲ��ȵ�Ц�ţ�ɥʬ��Ҳ��ȥ��������"
                        "��������Ȼ��Ҷ���ڣ�"<<endl;
                return;
            }
            else if(msg=="ask")
            {
                cout<<"���ɻ���ַ�ŭ�ش�����Ҷ����������ô���¡�Ҷ����а���Ц�ˣ�˵����ʵɥʬ���������������з������ģ�������Ⱦ����ʵ���ҵ�ѧ��"
                        "��Ϊ��һ��ʵ���������ֻ��һ���Ͼ͸�Ⱦ��ȫѧУ�������ǣ���Ŀǰ�ҷ��ֵĽ�����Ҵ��ߡ���������ʹ����������������ܿ���"
                        "ɥʬ��������������׷ɱ���ǡ������������ĵط�����ɣ���������ô�ӣ�"<<endl;
                return;
            }
            else if(msg=="jump")
            {
                pl.move_to(game_map.get_pos("wharf"));
                pl.recoverHP(-20);
                cout<<"You jump�� I jump�����С��һ����������������޴�ĳ���������ǲ��ɥ�����ý�ʣ��һ������ƴ���ε���ˮ����ͷ��"<<endl;
                return;
            }
            else if(msg=="fight")
            {
                cout<<"û��õĶ���ս���߼�����ȥ��¥��"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴��Χ���\nask: ����Ҷ����\njump: ����С���¥���������������Σ�գ�������ȥˮ����ͷ\nfight: ��ɥʬӲ�գ�ɱ��ȥ"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="wharf")
    {
        if(pl.get_status()==WHARF_DECIDE)
        {
            if(msg=="look")
            {
                cout<<"���ǽ�ƣ���ߵ������ˣ�ˮ����ͷ���������ﴬֻȷʵ���٣����м������ʵ�ƻ����С������һ�ҿ������Ƚ��µĴ���"
                        "Զ����Ҷ�����ں��԰������ܻ����������򲨹����Ե�ˮ�棬�������������������ƺ�������ʲôΣ����׼��������"<<endl;
                return;
            }
            else if(msg=="pick apple")
            {
                pl.pick("apple");
                return;
            }
            else if(msg=="take boat")
            {
                Vehicle* v=new Vehicle("boat");
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
                cout<<"���С�������Ƥ��ͧ�����������ţ�׼��ȥ�������..."<<endl;
                pl.move_to(game_map.get_pos("lake"));
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴��ͷ���\npick apple: ����ƻ��\ntake boat: �˴�\nrow: ����ȥ����\n(������use bread����ղ���¥��ʧ������)"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="lake")
    {
        if(pl.get_status()==LAKE_ROW)
        {
            if(msg=="look")
            {
                cout<<"�����ڴ����Ĵ�����������Ҷ�����Ѿ������ˣ���Զ���ľɹ�Ժ¥���ϣ�Ҳ�������Ǹո��ڵĵط����Ѿ�������ɥʬ��"
                        "С�������Աߣ����˿�����˵����������ʱ��ȫ�ˣ���磬������á���һ��Ҫ���ų�ȥ���ҵİְ����裨һ����ǰɿ�飩��"
                        "��Ҳ���������������룬������Ҫ����������ຼ���ӣ��Ͱ�ȫ�ˣ�"<<endl;
                return;
            }
            else if(msg=="goto south gate")
            {
                pl.set_status(LAKE_FIGHT);
                cout<<"���Ǿ�������ȥ�ϴ����Ե�ˮ�����������ӳ�ȥ��������ǰ�ľ���������һ��..."<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴���������\ngoto south gate: ׼�������ϴ���"<<endl;
                return;
            }
        }
        else if(pl.get_status()==LAKE_FIGHT)
        {
            if(msg=="look")
            {
                cout<<"��Ҫ��ʻ���ϱߣ���Ҫ���������ţ����Ƕ���һ�����Ŷ��ﾹȻ�ε��ż�ֻ���µ�ɥʬ����ˮɥʬ��"
                    "����ϸһ����ˮɥʬ�ſ��}�˵���ɫ��ͣ������˷��Ƶ��������ι�������Ⱥˮɥʬ��������Ӿ�����ҿ������������ͣ�"<<endl;
                return;
            }
            else if(msg=="escape")
            {
                pl.move_to(game_map.get_pos("wharf"));
                cout<<"���С��Ͻ���ͷ�����ٻ��򰶱ߣ��ӻ�ˮ����ͷ��"<<endl;
                return;
            }
            else if(msg=="fight")
            {
                Zombie* z=new Zombie("water");
                pl.fight(z);
                //����ɹ����ˮɥʬ
                cout<<"����һ����ս����������һ�������ˮɥʬ�������Աߵ�С��ȴ���Ÿ첲����Щ���Ծ�..."<<endl;
                pl.set_status(LAKE_SAVE);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴ˮɥʬ���\nfight: ��ˮɥʬս����ͻ�Ʒ���\nescape: ��ͷ�ӻ�ˮ����ͷ"<<endl;
                return;
            }
        }
        else if(pl.get_status()==LAKE_SAVE)
        {
            if(msg=="look")
            {
                cout<<"�㿴��С��������ĸ첲������һ����������ɫ�˿ڣ����ˣ��ղŵ�ս����С�ﱻˮɥʬҧ���ˣ�"
                        "С���������������۽����£�����������ԭ��ˮ�������۾���ʼ���ף����������ӣ����ͻ���ɥʬ��"
                        "��������˵�����Բ������������ˣ������Ҳ��������ӳ�ȥ�ˣ���ɽ�п���û���������´��ɣ�����..."
                        "������һƬ�հף��������ںޣ��ղ�û�б�����С��������취�����ͻ���Լ�Ҳҧ�ˡ�"
                        "���㿴������ʵ�ڲ����Ľ������´���������Զ��˯��������ס������ѵ����û��ʲô�취����"
                        "ͻȻ���뵽������ʵ���������Щ�������̵�ƿ�Ӻ�Ҷ���ڵĻ����᲻���н�ҩ�����ǣ����ǣ�Ҷ�����ǻ��˰���"
                        "����Ļ��з���ҩ�𣿾���ᣬ�ǵ��׺�ɫ�Լ��ǽ�ҩ������ɫ�Լ����أ�����ô��ˣ�˵��һ���������ϱ��ɥʬ��"
                        "���Լ�ҧ���������Լ���ʱ��û��˳��һƿ�����ǵ��ˣ���һ�±�������һ�°ɣ�"<<endl;
                return;
            }
            else if(msg=="push")
            {
                cout<<"��һ���ģ��͵ذ�С��������ȥ���㿴����������һ��һ��������ȥ����������ˮ�ף����㣬����һ�ˣ���������..."<<endl;
                this->stage=PARTNER_DIE;
                pl.move_to(game_map.get_pos("south gate"));
                return;
            }
            else if(msg=="give red tube")
            {
                if(!pl.have("red tube"))
                {
                    cout<<"��֮ǰ������ʵ���Ҳ�û�����ߺ�ɫ�Լ�"<<endl;
                    return;
                }
                pl.drop("red tube");
                cout<<"С����º�ɫ�Լ���������ɫ����Ѫ�Ƶģ�Ч����Ȼ�ܺá�С����˿��漣��������ˣ�����Ҳ�𽥻ظ�ƽ����"
                        "���ſ�˫�ۣ�˵����лл������ң������룺��Ҷ������Ȼ�������£���������һ�֣����н�ҩ��˵����"
                        "���Է���һ�Լ���Ⱦ���õģ����õ�ʱ�Լ����顢������һƿ������С�ﰲȫ�ˣ�����������һ������"
                        "����һ������ص�ˮ·��������"<<endl;
                pl.move_to(game_map.get_pos("south gate"));
                return;
            }
            else if(msg=="give green tube")
            {
                if(!pl.have("green tube"))
                {
                    cout<<"��֮ǰ������ʵ���Ҳ�û��������ɫ�Լ�"<<endl;
                    return;
                }
                pl.drop("green tube");
                cout<<"С�������ɫ�Լ���ͻȻ˫Ŀ��ף��˿ڶ񻯣�ȫ��鴤����ͻȻ��ʶ������Ҷ���ڷ�����ɥʬ����ҩ������������ʹѧ�����¡������˵�һ��ɥʬ"
                        "����һ�ж��Ѿ����ˣ�С��˲�����˿��µ�ɥʬ��һ�ڰ���ҧס����Ҳ�����ɥʬ������������������"<<endl;
                this->stage=DIE;
                return;
            }
            else if(msg=="goto south gate")
            {
                cout<<"���˵�С�����ڴ����棬ʹ�ý�ҩ������������������ţ�˵��һ�������������ҵ��������㻮�������Ϳ쵽�ˡ�"
                        "�㿴�����ຼ���ӵ���ڣ������˰�ѧУ���ذ�Χ���侯���㿴����ϣ����ͻȻ���㱳��һʹ���㾪㵵ػ�ͷһ����"
                        "С����ҧ����ļ���˿�������ɫ��Һ�塣�����۾��Ѿ���ȫ�����ˣ���������һ���ᣬ������������˵���ԣ��Բ���..."
                        "������߿�ʼģ������֫�����������գ�Ҳ�����˴��ϣ������ɥʬ...����������������";
                this->stage=DIE;
                return;
            }
            //use red/green tube��ȫ����
            else if(msg=="hint")
            {
                cout<<"look: ���С�����\npush: ��С�����´�\ngive red tube: ��С�����Ѫ��ɫ�Լ�\ngive green tube: ��С���������ɫ�Լ�\n"
                       "goto south gate: ǿ�д��ű�ҧ�˵�С���������\n(����������bag��һ�±�������ʲôҩ��)"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="south gate")
    {
        if(pl.get_status()==SOUTH_END)
        {
            if(msg=="look")
            {
                cout<<"˳����������ˮ·��Ȼ�������ϴ����Աߵ��ຼ���ӡ����������Ǹ���ѧУ������һ���ӣ���ˮ�����ֳ󣬿�����ȴʮ������";
                if(this->stage==PARTNER_DIE)//С���Ѿ�����
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
                cout<<"�侯��������Ѫ��������ϰ���û�а취���۶��˰�����㱻��ɱ�ˡ���û�п�����ɽ���𣿣�"<<endl;
                this->stage=DIE;
                return;
            }
            else if(msg=="sing")
            {
                pl.get_off_vehicle();
                cout<<"�㳪���˸衣Զ����ѧУ��ɥʬ���У������������ɣ��ຼ������ɫ��ˮ����Ʈ�����������"
                            "�侯��������������ԥ��һ�����������ǹ��˵�������ﻹ���Ҵ��ߣ�ҽ����Ա������"
                            "���Ǳ�ȫ����װ���侯�ǳ���ȥ��ס�������Ȼ������Ȼ���Խ��ԽԶ��͸���������㿴����������Ժ��"
                            "�ϴ��ţ��㽭��ѧ�ĸ�����ϡ�ɼ������췢����һ�з·�����һ�㣬���˲������š�";
                if(this->stage==PARTNER_DIE)//����һ���ӳ���
                {
                    cout<<"����Ȼ�ӳ����ˣ�����������Ȼ��ʧ�����ٴ�����ѧУ������������׵�С���������ƽ����"
                            "���������Լ����ں�ɥʬ��ս���б�����С����������߽�ҩ����ѡ��ҩ��С��Ҳ�����ں��׳��ߡ�"
                            "���ǣ�û����ô�����������ֻ����һ���ӳ�������ӭ�����Ͼ���������������ȴ��˯��������ĺ�ҹ..."<<endl;
                    this->stage=ALONE_SUC;
                    return;
                }
                else//һ���ӳ�ȥ����ѽ�֣�
                {
                    cout<<"��תͷ����С������������ţ�Ҳ�����㣺˵�������������ӳ����ˣ���������Ц�ˣ���ҲЦ�ˡ�"
                            "������������ǵ��Ͼ�������"<<endl;
                    this->stage=SUC;
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
    show_info(info_invalid);//����������������ʱ���ж������Ϊ�Ƿ�ָ��
}
//--------------------------------------------------------------------

bool Game::is_end()const
{
    return this->stage==DIE||this->stage==ALONE_SUC||this->stage==SUC||this->stage==QUIT;
}

void Game::quit()//�˳���Ϸ
{
    cout<<"\n��Ϸ������лл���飡"<<endl;
}