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
    p.add_status(UNKNOWN);
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
    pl.set_pos(game_map.get_pos("dorm"));
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

    //���κγ���֮�¶���ִ�е�ָ��
    else if(pl.get_pos()->get_name()=="dorm")
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
                pl.set_pos(game_map.get_pos("Market"));
                show_info(info_to_market);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"����look�۲����ᣬ����pick forkʰȡ�²棬����pick umbrellaʰȡ��ɡ������goto marketǰ����������"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="Market")
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
                show_info("�ɹ�ʰȡ���");
                return;
            }
            else if(msg=="ask")
            {
                show_info(info_saleman);
                return;
            }
            else if(msg=="goto gate")
            {
                pl.set_pos(game_map.get_pos("dor gate"));
                show_info(info_to_gate);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"����look�鿴�������������pick breadʰȡ���������askѯ���ջ�Ա�����\
                \n����use bread���ԳԵ�һ��ʰȡ�������������������goto gate����ȥѧ԰�ſڣ�������������ѯ�ʺ���ȥ��"<<endl;
                return;
            }
        }
    }
    else if(pl.get_pos()->get_name()=="dor gate")
    {
        
    }
    else if(pl.get_pos()->get_name()=="west building")
    {

    }
    else if(pl.get_pos()->get_name()=="biolab")
    {

    }
    else if(pl.get_pos()->get_name()=="roof")
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