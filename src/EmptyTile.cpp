#include <EmptyTile.h>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

EmptyTile::EmptyTile(string name)
{
    ID = name;
}
string EmptyTile::enter()
{
    cout<<ID;
    return ID;
}
