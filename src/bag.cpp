#include "bag.h"

Bag::Bag()
{
    maxcapacity = global_initial_Bag_occupancy ;
    bag.clear() ;
}

void Bag::show()
{
    cout << "������Ϣ��" << endl;
    cout << "ʣ������/���������" << getmaxcapacity() - getcurcapacity() << "/" << getmaxcapacity() <<  endl;
    cout << "ӵ�У�" << endl;
    if(bag.empty())
        cout<<"��"<<endl;
    for (map<string,Info>::iterator p = bag.begin() ; p!= bag.end() ; p++)
    {
        cout << p->first << "*" << p->second->num << "   ռ�ã�" << (p->second->size)*(p->second->num)<< endl;
    }

}
bool Bag::find(string item) 
{
    for (map<string,Info>::iterator p = bag.begin() ; p!= bag.end() ; p++)
    {
        if (item == p->first) {return true ;}
    }
    return false ;
}
void Bag::det(string item)
{
    for (map<string,Info>::iterator p = bag.begin() ; p!= bag.end() ; p++)
    {
        if (item == p->first)
        {
            curcapacity -= p->second->size ;
            if (p->second->num == 1)
            {
                delete p->second ;
                bag.erase (p);
            }
            else
            {
                p->second->num -- ;
            }
            break ;
        }
    }
}
bool Bag::add(string item , int item_size)//�ڱ����������Ʒ �ɹ��򷵻�true
{
    if (curcapacity + item_size > maxcapacity)
    {
        return false ;
    }
    else
    {
        curcapacity += item_size ;
        for (map<string,Info>::iterator p = bag.begin() ; p!= bag.end() ; p++)
        {
            if (item == p->first)
            {
                p->second->num ++ ;
                return true ;
            } //�Ѿ����������Ʒ��
        }
        
        //�����������Ʒ
        Info p = new struct info;
        p->num = 1 ;
        p->size = item_size ;
        bag.insert(pair<string,Info> (item,p) );
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
map <string,Info> Bag::getbag() const 
{
    return bag ;
}