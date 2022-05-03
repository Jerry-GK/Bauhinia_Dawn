#pragma once
#include <iostream>
#include <map>
#include <string>
#include "global.h"
using namespace std;

class Bag
{
protected:
    int maxcapacity;
    int curcapacity = 0 ;
    map <string,int> bag ; //<名字，占用大小>
public:
    Bag();
    void show();
    bool find(string item);
    void det (string item);
    bool add (string item , int item_size); //在背包内添加物品 成功则返回true
    //这些函数用了迭代器指向bag.begin（）,不能加const
    int getcurcapacity () const ;
    int getmaxcapacity () const ;
};  