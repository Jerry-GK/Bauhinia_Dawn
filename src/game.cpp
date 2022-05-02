#include "game.h"

void Game::Init()
{
    show_welcome();
    //init positions in game map
    Position p;
    p.set("dorm",0,0);//宿舍
    p.add_status(DOR_WAKE_UP);
    //
    game_map.add_pos(p);
    
    p.set("Market",0,0);//超市
    p.add_status(MARKET_SEARCH);
    //
    game_map.add_pos(p);

    p.set("dor gate",0,0);//宿舍门口
    p.add_status(GATE_FIGHT);
    //
    game_map.add_pos(p);

    p.set("west building",0,0);//西教
    p.add_status(UNKNOWN);
    //
    game_map.add_pos(p);

    p.set("bio lab",0,0);//生物实验室
    p.add_status(UNKNOWN);
    //
    game_map.add_pos(p);
    
    p.set("roof",0,0);//原管院楼顶
    p.add_status(UNKNOWN);
    //
    game_map.add_pos(p);

    p.set("wharf",0,0);//水上码头
    p.add_status(UNKNOWN);
    //
    game_map.add_pos(p);

    p.set("lake",0,0);//启真湖
    p.add_status(UNKNOWN);
    //
    game_map.add_pos(p);

    p.set("south gate",0,0);//南门出口
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

void Game::submit()//从对话框读取玩家输入的文本（input_box->msg, clear input_box, call process）
{
    msg=input_box;
    input_box.clear();
    process(msg);
}

//--------------------------Process-----------------------------------
void Game::process(string msg)//根据pos，处理msg文本,最关键的部分，根据地点，划分出小状态
{
    //cout<<pl.get_pos()->get_name()<<endl;
    //任何场景下都可执行的指令
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

    //非任何场景之下都可执行的指令
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
                cout<<"输入begin开始游戏"<<endl;
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
                cout<<"输入look向窗外观察情况"<<endl;
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
                show_info("衣叉已拾取！");
                return;
            }
            else if(msg=="pick umbrella")
            {
                pl.pick("umbrella");
                show_info("雨伞已拾取！");
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
                cout<<"look:观察宿舍\npick fork拾取衣叉\npick umbrella拾取雨伞\ngoto market前往教育超市"<<endl;
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
                cout<<"look:查看超市情况\npick bread:拾取面包\nask:询问收获员情况\n"
                "use bread:可以吃掉一个拾取的面包补充体力\n"
                "pick knife: 购买一把小刀\ngoto gate:可以去学园门口（建议吃完面包、询问后再去）"<<endl;
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
                cout<<"你狼狈地逃回了教育超市,还好丧尸没有追过来。看来还是得准备点物资才能与丧尸再战。"<<endl;
                delete z;
                return;
            }
            else if(msg=="fight")
            {
                //战斗逻辑
                pl.fight(z);
                pl.set_status(GATE_AFTER_FIGHT);
                show_info(info_fight_suc);
                delete z;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看丧尸信息\nescape:逃回超市\nfight:迎战\n建议使用use <武器名> 指令，配备武器后再战"<<endl;
                delete z;
                return;
            }
        }
        if(pl.get_status()==GATE_AFTER_FIGHT)
        {
            if(msg=="look")
            {
                cout<<"你向四周看了看，发现只有一些东倒西歪的共享单车，一个启动着的小龟，和停在路旁的一些关着车门的私家车。"<<endl;
                return;
            }
            else if(msg=="take bike")
            {
                Vehicle* v= new Vehicle("自行车",20,10);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take e-bike")
            {   
                Vehicle* v= new Vehicle("小龟",30,10);
                pl.take_vehicle(v);
                return;               
            }
            else if(msg=="take car")
            {
                cout<<"你没有车钥匙,无法乘坐私家车！"<<endl;
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
                cout<<"look: 查看马路情况\ntake bike: 骑上自行车\ntake e-bike:骑上小龟\ntake car: 乘汽车\n"
                "get off: 离开交通工具\ngoto west building: 去西教"<<endl;
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

void Game::show_prompt(string prompt)const//生成提示信息
{
    show_info(prompt);
}

bool Game::is_end()const
{
    return this->stage==END;
}

void Game::quit()//退出游戏
{
    this->stage=END;
    show_bye();
}