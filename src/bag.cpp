#include "bag.h"

Bag::Bag()
{
    max_capacity=50;
    cur_capacity=max_capacity;
}

void Bag::show()
{
    cout<<"背包信息："<<endl;
    cout<<"最大容量："<<max_capacity<<endl;
    cout<<"当前容量："<<cur_capacity<<endl;
}