#pragma once
#include <string>

using namespace std;

static const string info_help=
"��Ҫ��Ϸָ�������\n\
-------------����ָ���Ҫ���ض�����������ʾʹ�ã�-------------\n\
begin: ������Ϸ\n\
goto <�ص�Ӣ����>: ǰ��ĳ���ط�\n\
pick <��Ʒ��>: ʰȡ��ߵ�ĳ����Ʒ\n\
take <��ͨ����Ӣ����>: ������ߵĽ�ͨ����\n\
-------------ͨ��ָ������������Կ�ʹ�ã�-------------\n\
look: �鿴�ܱ����\n\
check: �鿴��������״̬(ͨ��)\n\
map: �鿴��ͼ(ͨ��)\n\
bag: �鿴��ǰ��������(ͨ��)\n\
use <��ƷӢ����>: ʹ�ñ����е���Ʒ(ͨ��)\n\
drop <��ƷӢ����>: ���������е���Ʒ(ͨ��)\n\
get off <��ͨ����Ӣ����>: �뿪��ǰ�Ľ�ͨ����\n\
hint: ������ǰ��ȷ������ʾ(ͨ��)\n\
quit: �˳���Ϸ(ͨ��)\n\
-------------����ָ���������ʹ�ã�-------------\n\
sudo goto <�ص�Ӣ����>: ǿ����ת��ĳ���ص㳡��\n\
sudo pick <��ƷӢ����>: ǿ��ʰȡ��Ʒ\n\
sudo take <��ͨ����Ӣ����>: ǿ�Ƴ�����ͨ����\n\
";

static const string info_invalid="�����ָ����Ч��(������help�鿴һ��Ϸ�ָ��, ����hint�鿴��ǰ������ʾ)";
static const string info_welcome="��ӭ�������Ͼ�������! (����begin��ʼ��Ϸ)";
static const string info_bye="лл���飡";
static const string info_wake_up="����С�����������ϵ��һ����ͨ���ѧ����ס�ڱ̷塣���������������Ѷ���ȥ���ˣ�ֻ�����������ᡣ���Ͼŵ㣬����\
����һ��ģģ���������������Ӻܶ�������ܰ����ƺ������������е����죬��������ϴ������׼��ȥ��ѧ¥��ϰ��ͻȻ������ѧ¥����\
��һ���ҽ�......";
static const string info_look_outside="�㼱æ������ȥ���������𾪵�һĻ�����⣬һȺɥʬ���ڷ��˺ҧһ��ѧ��������ѧ����������ҽУ�����������ʧȥ��\
���󣬱�ø���Ⱥɥʬһ��������ʶ����ѧУ�����˿��µ�ɥʬ���������������취�ӳ�ȥ��\n�����ѡ��\nlook���鿴��Χ���\ngoto market: ǰ���������й۲�";

static const string info_look_around="�㱳���Լ�����������ȥ�����о���Ҫ��һЩ׼�����㿴�˿����ܣ��������ƺ�ûʲô�Եģ�Ҳûʲô��������������������ϸ����\
�ƺ�ֻ��������²�(fork)���������Լ���ɡ����������ǿ��Щ��������Ҫ��Ҫ�����أ�����ֱ��ǰ�����У�";

static const string info_to_market="����������������ɥʬ�����ߣ�һ·С��������ѧ԰��ǰ�������������";
static const string info_look_market="���ڳ������ܿ��˿������ҵ��ǣ��ۻ�Աû�б��ɥʬ��������������׷�����ʲô��ɥʬҲ�ƺ�\
�Գ����������ʳ�ﲻ����Ȥ��ֻ�������治��Ѳ�ߡ��������кܶ����������ò��С�";

static const string info_saleman="�ۻ�Ա�����㣺����ȥ���̿�����û���Ҵ��ߡ�";
static const string info_to_gate="���뿪���У����������ſڣ����ǻ��Ǳ�ɥʬ�����ˣ�һֻɥʬ�������������ƺ��޴�������......";

static const string info_fight_suc="���þ���ȫ����ɥʬ����������ǰ�����ˣ���Ҳ��������������û�б�ҧ����������ѧ԰��ǰ��·�ԣ��������ܿ���һ�ˣ�ֻ��\
Զ����Լ�м�ֻɥʬ������Ŀ�ĵ����š�����ȥ���̣��ɲ�ȷ���Լ��������ܷ�֧���Լ��ߵ���";
static const string info_goto_west="�����������̣���ǰ�ľ���������һ��......";

enum GAME_STAGE//��Ϸ��ǰ״̬��ö������
{
    BEGIN,
    DIE,
    PASS,
    END
};

enum PLAYER_STAGE
{
    UNKNOWN,
    //dormitory
    DOR_WAKE_UP,
    DOR_TO_LOOK_OUTSIDE,
    DOR_TO_CHOOSE,
    //market
    MARKET_SEARCH,
    MARKET_ASK,
    //dor gate
    GATE_FIGHT,
    GATE_AFTER_FIGHT,
    //west building
    WEST_INTO_BUILDING,
    WEST_MEET,
    WEST_FIGHT,
    WEST_CHECK,
    //bio lab
    BIO_INTO_BUILDING,
    BIO_MEET,
    BIO_LEAVE,
    //roof
    ROOF_HALL,
    ROOF_TOP,
    ROOF_LEAVE,
    //wharf
    WHARF_DECIDE,
    //lake
    LAKE_ROW,
    LAKE_FIGHT,
    LAKE_SAVE,
    //exit
    EXIT_END
};


//��ɫ��
const int initial_speed = 1 ; // ��ʼ�ƶ��ٶ�
const int initial_move_capability = 0 ;// ��ʼ�ƶ�����
const int initial_currentHP = 20 ;// ��ʼ��ǰ����
const int initial_MAXHP = 40 ;// ��ʼ�������
const int initial_EXP[9] = {10,30,60,150,250,350,500,750,1000} ;// �������辭��
const int initial_Bag_occupancy = 999999;
