#pragma once
#include "weapon.h"
#include <iostream>
#include <vector>
#include <string>

class Bag
{
protected:
    int capacity;
    Weapon* wep;//������װ����������
    vector<string> others;

public:
    Bag();
    void show();
};