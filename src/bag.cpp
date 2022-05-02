#include "bag.h"

Bag::Bag()
{
    capacity=50;
    wep=NULL;
}

void Bag::show()
{
    cout<<"背包信息："<<endl;
    cout<<"容量："<<capacity<<endl;

}