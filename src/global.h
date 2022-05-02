#pragma once
#include<string>
using namespace std;

static const string info_help=
"��Ҫ��Ϸָ�������\n\
look: �鿴�ܱ����\n\
goto <�ص�Ӣ����>: ǰ��ĳ���ط�\n\
check: �鿴��������״̬(ͨ��)\n\
map: �鿴��ͼ(ͨ��)\n\
bag: �鿴��ǰ��������(ͨ��)\n\
use <��ƷӢ����>: ʹ�ñ����е���Ʒ(ͨ��)\n\
hint: ������ǰ��ȷ������ʾ(ͨ��)\n\
quit: �˳���Ϸ(ͨ��)";

static const string info_invalid="�����ָ����Ч��(������-help�鿴ͨ�úϷ�ָ��)";
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


enum GAME_STAGE//��Ϸ��ǰ״̬��ö������
{
    BEGIN,
    DIE,
    PASS,
    END
};

enum PLAYER_STAGE
{
    //dormitory
    UNKNOWN,
    DOR_WAKE_UP,
    DOR_TO_LOOK_OUTSIDE,
    DOR_TO_CHOOSE,
    MARKET_SEARCH,
    MARKET_ASK
};