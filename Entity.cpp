#include <Entity.h>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Entity::Entity()
{
    name = "N";
    health = -1;
    strength = -1;
    speed = 0;
    xpos = -1;
    ypos = -1;
    hasMoved = true;
    isAlive = false;
}
Entity::Entity(string nam, int healt, int strengt, int def, int pir, int har, int spee, int moves, int rang)
{
    name = nam;
    health = healt;
    strength = strengt;
    speed = spee;
    mov = moves;
    range = rang;
    hasMoved = false;
    pierce = pir;
    hard = har;
    defence = def;
    isAlive = true;
}
void Entity::setPos(int x, int y)
{
    xpos = x;
    ypos = y;
}
void Entity::attack(Entity &enemy, string a, string d)
{
    int mult = 1;
    bool bbreak = false;
    if(pierce>enemy.hard)
    {
        bbreak = true;
    }
    if(a == "DL")
    {
        mult*=8;
        if(d == "DL")
        {
            mult *= 2;
        } else if(d == "L")
        {
            mult *= 5;
        } else if(d == "UL")
        {
            mult *= 5;
        } else if(d == "D")
        {
            mult *= 6;
        } else if(d == "U")
        {
            mult *= 0;
        } else if(d == "R")
        {
            mult *= 4;
        }
    } else if(a == "L")
    {
        mult*=8;
        if(d == "DL")
        {
            mult *= 3;
        } else if(d == "L")
        {
            mult *= 1;
        } else if(d == "UL")
        {
            mult *= 3;
        } else if(d == "D")
        {
            mult *= 4;
        } else if(d == "U")
        {
            mult *= 4;
        } else if(d == "R")
        {
            mult *= 7;
        }
    } else if(a == "UL")
    {
        mult*=8;
        if(d == "DL")
        {
            mult *= 5;
        } else if(d == "L")
        {
            mult *= 5;
        } else if(d == "UL")
        {
            mult *= 2;
        } else if(d == "D")
        {
            mult *= 0;
        } else if(d == "U")
        {
            mult *= 6;
        } else if(d == "R")
        {
            mult *= 4;
        }
    } else if(a == "U")
    {
        mult*=7;
        if(d == "DL")
        {
            mult *= 3;
        } else if(d == "L")
        {
            mult *= 3;
        } else if(d == "UL")
        {
            mult *= 3;
        } else if(d == "D")
        {
            mult *= 8;
        } else if(d == "U")
        {
            mult *= 8;
        } else if(d == "R")
        {
            mult *= 0;
        }
    } else if(a == "UR")
    {
        mult*=6;
        if(d == "DL")
        {
            mult *= 7;
        } else if(d == "L")
        {
            mult *= 5;
        } else if(d == "UL")
        {
            mult *= 3;
        } else if(d == "D")
        {
            mult *= 0;
        } else if(d == "U")
        {
            mult *= 9;
        } else if(d == "R")
        {
            mult *= 5;
        }
    } else if(a == "R")
    {
        mult*=6;
        if(d == "DL")
        {
            mult *= 6;
        } else if(d == "L")
        {
            mult *= 5;
        } else if(d == "UL")
        {
            mult *= 6;
        } else if(d == "D")
        {
            mult *= 4;
        } else if(d == "U")
        {
            mult *= 4;
        } else if(d == "R")
        {
            mult *= 5;
        }
    } else if(a == "DR")
    {
        mult*=6;
        if(d == "DL")
        {
            mult *= 3;
        } else if(d == "L")
        {
            mult *= 5;
        } else if(d == "UL")
        {
            mult *= 7;
        } else if(d == "D")
        {
            mult *= 9;
        } else if(d == "U")
        {
            mult *= 0;
        } else if(d == "R")
        {
            mult *= 5;
        }
    }
    int dmg = (strength*mult)/10-(bbreak?0:enemy.defence);
    dmg = (dmg>0?dmg:0);
    cout<<"attacked for "<<dmg<<" damage"<<'\n'<<mult<<"  "<<strength<<"  "<<enemy.defence<<"  ";
    cout<<a<<"  "<<d<<"  "<<'\n';
    enemy.health-=dmg;
    if(enemy.health<=0)
    {
        enemy.isAlive = false;
        cout<<"enemy was killed"<<'\n';
    }
}
