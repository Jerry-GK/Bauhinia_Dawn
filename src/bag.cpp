#include "bag.h"

Bag::Bag()
{
    maxcapacity = global_initial_Bag_occupancy ;
    bag.clear() ;
}

void Bag::show()
{
    cout << "背包信息：" << endl;
    cout << "剩余容量/最大容量：" << getmaxcapacity() - getcurcapacity() << "/" << getmaxcapacity() <<  endl;
    cout << "拥有：" << endl;
    if(bag.empty())
        cout<<"空"<<endl;
    for (map<string,Info>::iterator p = bag.begin() ; p!= bag.end() ; p++)
    {
        cout << p->first << "*" << p->second->num << "   占用：" << (p->second->size)*(p->second->num)<< endl;
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
bool Bag::add(string item , int item_size)//在背包内添加物品 成功则返回true
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
            } //已经存在这个物品了
        }
        
        //不存在这个物品
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