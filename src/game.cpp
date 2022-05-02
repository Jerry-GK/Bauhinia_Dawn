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
    p.add_status(UNKNOWN);
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
    pl.set_pos(game_map.get_pos("dorm"));
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

    //非任何场景之下都可执行的指令
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
                pl.set_pos(game_map.get_pos("Market"));
                show_info(info_to_market);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"输入look观察宿舍，输入pick fork拾取衣叉，输入pick umbrella拾取雨伞，输入goto market前往教育超市"<<endl;
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
                show_info("成功拾取面包");
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
                cout<<"输入look查看超市情况，输入pick bread拾取面包，输入ask询问收获员情况。\
                \n输入use bread可以吃掉一个拾取的面包补充体力，输入goto gate可以去学园门口（建议吃完面包、询问后再去）"<<endl;
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