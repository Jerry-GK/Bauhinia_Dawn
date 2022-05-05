#include "game.h"

void Game::Init()
{
    show_welcome();
    this->stage=PLAYING;
    //init positions in game map
    Position p;
    p.set("dormitory",0,0);//宿舍
    p.add_status(DOR_TO_LOOK_OUTSIDE);
    //
    game_map.add_pos(p);
    
    p.set("shop",0,0);//超市
    p.add_status(SHOP_SEARCH);
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
    p.add_status(ROOF_HALL);
    //
    game_map.add_pos(p);

    p.set("wharf",0,0);//水上码头
    p.add_status(WHARF_DECIDE);
    //
    game_map.add_pos(p);

    p.set("lake",0,0);//启真湖
    p.add_status(LAKE_ROW);
    //
    game_map.add_pos(p);

    p.set("south gate",0,0);//南门出口
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

void Game::submit()//从对话框读取玩家输入的文本（input_box->msg, clear input_box, call process）
{
    msg=input_box;
    input_box.clear();
    process(msg);
}

//--------------------------Process-----------------------------------
void Game::process(string msg)//根据pos，处理msg文本,最关键的部分，根据地点，划分出小状态
{
    //进入游戏
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
            cout<<"请输入begin开始游戏！"<<endl;
            return;
        }
    }
    //任何场景下都可执行的指令
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
    //非任何场景之下都可执行的指令
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
            else if(msg=="goto shop")
            {
                pl.move_to(game_map.get_pos("shop"));
                show_info(info_to_shop);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look:观察宿舍\npick fork拾取衣叉\npick umbrella拾取雨伞\ngoto shop前往教育超市"<<endl;
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
                cout<<"look:查看超市情况\npick bread:拾取面包\nask:询问收获员情况\n"
                "use bread:可以吃掉一个拾取的面包补充体力\n"
                "pick knife: 购买一把小刀\ngoto dor gate:可以去学园门口（建议吃完面包、询问后再去）"<<endl;
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
                        break;
                    case 1: 
                        pl.move_to(game_map.get_pos("shop"));
                        cout<<"你狼狈地逃回了教育超市,还好丧尸没有追过来。看来还是得准备点物资才能与丧尸再战。"<<endl;
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
            else if(msg=="hint")
            {
                cout<<"look: 查看马路情况\ntake bike: 骑上自行车\ntake e-bike:骑上小龟\ntake car: 乘汽车\n"
                "goto west building: 去西教"<<endl;
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
            Zombie* z=new Zombie("roll");
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
                cout<<"眼前的丧尸双目圆睁，头发不多，牙齿、舌头全变成了瘆人的绿色。小语在旁边说：哥哥好厉害！这个丧尸看起来像个老博,要不要检查他一下呢？"<<endl;
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
                cout<<"你和小语从生科院一路来到旧管院楼顶（现行政楼）。一路上，遇到了无数可怕的丧尸。最后，你们安全到达了这栋高高建筑的一楼大厅。"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 检查路边情况\ntake bike: 骑上自行车(好像离目的地有点远)\ntake e-bike: 骑小龟\n"
                        "take car: 开叶教授的私家车\ngoto roof: 前往旧管院楼顶"<<endl;
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
                cout<<"你向大厅望去，被惊呆了。这里明显有激烈的打斗痕迹，血迹、弹孔到处都是，地上还有一只断手，手里紧紧握着一把枪。"
                        "看来这里发生过恶战。但奇怪的是现在这里似乎并没有丧尸的动静。小语说：要不我们先坐电梯到楼顶看看吧？"
                        "就像叶教授说的，那里视野好，能看到哪个出口丧尸少、有机会逃出去！";
                return;
            }
            else if(msg=="pick gun")
            {
                pl.pick("gun");
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
                cout<<"look: 查看大厅情况\npick gun: 捡起断手中的枪\ngo up: 坐电梯去楼顶"<<endl;
                return;
            }
        }
        else if(pl.get_status()==ROOF_TOP)
        {
            if(msg=="look")
            {
                cout<<"你和小语来到了旧管院的楼顶——这里是浙大的最高点，视野最为开阔。你们向远处望去，浙大全貌一览无余。"
                        "可以看到学校到处都散布着饥肠辘辘的丧尸，你把眼光投向东二门，不出所料，全是丧尸。校医院大门、蓝田大门也是。"
                        "再转过头，南面的东三门、甚至是新建的南大门门口也都围满了丧尸，看来从校门逃出没有任何希望了，你和小语陷入了绝望。"
                        "你盯着启真湖，突然眼前一亮：启真湖的支流弯弯曲曲的向南方流去，流向南华园。小语似乎看懂了你的想法"
                        "忙说：我听说顺着启真湖往南花园方向，有一条隐秘的水路，可以通向学校南边的余杭塘河！也就是说，我们可以通过水路出校！"
                        "你欣喜若狂，冷静下来，说：可是，我们怎么从水路逃跑呢？我们又没有船。小语想了想，说道：水上码头！那里是学校开设的"
                        "水上运动课的上课地点，我恰巧上过，那里有许多皮划艇！"<<endl;
                return;
            }
            else if(msg=="leave")
            {
                pl.set_status(ROOF_LEAVE);
                cout<<"你和小语准备离开大楼，开车前往水上码头，可是确发现了一丝不对劲..."<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 向四周眺望观察学校情况\nleave: 准备离开大楼，开车前往启真湖"<<endl;   
                return;
            }
        }
        else if(pl.get_status()==ROOF_LEAVE)
        {
            if(msg=="look")
            {
                cout<<"来时上楼的电梯好像坏了，楼梯传来嘈杂的声音，再仔细一听，似乎是丧尸的声音！你和小语忙跑回楼顶往下看，"
                        "眼前的景象把你俩吓了个半死：楼下，成群的丧尸正涌入大楼，楼梯里，丧尸的脚步声越来越近..."
                        "怎么会这样？而远处，你居然看到了有一个熟悉的人，他坐在楼下的花坛旁，从容不迫地笑着，丧尸们也不去攻击他。"
                        "而他，竟然是叶教授！"<<endl;
                return;
            }
            else if(msg=="ask")
            {
                cout<<"你疑惑而又愤怒地大声问叶教授这是怎么回事。叶教授邪恶地笑了，说：其实丧尸病毒就是我昨晚研发出来的，用它感染了我实验室的学生"
                        "作为第一批实验对象，他们只用一晚上就感染了全学校。而你们，是目前我发现的仅存的幸存者。所以我诱使你们来到这里，而我能控制"
                        "丧尸，让他们来这里追杀你们。哈哈，我挑的地方不错吧，看你们怎么逃！"<<endl;
                return;
            }
            else if(msg=="jump")
            {
                pl.move_to(game_map.get_pos("wharf"));
                pl.recoverHP(-20);
                cout<<"You jump， I jump！你和小语一起跳到了启真湖，巨大的冲击力让你们差点丧命，用仅剩的一点体力拼命游到了水上码头。"<<endl;
                return;
            }
            else if(msg=="fight")
            {
                cout<<"没想好的多重战斗逻辑，先去跳楼吧"<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看周围情况\nask: 质问叶教授\njump: 拉着小语从楼顶跳到启真湖（很危险），再游去水上码头\nfight: 跟丧尸硬刚，杀下去"<<endl;
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
                cout<<"你们筋疲力竭地爬上了，水上码头，发现这里船只确实不少，还有几块新鲜的苹果。小语挑了一艘看起来比较新的船。"
                        "远处，叶教授在湖对岸气急败坏。你们望向波光粼粼的水面，看起来很宁静，但又似乎隐藏着什么危机。准备好了吗！"<<endl;
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
                    cout<<"当前的交通工具无法在水上行驶！"<<endl;
                    return;
                }
                cout<<"你和小语乘上了皮划艇，划向阳明桥，准备去启真湖心..."<<endl;
                pl.move_to(game_map.get_pos("lake"));
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看码头情况\npick apple: 捡起苹果\ntake boat: 乘船\nrow: 划船去出口\n(建议先use bread补充刚才跳楼损失的体力)"<<endl;
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
                cout<<"你们在船上四处张望，发现叶教授已经不见了，不远处的旧管院楼顶上，也就是你们刚刚在的地方，已经布满了丧尸。"
                        "小语在你旁边，松了口气，说道：总算暂时安全了，哥哥，有你真好。我一定要活着出去见我的爸爸妈妈（一顿提前煽情）。"
                        "你也放松了下来，心想，现在主要划到南面的余杭塘河，就安全了！"<<endl;
                return;
            }
            else if(msg=="goto south gate")
            {
                pl.set_status(LAKE_FIGHT);
                cout<<"你们决定划船去南大门旁的水道，从那里逃出去。可是眼前的景象让你大吃一惊..."<<endl;
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看湖四周情况\ngoto south gate: 准备划到南大门"<<endl;
                return;
            }
        }
        else if(pl.get_status()==LAKE_FIGHT)
        {
            if(msg=="look")
            {
                cout<<"船要想驶向南边，需要穿过阳明桥，可是定睛一看，桥洞里竟然游荡着几只可怕的丧尸，是水丧尸！"
                    "再仔细一看，水丧尸张开瘆人的绿色嘴巴，正发了疯似地向你们游过来。这群水丧尸不仅能游泳，而且看起来更加凶猛！"<<endl;
                return;
            }
            else if(msg=="escape")
            {
                pl.move_to(game_map.get_pos("wharf"));
                cout<<"你和小语赶紧掉头，飞速划向岸边，逃回水上码头。"<<endl;
                return;
            }
            else if(msg=="fight")
            {
                Zombie* z=new Zombie("water");
                pl.fight(z);
                //如果成功打败水丧尸
                cout<<"经过一番激战，你们终于一起击败了水丧尸，可是旁边的小语却捂着胳膊，有些不对劲..."<<endl;
                pl.set_status(LAKE_SAVE);
                return;
            }
            else if(msg=="hint")
            {
                cout<<"look: 查看水丧尸情况\nfight: 与水丧尸战斗、突破封锁\nescape: 掉头逃回水上码头"<<endl;
                return;
            }
        }
        else if(pl.get_status()==LAKE_SAVE)
        {
            if(msg=="look")
            {
                cout<<"你看向小语，发现她的胳膊划开了一道长长的绿色伤口，糟了，刚才的战斗中小语被水丧尸咬伤了！"
                        "小语浑身发抖，眼泪从眼角流下，你望向她，原本水汪汪的眼睛开始泛白，不出几分钟，她就会变成丧尸！"
                        "她抽泣着说到：对不起，我拖累你了，看来我不能陪你逃出去了，釜山行看过没？把我推下船吧，呜呜..."
                        "你脑子一片空白，心里万般悔恨，刚才没有保护好小语。如果不想办法，她就会把自己也咬伤。"
                        "可你看着她，实在不忍心将她推下船，让她永远沉睡在启真湖底。哎，难道真的没有什么办法了吗？"
                        "突然你想到了生物实验室里的那些花花绿绿的瓶子和叶教授的话，会不会有解药？可是，可是，叶教授是坏人啊，"
                        "他真的会研发解药吗？就算会，那到底红色试剂是解药还是绿色试剂是呢？如果用错了，说不一定她会马上变成丧尸，"
                        "把自己咬死。哎，自己当时有没有顺走一瓶？不记得了，看一下背包，赌一下吧！"<<endl;
                return;
            }
            else if(msg=="push")
            {
                cout<<"你一狠心，猛地把小语推了下去。你看到她的眼神一点一点黯淡下去，缓缓沉入水底，而你，独自一人，划向南门..."<<endl;
                this->stage=PARTNER_DIE;
                pl.move_to(game_map.get_pos("south gate"));
                return;
            }
            else if(msg=="give red tube")
            {
                if(!pl.have("red tube"))
                {
                    cout<<"你之前在生物实验室并没有拿走红色试剂"<<endl;
                    return;
                }
                pl.drop("red tube");
                cout<<"小语喝下红色试剂，别看这颜色像鲜血似的，效果竟然很好。小语的伤口奇迹般地愈合了，身体也逐渐回复平静。"
                        "她张开双眼，说到：谢谢你救了我！你心想：这叶教授虽然不干人事，但是留了一手，保有解药，说不定"
                        "是以防万一自己感染备用的，还好当时自己机灵、拿走了一瓶。看到小语安全了，你终于松了一口气。"
                        "跟她一起从隐秘的水路划向南门"<<endl;
                pl.move_to(game_map.get_pos("south gate"));
                return;
            }
            else if(msg=="give green tube")
            {
                if(!pl.have("green tube"))
                {
                    cout<<"你之前在生物实验室并没有拿走绿色试剂"<<endl;
                    return;
                }
                pl.drop("green tube");
                cout<<"小语喝下绿色试剂后，突然双目变白，伤口恶化，全身抽搐。你突然意识到这是叶教授发明的丧尸病毒药剂，就是他诱使学生喝下、产生了第一批丧尸"
                        "可是一切都已经晚了，小语瞬间变成了可怕的丧尸，一口把你咬住，你也变成了丧尸。黎明，不属于你们"<<endl;
                this->stage=DIE;
                return;
            }
            else if(msg=="goto south gate")
            {
                cout<<"受伤的小语躺在船后面，使用解药无望，你奋力划向南门，说不一定到了外面能找到帮助！你划啊划，就快到了。"
                        "你看到了余杭塘河的入口，看到了把学校重重包围的武警，你看到了希望。突然，你背后一痛。你惊愕地回头一望，"
                        "小语正咬着你的肩膀，伤口渗出绿色的液体。她的眼睛已经完全浑浊了，但留下了一滴泪，你听到她轻声说：对，对不起..."
                        "你的视线开始模糊，四肢逐渐无力，最终，也倒在了船上，变成了丧尸...黎明，不属于你们";
                this->stage=DIE;
                return;
            }
            //use red/green tube在全局有
            else if(msg=="hint")
            {
                cout<<"look: 检查小语情况\npush: 将小语推下船\ngive red tube: 给小语服用血红色试剂\ngive green tube: 给小语服用深绿色试剂\n"
                       "goto south gate: 强行带着被咬伤的小语逃向出口\n(可以先输入bag看一下背包里有什么药剂)"<<endl;
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
                cout<<"顺着这条隐秘水路果然划到了南大门旁边的余杭塘河。这条河流是隔离学校与外界的一条河，河水又绿又丑，可现在却十分亲切";
                if(this->stage==PARTNER_DIE)//小语已经死了
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
                cout<<"武警见浑身是血的你打算上岸，没有办法，扣动了扳机，你被击杀了。（没有看过釜山行吗？）"<<endl;
                this->stage=DIE;
                return;
            }
            else if(msg=="sing")
            {
                pl.get_off_vehicle();
                cout<<"你唱起了歌。远处，学校里丧尸横行，天上阴雨蒙蒙，余杭塘河绿色的水面上飘起阵阵歌声。"
                            "武警们听到歌声，犹豫了一会儿，放下了枪，说到：这里还有幸存者，医护人员快来！"
                            "你们被全副武装的武警们冲上去扶住，送往救护车。救护车越开越远，透过车窗，你看到了愈来愈院的"
                            "南大门，浙江大学四个字依稀可见，今天发生的一切仿佛做梦一般，令人不敢相信。";
                if(this->stage==PARTNER_DIE)//独自一人逃出来
                {
                    cout<<"你虽然逃出来了，可是心里怅然弱失。你再次望向学校，想起启真湖底的小语，心情难以平复。"
                            "如果，如果自己能在和丧尸的战斗中保护好小语，哪怕能拿走解药、能选对药，小语也不会在湖底长眠。"
                            "可是，没有那么多如果，最终只有你一人逃出来，你迎来了紫荆的黎明，而她，却沉睡在了永恒的黑夜..."<<endl;
                    this->stage=ALONE_SUC;
                    return;
                }
                else//一起逃出去（最佳结局）
                {
                    cout<<"你转头望向小语，她静静地坐着，也看向你：说道：我们总算逃出来了，不是吗？你笑了，她也笑了。"
                            "或许，这就是你们的紫荆黎明。"<<endl;
                    this->stage=SUC;
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
    show_info(info_invalid);//以上条件均不满足时，判定输入的为非法指令
}
//--------------------------------------------------------------------

bool Game::is_end()const
{
    return this->stage==DIE||this->stage==ALONE_SUC||this->stage==SUC||this->stage==QUIT;
}

void Game::quit()//退出游戏
{
    cout<<"\n游戏结束，谢谢体验！"<<endl;
}