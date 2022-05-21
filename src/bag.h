#pragma once
#include <iostream>
#include <map>
#include <string>
#include "global.h"

using namespace std;

struct info
{
    int size ; //ռ�ô�С
    int num = 0; //����
};
typedef info* Info ;
class Bag
{
protected:
    int maxcapacity;
    int curcapacity = 0 ;
    map <string,Info> bag ; //<���֣�ռ�ô�С>
public:
    Bag();
    void show();
    bool find(string item);
    void det (string item);
    bool add (string item , int item_size); //�ڱ����������Ʒ �ɹ��򷵻�true
    //��Щ�������˵�����ָ��bag.begin(),���ܼ�const
    int getcurcapacity () const ;
    int getmaxcapacity () const ;
    map <string,Info> getbag() const ;
};  