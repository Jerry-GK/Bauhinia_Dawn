#pragma once
#include "weapon.h"
#include <iostream>
#include <vector>
#include <string>

class Bag
{
protected:
    int max_capacity;
    int cur_capacity;
    vector<string> items;

public:
    Bag();
    void show();
    void add(string item);
    void del(string item);
};