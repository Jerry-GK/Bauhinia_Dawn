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
    p.add_status(UNKNOWN);
    //
    game_map.add_pos(p);

    p.set("bio lab",0,0);//����ʵ����
    p.add_status(UNKNOWN);
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
        this->pl.use(msg.substr(3,msg.length()-3));
        return;
    }
    else if(msg.find("drop")==0)
    {
        this->pl.drop(msg.substr(3,msg.length()-4));
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
                show_info("�²���ʰȡ��");
                return;
            }
            else if(msg=="pick umbrella")
            {
                pl.pick("umbrella");
                show_info("��ɡ��ʰȡ��");
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
                Vehicle* v= new Vehicle("���г�",20,10);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take e-bike")
            {   
                Vehicle* v= new Vehicle("С��",30,10);
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

    }
    else if(pl.get_pos()->get_name()=="biolab")//Scene 5: Biology laboratory
    {

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