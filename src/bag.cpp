#include "bag.h"

Bag::Bag()
{
    maxcapacity = initial_Bag_occupancy ;
    bag.clear() ;
}

void Bag::show()
{
    cout << "背包信息：" << endl;
    cout << "当前容量/最大容量：" << getcurcapacity() << "/" << getmaxcapacity() <<  endl;
    cout << "拥有：" << endl;
    for (map<string,int>::iterator p = bag.begin() ; p!= bag.end() ; p++)
    {
        cout << p->first << "   占用：" << p->second << endl;
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
}//只删除一个

bool Bag::add(string item , int item_size)//在背包内添加物品 成功则返回true
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