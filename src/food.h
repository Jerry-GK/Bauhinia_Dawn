#pragma once
#include <string>
#include <iostream>
#include "global.h"
using namespace std;

class Food
{
protected:
    string name ;
    int occupancy ;
public:
    Food(const string setname, const int setoccupancy);
    string getname()const ;
    int getoccupancy()const ;
    virtual void show() const;
    virtual ~Food() = 0;

    static Food* new_food(string name);
    static bool isFood(string item) ;
};

class Bread : public Food
{
private:
    int effect;
    int cost;
public:
    Bread();
    int geteffect() const;
    int getcost() const;
    void show() const;
};

class Apple : public Food
{
private:
    int effect;
    int cost;
public:
    Apple();
    int geteffect() const;
    int getcost() const;
    void show() const;
};

class RedTube : public Food
{
public:
    RedTube();
    void show() const;
};

class GreenTube : public Food
{
public:
    GreenTube();
    void show() const;
};