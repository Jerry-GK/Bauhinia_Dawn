#include "bag.h"

Bag::Bag()
{
    max_capacity=50;
    cur_capacity=max_capacity;
}

void Bag::show()
{
    cout<<"������Ϣ��"<<endl;
    cout<<"���������"<<max_capacity<<endl;
    cout<<"��ǰ������"<<cur_capacity<<endl;
}