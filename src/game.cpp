#include "game.h"

void Game::Init()
{
    show_welcome();
    //init positions in game map
    Position p;
    p.set("dorm",0,0);//����
    p.add_status(DOR_WAKE_UP);
    //
    game_map.add_pos(p);
    
    p.set("Market",0,0);//����
    p.add_status(MARKET_SEARCH);
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
    p.add_status(UNKNOWN);
    //
    game_map.add_pos(p);

    p.set("wharf",0,0);//ˮ����ͷ
    p.add_status(UNKNOWN);
    //
    game_map.add_pos(p);

    p.set("lake",0,0);//�����
    p.add_status(UNKNOWN);
    //
    game_map.add_pos(p);

    p.set("south gate",0,0);//���ų���
    p.add_status(UNKNOWN);
    //
    game_map.add_pos(p);

    //init player
    pl.move_to(game_map.get_pos("dorm"));
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
    //cout<<pl.get_pos()->get_name()<<endl;
    //�κγ����¶���ִ�е�ָ��
    if(msg=="-help")
    {
        show_info(info_help);
        return;
    }
    else if(msg=="quit")
    {
        this->stage=END;
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
    else if(msg.find("use")==0)
    {
        this->pl.use(msg.substr(4,msg.length()-4));
        return;
    }
    else if(msg.find("drop")==0)
    {
        this->pl.drop(msg.substr(5,msg.length()-5));
        return;
    }

    //���κγ���֮�¶���ִ�е�ָ��
    else if(pl.get_pos()->get_name()=="dorm")//Scene 1: Dormitory
    {
        if(pl.get_status()==DOR_WAKE_UP)
        {
            if(msg=="begin")
            {
                show_info(info_wake_up);    
                pl.set_status(DOR_TO_LOOK_OUTSIDE);
                return;
            }
            if(msg=="hint")
            {
                cout<<"����begin��ʼ��Ϸ"<<endl;
                return;
            }
        }
        else if(pl.get_status()==DOR_TO_LOOK_OUTSIDE)
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
            else if(msg=="goto market")
            {
                pl.move_to(game_map.get_pos("Market"));
                show_info(info_to_market);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look:�۲�����\npick forkʰȡ�²�\npick umbrellaʰȡ��ɡ\ngoto marketǰ����������"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="Market")//Scene 2: Market
    {
        if(pl.get_status()==MARKET_SEARCH)
        {
            if(msg=="look")
            {
                show_info(info_look_market);
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
            else if(msg=="goto gate")
            {
                pl.move_to(game_map.get_pos("dor gate"));
                show_info(info_to_gate);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look:�鿴�������\npick bread:ʰȡ���\nask:ѯ���ջ�Ա���\n"
                "use bread:���ԳԵ�һ��ʰȡ�������������\n"
                "pick knife: ����һ��С��\ngoto gate:����ȥѧ԰�ſڣ�������������ѯ�ʺ���ȥ��"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="dor gate")//Scene 3: Gate of the dormitory, beside the road
    {
        Zombie* z;
        z=new Zombie;
        if(pl.get_status()==GATE_FIGHT)
        {
            if(msg=="look")
            {
                z->show();
                return;
            }
            else if(msg=="escape")
            {
                pl.move_to(game_map.get_pos("Market"));
                cout<<"���Ǳ����ӻ��˽�������,����ɥʬû��׷�������������ǵ�׼�������ʲ�����ɥʬ��ս��"<<endl;
                delete z;
                return;
            }
            else if(msg=="fight")
            {
                //ս���߼�
                pl.fight(z);
                pl.set_status(GATE_AFTER_FIGHT);
                show_info(info_fight_suc);
                delete z;
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
                Vehicle* v= new Vehicle("���г�",20,0);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take e-bike")
            {   
                Vehicle* v= new Vehicle("С��",30,0);
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
            else if(msg=="get off")
            {
                pl.get_off_vehicle();
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: �鿴��·���\ntake bike: �������г�\ntake e-bike:����С��\ntake car: ������\n"
                "get off: �뿪��ͨ����\ngoto west building: ȥ����"<<endl;
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
            Zombie* z=new Roll_Zombie();
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
                cout<<"��ǰ��ɥʬ˫ĿԲ����ͷ�����ࡣС�����Ա�˵���������������ɥʬ����������ϲ�,Ҫ��Ҫ�����һ���أ�"<<endl;
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
                Vehicle* v= new Vehicle("���г�",20,0);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take e-bike")
            {   
                Vehicle* v= new Vehicle("С��",30,0);
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
                Vehicle* v= new Vehicle("���г�",20,0);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take car")
            {
                Vehicle*v =new Vehicle("˽�ҳ�",50,0);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="get off")
            {
                pl.get_off_vehicle();
                return;
            }
            else if(msg=="goto roof")
            {
                pl.move_to(game_map.get_pos("roof"));
                pl.get_off_vehicle();
                cout<<"���С�������˹�Ժ���ƺ�ûʲôɥʬ��������������¥��"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: ���·�����\ntake bike: �������г�(������Ŀ�ĵ��е�Զ)\ntake e-bike: ��С��\n"
                        "take car: ��Ҷ���ڵ�˽�ҳ�\nget off: �뿪��ͨ����\ngoto roof: ǰ���ɹ�Ժ¥��"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="roof")//Scene 6: The roof of the old 
    {

    }
    else if(pl.get_pos()->get_name()=="wharf")
    {

    }
    else if(pl.get_pos()->get_name()=="lake")
    {

    }
    else if(pl.get_pos()->get_name()=="south gate")
    {

    }
    show_info(info_invalid);
}
//--------------------------------------------------------------------

void Game::show_prompt(string prompt)const//������ʾ��Ϣ
{
    show_info(prompt);
}

bool Game::is_end()const
{
    return this->stage==END;
}

void Game::quit()//�˳���Ϸ
{
    this->stage=END;
    show_bye();
}