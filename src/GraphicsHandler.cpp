#include <GraphicsHandler.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <Map.h>
#include <Entity.h>

using namespace sf;
using namespace std;

map<string, Texture> texts;
int tcount;
const int xwin = 25;
const int ywin = 15;
RenderWindow window(VideoMode(xwin*63+200,ywin*63), "Just Work");

void GraphicsHandler::init()
{
    Texture temp = Texture();
    string stex[] = {"AttackCursor", "MoveMarker", "MoveTile","TestTile","Cursor","UI","BlankTile","NormalTile","ShopTile","RandTile","RestTile","BossTile","MysteryTile"};
    Clock c;
    float tc = 0;
    for(string a : stex)
    {
        c.restart();
        cout<<'\n'<<"LOADING "<<a<<'\n';
        temp.loadFromFile("Images/" + a + ".png");
        texts[a] = temp;
        tcount++;
        tc+=c.getElapsedTime().asSeconds();
        cout<<c.getElapsedTime().asMicroseconds();
    }
    string chars[] = {"TestPlayer", "TestEnemy"};
    for(string a : chars)
    {
        temp.loadFromFile("Images/" + a + "/" + a + ".png");
        texts[a] = temp;
        tcount++;
        for(int i = 1; i <= 10; i++)
        {
            temp.loadFromFile("Images/" + a + "/" + a + "Att" + to_string(i) + ".png");
            texts[a + "Att" + to_string(i)] = temp;
            tcount++;
        }
    }
    cout<<'\n'<<"LOADED "<<tcount<<" textures in "<<tc<<" seconds.";
    RenderTexture texmap;
    texmap.create(m.xsize*63, m.ysize*63);
    for(int x = 0; x < m.xsize; x++)
    {
        for(int y = 0; y < m.ysize; y++)
        {
            texmap.draw(getSprite(m.tmap[x][y], x*63, y*63));
            texmap.display();
        }
    }
    texts["TileMap"] = texmap.getTexture();
}
Sprite GraphicsHandler::getSprite(string a, int x, int y)
{
    Sprite temp = Sprite(texts[a]);
    temp.setPosition(x,y);
    return temp;
}
void GraphicsHandler::updateBattle(int state, int moves[2], char infoMap[25][15], int mov, char field[25][15], int xpos, int ypos, Entity party[4], Entity enemy[4])
{
    window.clear();
    int xs = 25;
    int ys = 15;
    for(int x = 0; x < xs; x++)
    {
        for(int y = 0; y < ys; y++)
        {
            switch(field[x][y])
            {
            case '.':
                window.draw(getSprite("BlankTile", x*63, y*63));
                break;
            case '#':
                window.draw(getSprite("TestTile", x*63, y*63));
                break;
            default:
                window.draw(getSprite("BlankTile", x*63, y*63));
                break;
            }
        }
    }
    window.draw(getSprite("UI",xwin*63));
    for(int x = 0; x<4; x++)
    {
        if(party[x].health >0) { window.draw(getSprite(party[x].name, party[x].xpos*63, party[x].ypos*63));}
    }
    for(int x = 0; x<4; x++)
    {
        if(enemy[x].health >0) { window.draw(getSprite(enemy[x].name, enemy[x].xpos*63, enemy[x].ypos*63));}
    }
    if(state == 1)
    {
        int yc;
        for(int y = ypos/63-mov; y <= ypos/63; y++)
        {
            yc = y-ypos/63+mov;
            for(int x = xpos/63-yc; x <= xpos/63+yc; x++)
            {
                if(x < 25 && y < 15 && x >= 0 && y >= 0 && infoMap[x][y] == 'Y')
                {
                    window.draw(getSprite("MoveTile", x*63, y*63));
                }
            }
        }
        for(int y = ypos/63; y <= ypos/63+mov; y++)
        {
            yc = y-ypos/63;
            for(int x = xpos/63-mov+yc; x <= xpos/63+mov-yc; x++)
            {
                if(x < 25 && y < 15 && x >= 0 && y >= 0 && infoMap[x][y] == 'Y')
                {
                    window.draw(getSprite("MoveTile", x*63, y*63));
                }
            }
        }
        for(int x = (moves[1]<0?moves[1]:0); x<=(moves[1]<0?0:moves[1]);x++)
        {
            window.draw(getSprite("MoveMarker", xpos+x*63, ypos));
        }
        for(int y = (moves[0]<0?moves[0]:0); y<=(moves[0]<0?0:moves[0]);y++)
        {
            window.draw(getSprite("MoveMarker", xpos+moves[1]*63, ypos+y*63));
        }
    }
    window.draw(getSprite("Cursor",xpos,ypos));
    window.display();
}
void GraphicsHandler::updateAttack(Entity enemy[4], int selection)
{
    for(int x = 0; x<4; x++)
    {
        window.draw(getSprite(enemy[x].name, enemy[x].xpos*63, enemy[x].ypos*63));
    }
    window.draw(getSprite("AttackCursor", enemy[selection].xpos*63, enemy[selection].ypos*63));
    window.display();
}
void GraphicsHandler::updateMap(int xpos, int ypos)
{
    window.clear();
    window.draw(Sprite(texts["TileMap"], Rect<int>(xpos-(((xwin-1)/2)*63),ypos-(((ywin-1)/2)*63), xwin*63, ywin*63)));
    window.draw(getSprite("UI",xwin*63));
    window.draw(getSprite("TestPlayer",((xwin-1)/2)*63,((ywin-1)/2)*63));
    window.display();
}
RenderWindow &GraphicsHandler::getWindow()
{
    RenderWindow &w = window;
    return w;
}
