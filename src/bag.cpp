#include "bag.h"

Bag::Bag()
{
    maxcapacity = initial_Bag_occupancy ;
    bag.clear() ;
}

void Bag::show()
{
    cout << "������Ϣ��" << endl;
    cout << "��ǰ����/���������" << getcurcapacity() << "/" << getmaxcapacity() <<  endl;
    cout << "ӵ�У�" << endl;
    for (map<string,int>::iterator p = bag.begin() ; p!= bag.end() ; p++)
    {
        cout << p->first << "   ռ�ã�" << p->second << endl;
    }

}
bool Bag::find(string item) 
{
    for (map<string,int>::iterator p = bag.begin() ; p!= bag.end() ; p++)
    {
        if (item == p->first) {return true ;}
    }
    return false ;
}
void Bag::det(string item)
{
    for (map<string,int>::iterator p = bag.begin() ; p!= bag.end() ; p++)
    {
        if (item == p->first)
        {
            curcapacity -= p->second ;
            bag.erase (p);
            break ;
        }
    }
}//ֻɾ��һ��

bool Bag::add(string item , int item_size)//�ڱ����������Ʒ �ɹ��򷵻�true
{
    if (curcapacity + item_size > maxcapacity)
    {
        return false ;
    }
    else
    {
        curcapacity += item_size ;
        bag.insert(pair<string,int>(item,item_size));
        return true ;
    }
}

int Bag::getcurcapacity () const
{
    return curcapacity ;
}
int Bag::getmaxcapacity () const
{
    return maxcapacity ;
}