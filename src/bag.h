#pragma once
#include "weapon.h"
#include <iostream>
#include <vector>
#include <string>

class Bag
{
protected:
    int capacity;
    Weapon* wep;//包里所装的武器数组
    vector<string> others;

public:
    Bag();
    void show();
};