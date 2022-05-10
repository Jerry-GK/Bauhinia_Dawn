#include "game_map.h"

void GameMap::add_pos(Position p)
{
    this->vpos.insert(make_pair(p.name,p));
}

Position* GameMap::get_pos(string name)
{
    if(vpos.find(name)==vpos.end())
    {
        return NULL;
    }
    return &(vpos.find(name)->second);
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

double Position::getX () const
{
    return x ;
}

double Position::getY () const
{
    return y ;
}