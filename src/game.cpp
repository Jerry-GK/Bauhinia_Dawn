#include "game.h"
using namespace std ;

void Game::Init()
{
    cout<<info_welcome;

    this->stage=NOT_BEGIN;
    //主线地点初始化
    Position p;
    input_box.clear();
    msg.clear();
    partner_alive = true;
    enemy_alive = true;

    p.set("dormitory",20,120);//宿舍
    p.add_status(DOR_TO_LOOK_OUTSIDE);
    p.add_status(DOR_TO_CHOOSE);
    game_map.add_pos(p);
    
    p.set("shop",22,115);//超市
    p.add_status(SHOP_SEARCH);
    p.add_status(SHOP_ASK);
    game_map.add_pos(p);

    p.set("dor gate",15,115);//宿舍门口
    p.add_status(GATE_FIGHT);
    p.add_status(GATE_AFTER_FIGHT);
    game_map.add_pos(p);

    p.set("west building",20,50);//西教
    p.add_status(WEST_INTO_BUILDING);
    p.add_status(WEST_MEET);
    p.add_status(WEST_FIGHT);
    p.add_status(WEST_CHECK);
    game_map.add_pos(p);

    p.set("bio lab",70,10);//生物实验室
    p.add_status(BIO_INTO_BUILDING);
    p.add_status(BIO_MEET);
    p.add_status(BIO_LEAVE);
    game_map.add_pos(p);

    p.set("roof",25,65);//原管院楼顶
    p.add_status(ROOF_HALL);
    p.add_status(ROOF_TOP);
    p.add_status(ROOF_LEAVE);
    p.add_status(ROOF_SUC);
    p.add_status(ROOF_TO_WHARF);
    game_map.add_pos(p);

    p.set("wharf",35,75);//水上码头
    p.add_status(WHARF_DECIDE);
    game_map.add_pos(p);

    p.set("lake",35,75);//启真湖
    p.add_status(LAKE_ROW);
    p.add_status(LAKE_FIGHT);
    p.add_status(LAKE_SAVE);
    p.add_status(LAKE_SUC);
    game_map.add_pos(p);

    p.set("south gate",0,0);//南门出口
    p.add_status(SOUTH_END);
    game_map.add_pos(p);

    //支线地点初始化
    p.set("east building", 50, 50);//东教（刷怪窟）
    p.add_status(EAST_BUILDING);
    game_map.add_pos(p);

    p.set("library", 20, 5);//医学图书馆（物资库）
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

bool Game::Load(string filename)//待实现的读档函数
{
    
    //打开文件
    //打开txt文件（若不存返回false)
    //依次读入bag的成员变量，设置bag属性
    //依次读入player成员变量，并用其设置game对象中player的属性
    //依次读入game成员变量，并用其设置game对象的属性

    //成功则返回true
    cout << "读档中 . . ." << endl;
    ifstream fin(global_save_file_name.c_str(), ios::in);
    if (!fin) { //打开失败
        cout << "读取存档时发生错误(可能是存档文件不存在)！" << endl;
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
        cout << "读档成功！" << endl;
        return true ;
    }
}



bool Game::Save(string filename)//待实现的存档函数
{
    ofstream fout(global_save_file_name.c_str()) ;
    cout << "存档中 . . ." << endl;
    if (fout)
    {
        fout << "Game Saved Data :" << endl;

        //对游戏阶段的写入      
        fout << "Game member:" << endl;
        fout << "stage :" << stage << endl;
        fout << "partner :" << partner_alive << endl;
        fout << "enemy :" << enemy_alive << endl << "- - - - " << endl;

        //对玩家信息的写入
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

        //对玩家道具的写入
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
        cout << "存档成功！" << endl;
        return true ;
    }
    else
    {
        cout << "存档失败！（可能是文件不存在）" << endl;
        return false;
    }
    
}

void Game::read()
{
    cout<<"\nPlease enter: ";
    getline(cin,input_box);
    submit();
}

void Game::submit()//从对话框读取玩家输入的文本,处理文本（input_box->msg, clear input_box, call process）
{
    msg=input_box;
    //规范化msg
    transform(msg.begin(), msg.end(), msg.begin(), ::tolower);//转成小写
    msg.erase(0,msg.find_first_not_of(" "));//删除头部空格
    msg.erase(msg.find_last_not_of(" ") + 1);//删除尾部空格

    input_box.clear();
    process(msg);
}

//--------------------------Process (out put and control the game according to input, main part)--------------------
void Game::process(string msg)//根据pos，处理msg文本,最关键的部分，根据地点，划分出小状态
{
    //进入游戏
    if(is_end())//游戏已经结束，决定是否重来
    {
        if(msg=="load")
        {
            Load(global_save_file_name);//读取存档
            return;
        }
        else if(msg=="restart")
        {
            Init();//新建游戏
            return;
        }
        else if(msg=="quit")
        {
            this->stage=QUIT;
            return;
        }
        else
        {
            cout << "请按提示进行选择！" << endl;
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
            cout<<"你是"<<global_player_name<<"，是浙大计算机系的一名普通大二学生。昨晚是周六，室友都出去玩了，只留下你在宿舍。早上九点，你像"
                    "往常一样模模糊糊地醒来，肚子很饿。窗外很暗，似乎又是沆州特有的阴天，你简单完成了洗漱，正准备去教学楼自习，突然听到教学楼外面"
                    "有一声撕心裂肺的惨叫...... (look查看情况)"<<endl;
            this->stage = PLAYING;
            return;
        }
        else if(msg=="load")
        {
            Load(global_save_file_name);//读取存档
            return;
        }
        else
        {
            cout<<"请输入start开始游戏，或输入load读取存档！"<<endl;
            return;
        }
    }
    //任何场景下都可执行的指令
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
        cout << "重新开始游戏!\n" << endl;
        Init();//新建游戏
        return;
    }
    else if(msg=="goto east building")//前往东教学楼（丧尸窟）
    {
        if(pl.get_cur_pos()->get_name()=="dormitory"||pl.get_cur_pos()->get_name()=="lake"
           ||pl.get_cur_pos()->get_name()=="roof"||pl.get_cur_pos()->get_name()=="library"
           ||pl.get_cur_pos()->get_name()=="east building")
        {
            cout << "当前位置无法直接前往东教学楼！" << endl;
            return;
        }
        if(!pl.move_to(game_map.get_pos("east building")))
            return;
        pl.get_off_vehicle();
        cout << "你来到了东教。" << endl;
        return;
    }
    else if(msg=="goto library")
    {
        if(pl.get_cur_pos()->get_name()=="dormitory"||pl.get_cur_pos()->get_name()=="lake"
           ||pl.get_cur_pos()->get_name()=="roof"||pl.get_cur_pos()->get_name()=="library"
           ||pl.get_cur_pos()->get_name()=="east building")
        {
            cout << "当前位置无法直接前往医学图书馆！" << endl;
            return;
        }
        if(!pl.move_to(game_map.get_pos("library")))
            return;
        pl.get_off_vehicle();
        cout << "你来到了医学图书馆。" << endl;
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
        cout << "已回复至最大体力！" << endl;
        return;
    }
    //非任何场景之下都可执行的指令
    else if(pl.get_cur_pos()->get_name()=="dormitory")//Scene 1: Dormitory
    {
        if(pl.get_cur_status()==DOR_TO_LOOK_OUTSIDE)
        {
            if(msg=="look")
            {
                cout << "你急忙向窗外望去，看到了震惊的一幕：窗外，一群丧尸正在疯狂撕咬一名学生，这名学生发出阵阵惨叫，渐渐的眼神失去了"
                        "光泽，变得跟那群丧尸一样。你意识到，学校爆发了可怕的丧尸病毒，而你必须想办法逃出去。\n你可以选择：\nlook：查看宿舍周围情况\ngoto shop: 前往教育超市观察"
                     << endl;
                pl.set_status(DOR_TO_CHOOSE);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"输入look向窗外观察情况"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==DOR_TO_CHOOSE)
        {
            if(msg=="look")
            {
                cout <<"你背上自己的书包，想出去，但感觉需要做一些准备。你看了看四周，宿舍里似乎没什么吃的，也没什么武器可以用来防身，再仔细看看"
                       "似乎只有宿舍的衣叉(fork)，或者是自己的伞，看起来勉强有些攻击力，要不要捡起呢？或者直接前往超市？(hint查看提示)" <<endl;
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
                cout << "你从宿舍出来，躲着丧尸的视线，一路小跑来到了学园门前的启真教育超市" << endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look:观察宿舍\npick "<<global_fork_name<<"拾取衣叉\npick "<<global_umbrella_name
                    <<"拾取雨伞\ngoto shop前往教育超市"<<endl;
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
                cout<<"你在超市四周看了看，庆幸的是，售货员没有变成丧尸，你很想问她到底发生了什么。丧尸也似乎"
                      "对超市里人类的食物不感兴趣，只是在外面不断巡逻。超市里有很多面包，你饿得不行。(hint查看提示)"<<endl;
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
                cout << "售货员告诉你：昨晚，一群丧尸突然袭击了整个校园，事情发生的太突然，很多人都被感染了。"
                        "这个小超市还没有被攻破。但是现在学校的各个出口大门都有丧尸在巡逻，根本出不去。"
                        "听说教学区还有幸存者。她建议你去西教去找找看,说不定可以一起逃出去。" << endl;
                return;
            }
            else if(msg=="goto dor gate")
            {
                if(!pl.move_to(game_map.get_pos("dor gate")))
                    return;
                pl.get_off_vehicle();
                cout << "你离开超市，蹑手蹑脚来到宿舍门口，可是还是被丧尸发现了，丧尸张着绿色的嘴巴，"
                        "正向你扑来... (hint查看提示)"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look:查看超市情况\npick bread:拾取面包\nask:询问收获员情况\n"
                "use "<<global_bread_name<<":可以吃掉一个拾取的面包补充体力\n"
                "pick "<<global_knife_name<<": 购买一把小刀\n"
                "goto dor gate:可以去学园门口(建议准备好武器、吃完面包、询问后再去）"<<endl;
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
                cout<<"你狼狈地逃回了教育超市,还好丧尸没有追过来。看来还是得准备点物资才能与丧尸再战。"<<endl;
                delete z;
                return;
            }
            else if(msg=="fight")
            {
                //战斗逻辑
                switch(pl.fight(z))
                {
                    case 0:
                        this->stage=DIE;
                        cout << info_end << endl;
                        break;
                    case 1: 
                        pl.set_pos(game_map.get_pos("shop"));
                        cout<<"你狼狈地逃回了教育超市,还好丧尸没有追过来。看来还是得准备点物资才能与丧尸再战。"<<endl;
                        delete z;
                        break;
                    case 2:
                        pl.set_status(GATE_AFTER_FIGHT);
                        cout <<"你用尽了全力，丧尸总算在你眼前倒下了，你也气喘吁吁，还好没有被咬到。你来到学园门前的路旁，发现四周空无一人，只有"
                                "远处隐约有几只丧尸在漫无目的的走着。你想去西教，可不确定自己的体力能否支撑自己走到。" <<endl;
                        delete z;
                }
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看丧尸信息\nescape:逃回超市\nfight:迎战\n建议使用use <武器名> 指令，配备武器后再战"<<endl;
                delete z;
                return;
            }
        }
        if(pl.get_cur_status()==GATE_AFTER_FIGHT)
        {
            if(msg=="look")
            {
                cout<<"你向四周看了看，发现只有一些东倒西歪的共享单车，一个启动着的小龟，和停在路旁的一些关着车门的私家车。"<<endl;
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
                cout<<"你没有车钥匙,无法乘坐私家车！"<<endl;
                return;
            }
            else if(msg=="goto west building")
            {
                if(!pl.move_to(game_map.get_pos("west building")))
                    return;
                pl.get_off_vehicle();
                cout<<"你来到了西教，眼前的景象让你大吃一惊...... (hint查看提示)"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看马路情况\ntake "<<global_bike_name<<": 骑上自行车\ntake "<<global_ebike_name
                    <<":骑上小龟\ntake "<<global_car_name<<": 乘汽车\n""goto west building: 去西教"<<endl;
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
                cout<<"西教的一楼里，到处都是血迹和残肢，遍布四处，你差点呕吐。楼上传出阵阵丧尸的嘶吼声，看来丧尸似乎刚把这里扫荡一空。"
                        "你望向墙上显示教室占座率的大屏：0%，0%，0%...，所有人都死了吗？你陷入了绝望。突然你看到了一行字：西1-404，占座率1%"
                        "与此同时，你听到楼上有人喊：救命，有人吗？你十分激动，原来除了自己还有其他幸存者！"<<endl;
                return;
            }
            else if(msg=="search")
            {
                pl.set_status(WEST_MEET);
                cout<<"你蹑手蹑脚地爬上楼梯，不被丧尸发现。好不容易来到了西1-404门口，里面却异常安静，你小心翼翼地探过头去，发现里面有一个女生！"
                        "但你也不确定她是不是丧尸。她见了你，也十分害怕，开口问到：你，你没有被感染吧。你松了一口气，说到：没有没有，我也是刚来到这的,"
                        "这里到底发生了什么？她见你不是丧尸，便走了过来，说到：我昨晚来西教自习，结果睡着了，晚上10点多的时候，听到外面一阵躁动，"
                        "接着就出现了一群可怕的丧尸，见人就咬，在这里自习的同学很多都被...。我吓坏了，找了个教室，关了灯，躲了起来，一直不敢出去。"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看西教情况\nsearch: 寻找幸存者"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==WEST_MEET)
        {
            if(msg=="look")
            {
                cout<<"眼前的这个女生，看起来十分虚弱，眼里充满了惊恐，不像是在说谎。门口有丧尸的踱步声。"<<endl;
                return;
            }
            else if(msg=="give "+global_bread_name)
            {
                if(!pl.have(global_bread_name))
                {
                    cout<<"你没有面包！"<<endl;
                    return;
                }
                cout<<"你把面包递给了她，告诉她你叫"<<global_player_name<<"。她连忙道谢，说到：我叫小语，还好有幸存者，要是只剩我一个人我真不知道该怎么办。"
                        "不过我们总在教室等着也不是办法，得想办法找线索逃出去啊！你叹了叹气，说：没办法，学校的所有"
                        "出口的保安都已经被丧尸感染了，门口聚集了大量没有蓝码的丧尸，我们出不去的。"
                        "她说：既然这样，我们必须得找一找丧尸病毒爆发的线索了。"<<endl;
                pl.drop(global_bread_name);
                return;
            }
            else if(msg=="leave")
            {
                cout<<"你带着小语走出教室，想要寻找线索，但丧尸似乎不同意... (look查看丧尸特征)"<<endl;
                pl.set_status(WEST_FIGHT);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看她的情况\ngive "<<global_bread_name<<": 给她面包补充体力，说不定她会说些什么\nleave: 走出教室寻找线索"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==WEST_FIGHT)
        {
            Zombie* z=new Roll_Zombie;
            if(msg=="look")
            {
                cout<<"一只丧尸手里拿着一本书，想你冲过来。糟了，是卷王丧尸！"<<endl;
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
                        cout<<"你把门一关，逃回了教室里面"<<endl;
                        delete z;
                        break;
                    case 2:
                        pl.set_status(WEST_CHECK);
                        cout<<"费劲了九牛二虎之力总算击败了卷王丧尸，卷王真可怕。看着倒在眼前的丧尸，你和小语陷入沉思(look查看丧尸)"<<endl;
                        delete z;
                }
                return;
            }
            else if(msg=="escape")
            {
                pl.set_status(WEST_MEET);
                cout<<"你把门一关，逃回了教室里面"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看走廊情况\nfight:与丧尸作战\nescape: 逃回到教室"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==WEST_CHECK)
        {
            if(msg=="look")
            {
                cout<<"眼前的丧尸双目圆睁，头发不多，牙齿、舌头全变成了瘆人的绿色。小语在旁边说：你好厉害啊，居然打得过丧尸，要不要检查一下"
                      "他呢？说不定能搜出什么东西来，获取一些线索。(search搜身)"<<endl;
                return;
            }
            else if(msg=="search")
            {
                cout<<"你搜了搜他，找到了他的手机，扫了扫他的脸，完蛋，变成丧尸太丑扫不出来。没办法，用他的指纹解锁了手机"
                        "好像没什么特别的东西。你打开微信，都是跟导师和实验室同学的关于科研的聊天，连个妹子都没有，果然是单身老博。"
                        "突然，小语在旁边发现了一点端倪：你看那个最近的一条消息，昨晚晚上9点，导师叫他去实验室，然后他就再没有其他消息了。"
                        "你陷入沉思，再仔细一看，原来是生物系的老博，而他的实验室似乎与人体的自愈机理相关。小语说：要不我们去他的生物实验室"
                        "看一看吧，说不定能找到他被感染的线索！"<<endl;
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
                cout<<"你跟小语一起来到了生物实验室(look查看情况，go in直接进入)"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看死去的丧尸情况\nsearch:检查丧尸\ntake "<<global_bike_name<<":来到楼下，骑自行车\n"
                    "take "<<global_ebike_name<<":来到楼下，骑小龟\ngoto bio lab: 前往生物实验室(建议先乘坐交通工具)"<<endl;
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
                cout<<"生物实验室位于紫金港东南角的一栋灰色的大楼里。小语注意到，在门口并没有看到几只丧尸，但是地上却布满了密密麻麻的丧尸的血脚印，甚是奇怪。"
                        "你拿出丧尸的手机，对比聊天记录，没错，他的导师就是让他来的这里。生物实验室的门虚掩着..."<<endl;
                return;
            }
            else if(msg=="go in")
            {
                cout<<"你推开了生物实验室的门，眼前的景象看起来十分正常, 还有一个人... (look查看情况)"<<endl;
                pl.set_status(BIO_MEET);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看门口情况\ngo in: 进入生物实验室"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==BIO_MEET)
        {
            if(msg=="look")
            {
                cout<<"眼前是一位中年教授，穿着干净，显然没有被丧尸感染。实验室的桌子上，摆放着许多装着奇怪试剂管子，个头不小"
                      "有红色的，有绿色的，还不小。小语问道：要不要问一下他什么情况呢？ (ask询问)"<<endl;
                return;
            }
            else if(msg=="ask")
            {
                cout<<"中年男子介绍说自己姓叶，是生物学院的教授，昨天叫学生来实验室做实验，没想到他来的时候已经变成了丧尸，他不知道怎么回事"
                        "赶忙把他锁在了门外，自己也一直不敢出去，一直躲在实验室里研发解药。你心想：解药？该不会是这些花花绿绿的管子吧？"
                        "他接着说道：你们应该也想出去吧？可惜现在学校出口都是丧尸把守，根本出不去。我建议你们去旧管理学院大楼，就是浙大启真湖旁边最高的那个建筑"
                        "，现在是行政楼。去那栋楼的楼顶上去看一看，那里视野好，可以看看有没有出路，或者向外面求救也是比较容易发现的。小语很激动：确实是个好主意！"
                        "您也跟我们一起去吧。叶教授无奈的笑了笑，说：算了，老了。我去会给你们徒增负担，我还是研发解药吧，说不定还能解救感染的同学。"
                        "哦对了，那里挺远的，我的车停在楼下了，你们要用可以开！说完丢给了我们一串车钥匙。"
                        "你看了看眼前的叶教授，觉得他说的确实有道理，但总感觉哪句话怪怪的。算了，还是先去看看吧。"<<endl;
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
                cout<<"你和小语离开了实验室，回到生物大楼楼下。"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 检查实验室情况\nask: 询问教授情况\npick "<<global_redtube_name
                    <<": 偷偷揣走红色试管\npick "<<global_greentube_name<<": 偷偷揣走绿色试管\nleave: 离开实验室"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==BIO_LEAVE)
        {
            if(msg=="look")
            {
                cout<<"楼下，零散地停着自行车和小龟，还有旁边叶教授的私家车。走去管院太消耗体力，可是你也不太信任叶教授。"<<endl;
                return;
            }
            else if(msg=="take "+global_ebike_name)
            {
                cout<<"小龟没电了！"<<endl;
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
                cout<<"你和小语从生科院一路来到旧管院楼顶（现行政楼）。一路上，看到了无数可怕的丧尸。最后，你们安全到达了这栋高高建筑的一楼大厅。"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 检查路边情况\ntake "<<global_bike_name<<": 骑上自行车(好像离目的地有点远)\ntake "<<global_ebike_name<<": 骑小龟\n"
                        "take "<<global_car_name<<": 开叶教授的私家车\ngoto roof: 前往旧管院楼顶"<<endl;
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
                cout<<"你向大厅望去，被惊呆了。这里明显有激烈的打斗痕迹，血迹、弹孔到处都是，地上还有一只断手，手里紧紧握着一把枪。"
                        "看来这里发生过恶战。但奇怪的是现在这里似乎并没有丧尸的动静。小语说：要不我们先坐电梯到楼顶看看吧？"
                        "就像叶教授说的，那里视野好，能看到哪个出口丧尸少、有机会逃出去！(hint查看提示)"<<endl;
                return;
            }
            else if(msg=="pick "+global_gun_name)
            {
                pl.pick(global_gun_name, PICK);
                return;
            }
            else if(msg=="go up")
            {
                cout<<"你和小语乘电梯来到了楼顶"<<endl;
                pl.set_status(ROOF_TOP);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看大厅情况\npick "<<global_gun_name<<": 捡起断手握着的枪\ngo up: 坐电梯去楼顶"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==ROOF_TOP)
        {
            if(msg=="look")
            {
                cout<<"你和小语来到了旧管院的楼顶——这里是浙大的最高点，视野最为开阔。你们向远处望去，浙大全貌一览无余。"
                        "可以看到学校到处都散布着饥肠辘辘的丧尸，你把眼光投向东二门，不出所料，全是丧尸。校医院大门、蓝田大门也是。"
                        "再转过头，南面的东三门、甚至是新建的南大门门口也都围满了丧尸，看来从校门逃出没有任何希望了，你和小语陷入了绝望..."
                        <<endl;
                Player::delay();
                cout<<"你盯着启真湖，突然眼前一亮：启真湖的支流弯弯曲曲的向南方流去，流向南华园。小语似乎看懂了你的想法"
                        "忙说：我听说顺着启真湖往南花园方向，有一条隐秘的水路，可以通向学校南边的余杭塘河！也就是说，我们可以通过水路出校！"
                        "你欣喜若狂，冷静下来，说：可是，我们怎么从水路逃跑呢？我们又没有船。小语想了想，说道：水上码头！那里是学校开设的"
                        "水上运动课的上课地点，我恰巧上过，那里有许多皮划艇！我们可以划船，顺着水路一路出去!"<<endl;
                return;
            }
            else if(msg=="leave")
            {
                pl.set_status(ROOF_LEAVE);
                cout<<"你和小语准备离开大楼，开车前往水上码头，可是确发现了一丝不对劲... (look查看情况)"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 向四周眺望观察学校情况\nleave: 准备离开大楼，开车前往启真湖"<<endl;   
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
                cout<<"来时上楼的电梯好像坏了，而楼梯传来嘈杂的声音，再仔细一听，似乎是丧尸的声音！你和小语忙跑回楼顶往下看，"
                        "眼前的景象把你俩吓了个半死：楼下，成群的丧尸正涌入大楼，楼梯里，丧尸的脚步声越来越近..."
                        "怎么会这样？而远处，你居然看到了有一个熟悉的人，他坐在楼下的花坛旁，从容不迫地笑着，丧尸们也不去攻击他。"
                        "而他，竟然是叶教授！(ask质问)"<<endl;
                for (int i = 0; i < v_zom.size();i++)
                    delete v_zom[i];
                return;
            }
            else if(msg=="ask")
            {
                cout<<"你疑惑而又愤怒地大声问叶教授这是怎么回事。叶教授邪恶地笑了，说：其实丧尸病毒就是我昨晚研发出来的，用它感染了我实验室的学生"
                        "作为第一批实验对象，他们只用一晚上就感染了全学校。我作为生物学院唯一研究人体自愈的老师，致力于通过改变基因让人类掌握机体自愈功能，"
                        "却长期得不到重视，甚至被学术圈口诛笔伐，谴责我违背人类伦理，把我达成了罪人！为了让他们付出代价，也为了向世人展示我研究的伟大"
                        "成果，我决定让丧尸席卷全校！""而你们，是目前我发现的仅存的幸存者。所以我诱使你们来到这里，而我能控制"
                        "丧尸，让他们来这里追杀你们。哈哈哈哈，我挑的地方很不错吧，你们现在插翅难飞咯！"<<endl;
                for (int i = 0; i < v_zom.size();i++)
                    delete v_zom[i];
                return;
            }
            else if(msg=="jump")
            {
                cout << "你确定要从楼顶跳到湖里吗？(消耗"<<global_jump_damage<<"体力，输入 \"yes\" 确认):" << endl;
                string ensure;
                getline(cin, ensure);
                if(ensure!="yes")
                {
                    cout << "大楼太高了，你实在不敢跳。" << endl;
                    return;
                }
                pl.changeHP(-global_jump_damage);
                if(pl.getcurrentHP()==0)
                {
                    cout << "啪！尽管下面是湖，但是巨大的冲击力让你粉身碎骨，你摔死了！" << endl;
                    this->stage = DIE;
                    cout << info_end << endl;
                    return;
                }
                pl.set_pos(game_map.get_pos("wharf"));

                cout<<"You jump， I jump！你和小语一起跳到了启真湖，巨大的冲击力让你们差点丧命，用仅剩的一点体力拼命游到了水上码头。"<<endl;
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
                        cout << "你们发觉打不过这么多丧尸，狼狈地逃了回去" << endl;
                        break;;
                    case 2:
                        cout << "你成功打败了这一群丧尸，顺着层层楼梯杀了出去，来到了楼下叶教授面前(look查看)" << endl;
                        pl.set_status(ROOF_SUC);
                }
                for (int i = 0; i < v_zom.size();i++)
                    delete v_zom[i];
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看周围情况\nask: 质问叶教授\njump: 拉着小语从楼顶跳到启真湖（很危险,消耗"<<global_jump_damage<< "体力）"
                      "再游去水上码头\nfight: 跟丧尸硬刚，顺着楼梯杀下去"<<endl;
                for (int i = 0; i < v_zom.size();i++)
                    delete v_zom[i];
                return;
            }
        }
        else if(pl.get_cur_status()==ROOF_SUC)
        {
            if(msg=="look")
            {
                cout << "叶教授没想到你们竟能杀出来，十分震惊，面露惧色。小语说：要不饶他一命吧。(hint查看提示)" << endl;
                return;
            }
            else if(msg=="fight")
            {
                cout << "你对他不顾师生性命做丧尸实验的行为非常痛恨，将其击毙，为民除害！\n解了气，你们开始思考下一步该怎么办了。" << endl;
                enemy_alive = false;
                pl.set_status(ROOF_TO_WHARF);
                return;
            }
            else if(msg=="forgive")
            {
                cout << "你听了小语的话，还是没有对叶教授痛下杀手。他趁你不注意，光速溜回了车里，把车开走了。你很是生气，现在，该怎么办呢？" << endl;
                pl.set_status(ROOF_TO_WHARF);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 观察叶教授神色\nfight: 击毙叶教授\nforgive: 饶叶教授一命"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==ROOF_TO_WHARF)
        {
            if(msg=="look")
            {
                cout << "你看了看四周，从大楼底下可以看到对岸的水上码头，对！你们现在要前往水上码头，从水路逃跑！可是，怎么去呢？"
                     << "你向周围看了看，有自行车，有电动车，";
                if(enemy_alive)
                    cout << "可是来时候的汽车被叶教授开走逃跑了, 真烦。" << endl;
                else
                    cout << "还有来的时候开的叶教授的汽车。" << endl;
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
                    cout << "叶教授刚才已经把汽车开走了！" << endl;
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
                cout << "你们来到了水上码头" << endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看周围情况\ntake "<<global_bike_name<<": 骑上自行车\ntake "<<global_ebike_name
                    <<":骑上小龟\ntake "<<global_car_name<<": 乘汽车\n""goto wharf: 乘当前载具，去水上码头"<<endl;
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
                cout << "你们来到水上码头，发现这里船只确实不少，还有几块新鲜的苹果。小语挑了一艘看起来比较新的船。";
                if(enemy_alive)
                    cout << "远处，叶教授在对岸的大楼下气急败坏。";
                cout<<"你们望向波光粼粼的水面，看起来很宁静，但又似乎隐藏着什么危机。准备好了吗！"<<endl;
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
                    cout<<"当前的交通工具无法在水上行驶！"<<endl;
                    return;
                }
                pl.set_pos(game_map.get_pos("lake"));
                cout<<"你和小语乘上了皮划艇，划向阳明桥，准备划到启真湖心..."<<endl;

                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看码头情况\npick "<<global_apple_name<<": 捡起苹果\ntake "<<global_boat_name
                    <<": 乘船\nrow: 划船去出口\n(建议先use bread补充刚才损失的体力)"<<endl;
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
                cout<<"你们在船上四处张望。回头一看";
                if(enemy_alive)
                    cout << "发现叶教授已经不见了踪影";
                cout<<"不远处的旧管院楼顶上，也就是你们刚刚在的地方，已经布满了丧尸。"
                      "小语在你旁边，松了口气，说道：总算暂时安全了，还好有你，不然我一个人肯定逃不出去。出去以后我一定要去"
                      "找我的爸爸妈妈，他们一定很担心我。你也放松了下来，心想，现在主要划到南面的余杭塘河，就安全了！"<<endl;
                return;
            }
            else if(msg=="goto south gate")
            {
                pl.set_status(LAKE_FIGHT);
                cout<<"你们决定划船去南大门旁的水道，从那里逃出去。可是眼前的景象让你大吃一惊... (look查看情况)"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看湖四周情况\ngoto south gate: 准备划到南大门"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==LAKE_FIGHT)
        {
            Zombie* z=new Water_Zombie;
            if(msg=="look")
            {
                cout<<"船要想驶向南边，需要穿过阳明桥，可是定睛一看，桥洞里竟然游荡着可怕的丧尸，是水丧尸！"
                    "再仔细一看，水丧尸张开瘆人的绿色嘴巴，正发了疯似地向你们游过来。这群水丧尸不仅能游泳，而且看起来更加凶猛！"<<endl;
                z->show();
                return;
            }
            else if(msg=="escape")
            {
                pl.set_pos(game_map.get_pos("wharf"));
                cout<<"你和小语赶紧掉头，飞速划向岸边，逃回水上码头。"<<endl;
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
                        cout<<"你和小语赶紧掉头，飞速划向岸边，逃回水上码头。"<<endl;
                        delete z;
                        break;
                    case 2:
                        //如果成功打败水丧尸
                        cout<<"经过一番激战，你们终于一起击败了水丧尸，可是旁边的小语却捂着胳膊，有些不对劲...(look查看小语情况)"<<endl;
                        pl.set_status(LAKE_SAVE);
                        delete z;
                }
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看水丧尸情况\nfight: 与水丧尸战斗、突破封锁\nescape: 掉头逃回水上码头"<<endl;
                return;
            }
        }
        else if(pl.get_cur_status()==LAKE_SAVE)
        {
            if(msg=="look")
            {
                cout<<"你看向小语，发现她的胳膊划开了一道长长的绿色伤口，糟了，刚才的战斗中小语被水丧尸咬伤了！"
                        "小语浑身发抖，眼泪从眼角流下，你望向她，原本水汪汪的眼睛开始泛白，不出几分钟，她就会变成丧尸！"
                        "她抽泣着说到：对不起，我拖累你了，看来我不能陪你逃出去了，把我推下船吧，呜呜..."
                        "你脑子一片空白，心里万般悔恨，刚才没有保护好小语。如果不想办法，她就会把自己也咬伤。"
                        "可你看着她，实在不忍心将她推下船，让她永远沉睡在启真湖底。哎，难道真的没有什么办法了吗？"<<endl;
                Player::delay();
                cout<<"突然你想到了生物实验室里的那些花花绿绿的瓶子和叶教授的话，会不会有解药？可是，可是，叶教授是坏人啊，"
                        "他真的会研发解药吗？就算会，那到底红色试剂是解药还是绿色试剂是呢？如果用错了，说不一定她会马上变成丧尸，"
                        "把自己咬死。哎，自己当时有没有顺走一瓶？不记得了，看一下背包，赌一下吧！(hint查看提示)"<<endl;
                return;
            }
            else if(msg=="push")
            {
                cout<<"你一狠心，猛地把小语推了下去。你看到她的眼神一点一点黯淡下去，缓缓沉入水底，而你，独自一人，划向南门..."<<endl;
                partner_alive = false;
                if(!pl.move_to(game_map.get_pos("south gate")))
                    return;
                return;
            }
            else if(msg=="give "+global_redtube_name)
            {
                if(!pl.have(global_redtube_name))
                {
                    cout<<"你之前在生物实验室并没有拿走红色试剂"<<endl;
                    return;
                }
                pl.drop(global_redtube_name);
                cout<<"小语喝下红色试剂，别看这颜色像鲜血似的，效果竟然很好。小语的伤口奇迹般地愈合了，身体也逐渐回复平静。"
                        "她张开双眼，说到：谢谢你救了我！你心想：这叶教授虽然不干人事，但是留了一手，保有解药，说不定"
                        "是以防万一自己感染备用的，还好当时自己机灵、拿走了一瓶。看到小语安全了，你终于松了一口气。"
                        "跟她一起从隐秘的水路划向南门"<<endl;
                if(!pl.move_to(game_map.get_pos("south gate")))
                    return;
                return;
            }
            else if(msg=="give "+global_greentube_name)
            {
                if(!pl.have(global_greentube_name))
                {
                    cout<<"你之前在生物实验室并没有拿走绿色试剂"<<endl;
                    return;
                }
                pl.drop(global_greentube_name);
                cout<<"小语喝下绿色试剂后，突然双目变白，伤口恶化，全身抽搐。你突然意识到这是叶教授发明的丧尸病毒药剂，就是他诱使学生喝下、产生了第一批丧尸，"
                        "也正因如此他们嘴里才全身是绿色。可是一切都已经晚了，小语瞬间变成了可怕的丧尸，一口把你咬住，你也变成了丧尸。黎明，不属于你们"<<endl;
                partner_alive = false;
                this->stage=DIE;
                cout << info_end << endl;
                return;
            }
            else if(msg=="goto south gate")
            {
                cout<<"受伤的小语躺在船后面，使用解药无望，你奋力划向南门，说不一定到了外面能找到帮助！你划啊划，就快到了。"
                        "你看到了余杭塘河的入口，看到了把学校重重包围的武警，你看到了希望。突然，你背后一痛。你惊愕地回头一望，"
                        "小语正咬着你的肩膀，伤口渗出绿色的液体。她的眼睛已经完全浑浊了，但留下了一滴泪，你听到她轻声说：对，对不起..."
                        "你的视线开始模糊，四肢逐渐无力，最终，也倒在了船上，变成了丧尸...黎明，不属于你们"<<endl;
                this->stage=DIE;
                cout << info_end << endl;
                return;
            }
            //use red/green tube在全局有
            else if(msg=="hint")
            {
                cout<<"look: 检查小语情况\npush: 将小语推下船\ngive "<<global_redtube_name<<": 给小语服用血红色试剂\n"
                       "give "<<global_greentube_name<<": 给小语服用深绿色试剂\n"
                       "goto south gate: 强行带着被咬伤的小语逃向出口\n(可以先输入bag看一下背包里有什么药剂)"<<endl;
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
                cout<<"顺着这条隐秘水路果然划到了南大门旁边的余杭塘河。这条河流是隔离学校与外界的一条河，河水又绿又丑，可现在却十分亲切";
                if(!partner_alive)//小语已经死了
                    cout<<"你向对岸望去，发现学校早已被武警包围了，四周全是警车，武警们正用枪对准着你，显然，你是潜在的丧尸。"<<endl;
                else//小语跟你一起逃出来了
                    cout<<"小语指向对岸，对你说：看！你转过头，原来，学校四周早已被武警重重包围了，到处都是警车，武警们正用枪"
                            "对着浑身是血的你们，显然，你们被当作潜在的丧尸了。小语提醒你：别轻举妄动，我们要让他们相信我们没有被感染！"
                            "我看过釜山行，我们可以唱歌给他们听！"<<endl;
                return;
            }
            else if(msg=="ashore")
            {
                pl.get_off_vehicle();
                cout<<"武警见浑身是血的你打算强行上岸，没有办法，扣动了扳机，你被击杀了。（没有看过釜山行吗？）"<<endl;
                this->stage=DIE;
                cout << info_end << endl;
                return;
            }
            else if(msg=="sing")
            {
                pl.get_off_vehicle();
                cout<<"你唱起了歌。远处，学校里丧尸横行，天上阴雨蒙蒙，余杭塘河绿色的水面上飘起阵阵歌声。"
                            "武警们听到歌声，犹豫了一会儿，放下了枪，说到：这里还有幸存者，医护人员快来！"
                            "你们被全副武装的武警们冲上去扶住，送往救护车。救护车越开越远，透过车窗，你看到了愈来愈院的"
                            "南大门，浙江大学四个字依稀可见，今天发生的一切仿佛做梦一般，令人不敢相信。"<<endl;
                Player::delay();
                if(!partner_alive)//独自一人逃出来
                {
                    cout<<"你虽然逃出来了，可是心里怅然弱失。你再次望向学校，想起启真湖底的小语，心情难以平复。"
                            "如果，如果自己能在和丧尸的战斗中保护好小语，哪怕能拿走解药、能选对药，小语也不会在湖底长眠。"
                            "可是，没有那么多如果，最终只有你一人逃出来，你迎来了紫荆的黎明，而她，却沉睡在了永恒的黑夜..."<<endl;
                    this->stage=ALONE_SUC;
                    cout << info_end << endl;
                    return;
                }
                else//一起逃出去（最佳结局）
                {
                    cout<<"你转头望向小语，她静静地坐着，也看向你：说道：我们总算逃出来了，不是吗？你笑了，她也笑了。"
                            "或许，这就是你们的紫荆黎明。"<<endl;
                    this->stage=SUC;
                    cout << info_end << endl;
                    return;
                }
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看周边情况\nashore: 直接上岸\nsing: 唱歌给武警们听"<<endl;
                return;
            }
        }
    }
    //支线地点（临时）
    else if(pl.get_cur_pos()->get_name()=="east building")//东教，丧尸窟
    {
        if(msg=="look")
        {
            cout<<"这里是东教，原本是学习的天堂，现在却成了丧尸窟，到处都是穷凶极恶的丧尸，宛如人间地狱。"
                  "但是富贵险中求，对你来说丧尸意味着危险，但是击败他们也意味着战斗经验的提升，而且说不定能从他们身上搜出钱来，购买物资。"
                  "你决定拿好武器，调整好状态，击败丧尸！"<<endl;
            return;
        }
        else if(msg=="fight")
        {
            Zombie *z = NULL;
            vector<Zombie*> v_zom;
            
            //随机生成丧尸
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
                cout << "这次出现的是" << z->getname() << " !" << endl;
                switch(pl.fight(z))
                {
                    case 0:
                        this->stage=DIE;
                        cout << info_end << endl;
                        break;
                    case 1: 
                        cout<<"你赶紧逃回了东教门口"<<endl;
                        delete z;
                        break;
                    case 2:
                        //成功打败丧尸
                        cout << "你成功打败了这只丧尸，还要继续战斗吗？" << endl;
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
                        cout << "你发觉打不过这么多丧尸，狼狈地逃回了东教门口" << endl;
                        break;;
                    case 2:
                        cout << "你成功打败了这一群丧尸，还要继续战斗吗？" << endl;
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
            cout << "look: 观察东教学情况\nfight: 随机找到一只丧尸并与之作战\nreturn: 从哪来回哪去" << endl;
            return;
        }
    }
    else if(pl.get_cur_pos()->get_name()=="library")//医学图书馆，物资库
    {
        if(msg=="look")
        {
            cout << "这里原本是图书馆，丧尸病毒爆发后变成了秘密物资库，摆放着各种各样的武器和食物，需要花钱购买：" << endl;
            cout << "-------------食物栏-------------" << endl;
            Bread b;
            b.show();
            cout << endl;
            Apple a;
            a.show();
            cout << endl;
            cout << "-------------武器库-------------" << endl;
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
                cout << "不存在该物品！" << endl;
                return;
            }
            if(!(item==global_bread_name||item==global_apple_name||
                item==global_fork_name||item==global_knife_name||item==global_umbrella_name||item==global_gun_name
                ||item==global_bloodsickle_name))
            {
                cout << "无法在这里购买此物品！" << endl;
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
            cout << "look: 观察图书馆武器库情况\npick <武器英文名>: 购买某种武器\nreturn: 从哪来回哪去" << endl;
            return;
        }
    }
    cout << "输入的指令无效！(可输入help查看一般合法指令, 输入hint查看当前操作提示)" << endl; //以上条件均不满足时，判定输入的为非法指令
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

void Game::quit()//退出游戏
{
    cout<<"\n游戏结束，谢谢体验！"<<endl;
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
