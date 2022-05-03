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
    p.add_status(WEST_INTO_BUILDING);
    //
    game_map.add_pos(p);

    p.set("bio lab",0,0);//生物实验室
    p.add_status(BIO_INTO_BUILDING);
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
        this->pl.use(msg.substr(4,msg.length()-4));
        return;
    }
    else if(msg.find("drop")==0)
    {
        this->pl.drop(msg.substr(5,msg.length()-5));
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
                Vehicle* v= new Vehicle("自行车",20,0);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take e-bike")
            {   
                Vehicle* v= new Vehicle("小龟",30,0);
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
                cout<<"look: 查看马路情况\ntake bike: 骑上自行车\ntake e-bike:骑上小龟\ntake car: 乘汽车\n"
                "get off: 离开交通工具\ngoto west building: 去西教"<<endl;
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
                cout<<"西教的一楼里，到处都是血迹和残肢，遍布四处，你差点呕吐。楼上传出阵阵丧尸的嘶吼声，看来丧尸似乎刚把这里扫荡一空。"
                        "你望向墙上显示教室占座率的大屏：0%，0%，0%...，所有人都死了吗？你陷入了绝望。突然你看到了一行字：西1-404，占座率1%"
                        "与此同时，你听到楼上有人喊：救命，有人吗？你十分激动，原来除了自己还有其他幸存者！但是听着楼上丧尸的死嘶吼，你"
                        "陷入了犹豫..."<<endl;
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
        else if(pl.get_status()==WEST_MEET)
        {
            if(msg=="look")
            {
                cout<<"眼前的这个女生，看起来十分虚弱、害怕，不像是在说谎。门口有丧尸的踱步声。"<<endl;
                return;
            }
            else if(msg=="give bread")
            {
                cout<<"你把面包递给了她，告诉她你叫小泽。她连忙道谢，说到：我叫小语，还好有幸存者，要是只剩我一个人我真不知道该怎么办。"
                        "不过我们总在教室等着也不是办法，得想办法找线索逃出去啊！你叹了叹气，说：没办法，学校的所有"
                        "出口的保安都已经被丧尸感染了，门口聚集了大量没有蓝码的丧尸，我们出不去的。"
                        "她说：既然这样，我们必须得找一找丧尸病毒爆发的线索了。"<<endl;
                pl.drop("bread");
                return;
            }
            else if(msg=="leave")
            {
                cout<<"你带着小语走出教室，想要寻找线索，但丧尸似乎不同意..."<<endl;
                pl.set_status(WEST_FIGHT);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看她的情况\ngive bread: 给她面包补充体力，说不定她会说些什么\nleave: 走出教室寻找线索"<<endl;
                return;
            }
        }
        else if(pl.get_status()==WEST_FIGHT)
        {
            Zombie* z=new Roll_Zombie();
            if(msg=="look")
            {
                cout<<"一只丧尸手里拿着一本书，想你冲过来。糟了，是卷王丧尸！"<<endl;
                return;
            }
            else if(msg=="fight")
            {   
                pl.fight(z);
                pl.set_status(WEST_CHECK);
                cout<<"费劲了九牛二虎之力总算击败了卷王丧尸，卷王真可怕。看着倒在眼前的丧尸，你和小语陷入沉思"<<endl;
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
        else if(pl.get_status()==WEST_CHECK)
        {
            if(msg=="look")
            {
                cout<<"眼前的丧尸双目圆睁，头发不多。小语在旁边说：哥哥好厉害！这个丧尸看起来像个老博,要不要检查他一下呢？"<<endl;
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
            else if(msg=="take bike")
            {
                Vehicle* v= new Vehicle("自行车",20,0);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take e-bike")
            {   
                Vehicle* v= new Vehicle("小龟",30,0);
                pl.take_vehicle(v);
                return;               
            }
            else if(msg=="goto bio lab")
            {
                pl.move_to(game_map.get_pos("bio lab"));
                pl.get_off_vehicle();
                cout<<"你跟小语一起来到了生物实验室"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看死去的丧尸情况\nsearch:检查丧尸\ntake bike:来到楼下，骑自行车\n"
                    "take e-bike:来到楼下，骑小龟\ngoto bio lab: 前往生物实验室(建议先乘坐交通工具)"<<endl;
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
                cout<<"生物实验室在紫金港东区的一栋大楼里。小语注意到，在门口并没有看到几只丧尸，但是地上却布满了密密麻麻的丧尸的血脚印，甚是奇怪。"
                        "你拿出丧尸的手机，对比聊天记录，没错，他的导师就是让他来的这里。生物实验室的门虚掩着..."<<endl;
                return;
            }
            else if(msg=="go in")
            {
                cout<<"你推开了生物实验室的门，眼前的景象看起来十分正常..."<<endl;
                pl.set_status(BIO_MEET);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看门口情况\ngo in: 进入生物实验室"<<endl;
                return;
            }
        }
        else if(pl.get_status()==BIO_MEET)
        {
            if(msg=="look")
            {
                cout<<"眼前是一位中年教授，穿着干净，显然没有被丧尸感染。实验室的桌子上，摆放着许多装着奇怪试剂管子，个头不小"
                      "有红色的，有绿色的，还不小。小语问道：要不要问一下他什么情况呢？"<<endl;
                return;
            }
            else if(msg=="ask")
            {
                cout<<"中年男子介绍说自己姓叶，是生物学院的教授，昨天叫学生来实验室做生意，没想到来的时候已经变成了丧尸，他不知道怎么回事"
                        "赶忙把他锁在了门外，自己也一直不敢出去，一直躲在实验室里研发解药。你心想：解药？该不会是这些花花绿绿的管子吧？"
                        "他接着说道：你们应该也想出去吧？可惜现在学校出口都是丧尸把守，我建议你们去旧管理学院楼，就是浙大启真湖旁边最高的那个建筑"
                        "，的楼顶上去看一看，那里视野好，可以看看有没有出路，或者向外面求救也是比较容易发现的。小语很激动：确实是个好主意！"
                        "您也跟我们一起去吧。叶教授无奈的笑了笑，说：算了，老了。我去会给你们添负担，我还是研发解药吧，说不定还能解救感染的同学。"
                        "哦对了，那里挺远的，我的车停在楼下了，你们要用可以开！说完丢给了我们一串车钥匙。"
                        "你看了看眼前的叶教授，觉得他说的确实有道理，但总感觉哪里怪怪的。算了，还是先去看看吧。"<<endl;
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
                cout<<"你和小语离开了实验室，回到生物大楼楼下。"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 检查实验室情况\nask: 询问教授情况\npick red tube: 偷偷揣走红色试管\npick green tube: 偷偷揣走绿色试管\n"
                        "leave: 离开实验室"<<endl;
                return;
            }
        }
        else if(pl.get_status()==BIO_LEAVE)
        {
            if(msg=="look")
            {
                cout<<"楼下，零散地停着自行车和小龟，还有旁边叶教授的私家车。走去管院太消耗体力，可是你也不太信任叶教授。"<<endl;
                return;
            }
            else if(msg=="take e-bike")
            {
                cout<<"小龟没电了！"<<endl;
                return;
            }
            else if(msg=="take bike")
            {
                Vehicle* v= new Vehicle("自行车",20,0);
                pl.take_vehicle(v);
                return;
            }
            else if(msg=="take car")
            {
                Vehicle*v =new Vehicle("私家车",50,0);
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
                cout<<"你和小语来到了管院，似乎没什么丧尸，坐电梯来到了楼顶"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 检查路边情况\ntake bike: 骑上自行车(好像离目的地有点远)\ntake e-bike: 骑小龟\n"
                        "take car: 开叶教授的私家车\nget off: 离开交通工具\ngoto roof: 前往旧管院楼顶"<<endl;
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