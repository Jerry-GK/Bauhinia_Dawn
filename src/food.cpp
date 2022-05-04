#include "food.h"

Food::Food(const string setname)
{
    name = setname ;
    if (setname == "bread")
    {
        effect = 5 ;
        occupancy = 2;
    }
    else if (setname == "apple")
    {
        effect = 2 ;
        occupancy = 1 ;
    }
    else if (setname == "red tube")
    {
        effect = -30 ;
        occupancy = 8 ;
    }
        else if (setname == "green tube")
    {
        effect = 30 ;
        occupancy = 8 ;
    }
}
string Food::getname() const
{
    return name ;
}
int Food::geteffect() const 
{
    return effect ;
}
int Food::getoccupancy() const 
{
    return occupancy ;
}
bool isFood(string item)
{
    string Food = "bread#apple#red tube#green tube" ;
    return (Food.find(item) < Food.length() );
}


