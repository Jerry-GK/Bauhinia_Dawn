#pragma once
#include <string>
using namespace std;

class Food
{
private:
    string name ;
    int effect ;
    int occupancy ;
public:
    Food(const string setname);

    string getname()const ;

    int geteffect()const ;

    int getoccupancy()const ;
    
};
bool isFood(string item) ;