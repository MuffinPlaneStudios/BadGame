#include <Events.h>
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
Events::Events()
{
    name = "BlankEvent";
    ID = 0;
}
Events::Events(string eve, int i)
{
    name = eve;
    ID = i;
}

bool Events::dew()
{
    switch(ID)
    {
    case 0:
        return 0;
        break;
    case 1:
        return true;
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    }
}
