#include "game_map.h"

void GameMap::add_pos(Position p)
{
    this->vpos.insert(make_pair(p.name,p));
}

Position* GameMap::get_pos(string name)
{
    return &(vpos.find(name)->second);
}

void GameMap::show()
{
    cout<<"地图信息(精简版)："<<endl;
    for(map<string,Position>::iterator it=vpos.begin();it!=vpos.end();it++)
    {
        cout<<it->first<<" 坐标("<<it->second.x<<", "<<it->second.y<<")"<<endl;
    }
}

void Position::set(string name,double x,double y)
{
    this->name=name;
    this->x=x;
    this->y=y;
    status.clear();
}
void Position::add_status(PLAYER_STAGE s)
{
    status.push_back(s);
}
string Position::get_name()
{
    return this->name;
}

vector<PLAYER_STAGE> Position::get_status()
{
    return this->status;
}