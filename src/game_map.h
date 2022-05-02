#pragma once
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include "global.h"
using namespace std;

class Position;

class GameMap
{
private:
    map<string, Position> vpos;
public:
    void add_pos(Position p);
    Position* get_pos(string name);
    void show();
};

class Position
{
private:
    string name;
    double x;
    double y;
    vector<PLAYER_STAGE> status;  
public:
    void set(string name,double x,double y);

    void add_status(PLAYER_STAGE s);

    string get_name();
    
    vector<PLAYER_STAGE> get_status();
    
    friend class GameMap;
};

