#include <FightHandler.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <GraphicsHandler.h>
#include <Entity.h>
using namespace std;
using namespace sf;

FightHandler::FightHandler()
{
    init();
}
void FightHandler::init()
{
    mapFile.open("Battlefield.txt");
    char mapChar;
    int x = 0;
    int y = 0;
    cout<<'\n';
    while(y!=(ysize-1)||x!=xsize)
    {
        mapFile.get(mapChar);
        if(mapChar == '\n')
        {
            x = 0;
            y++;
        } else
        {
            field[x][y] = mapChar;
            x++;
        }
        cout<<mapChar;
        if(y==(ysize-1)&&x==(xsize-1)) {
            mapFile.close();
        }
    }
}
void FightHandler::fight(GraphicsHandler &handler)
{
    int x = 3;
    int xpos = x*63;
    int y = 3;
    int ypos = y*63;
    const float timestep = .2;
    bool cont = true;

    Entity party[4];
    party[0] = Entity("TestPlayer", 5, 3, 5, 3, 2);
    party[0].setPos(4,4);
    party[1] = Entity("TestPlayer", 5, 3, 5, 3, 2);
    party[1].setPos(6,4);
    Entity enemy[4];
    enemy[0] = Entity("TestEnemy", 5, 3, 5, 3, 2);
    enemy[0].setPos(6,7);
    enemy[1] = Entity("TestEnemy", 5, 3, 5, 3, 2);
    enemy[1].setPos(10,6);


    Event event = Event();
    bool ev = true;
    int moves[2];
    moves[0] = 0;
    moves[1] = 0;
    int selected = 0;
    int selec = -1;
    for(int x = 0; x < xsize; x++)
    {
        for(int y = 0; y < ysize; y++)
        {
            if(field[x][y] == '.')
            {
                infoMap[x][y] = 'N';
            } else
            {
                infoMap[x][y] = 'Y';
            }
        }
    }
    for(int i = 0; i<4; i++)
    {
        infoMap[party[i].xpos][party[i].ypos] = 'N';
        infoMap[enemy[i].xpos][enemy[i].ypos] = 'N';
    }
    handler.updateBattle(selected, moves, infoMap, 0, field, xpos, ypos, party, enemy);
    //Fight loop
    do
    {
        handler.getWindow().waitEvent(event);
        switch(event.type)
        {
        case Event::Closed:
            handler.getWindow().close();
            cont = false;
            break;
        case Event::TextEntered:
            char a;
            if (event.text.unicode < 128) { a = static_cast<char>(event.text.unicode); }
            if(!selected)
            {
                switch(a)
                {
                case 'w':
                    if(field[x][y-1] != '.'){
                        for(int i=1; i<=63; i++)
                        {
                            if(updateStep.getElapsedTime().asSeconds() > timestep/63.0)
                            {
                                updateStep.restart();
                                ypos--;
                                handler.updateBattle(selected, moves, infoMap, 0, field, xpos, ypos, party, enemy);
                            } else { i--;}
                        }
                        y--;
                    }
                    while(ev)
                    {
                        ev = handler.getWindow().pollEvent(event);
                    }
                    ev = true;
                    break;
                case 's':
                    if(field[x][y+1] != '.'){
                        for(int i=1; i<=63; i++)
                        {
                            if(updateStep.getElapsedTime().asSeconds() > timestep/63.0)
                            {
                                updateStep.restart();
                                ypos++;
                                handler.updateBattle(selected, moves, infoMap, 0, field, xpos, ypos, party, enemy);
                            } else { i--;}
                        }
                        y++;
                    }
                    while(ev)
                    {
                        ev = handler.getWindow().pollEvent(event);
                    }
                    ev = true;
                    break;
                case 'a':
                    if(field[x-1][y] != '.'){
                        for(int i=1; i<=63; i++)
                        {
                            if(updateStep.getElapsedTime().asSeconds() > timestep/63.0)
                            {
                                updateStep.restart();
                                xpos--;
                                handler.updateBattle(selected, moves, infoMap, 0, field, xpos, ypos, party, enemy);
                            } else { i--;}
                        }
                        x--;
                    }
                    while(ev)
                    {
                        ev = handler.getWindow().pollEvent(event);
                    }
                    ev = true;
                    break;
                case 'd':
                    if(field[x+1][y] != '.'){
                        for(int i=1; i<=63; i++)
                        {
                            if(updateStep.getElapsedTime().asSeconds() > timestep/63.0)
                            {
                                updateStep.restart();
                                xpos++;
                                handler.updateBattle(selected, moves, infoMap, 0, field, xpos, ypos, party, enemy);
                            } else { i--;}
                        }
                        x++;
                    }
                    while(ev)
                    {
                        ev = handler.getWindow().pollEvent(event);
                    }
                    ev = true;
                    break;
                case 'e':
                    handler.getWindow().close();
                    cont = false;
                    break;
                }
            } else
            {
                switch(a)
                {
                case 'w':
                    if(field[x][y+moves[0]-1] != '.'&&(abs(moves[0]-1)+abs(moves[1])<=party[selec].mov)){
                        moves[0]--;
                    }
                    break;
                case 's':
                    if(field[x][y+moves[0]+1] != '.'&&(abs(moves[0]+1)+abs(moves[1])<=party[selec].mov)){
                        moves[0]++;
                    }
                    break;
                case 'a':
                    if(field[x+moves[1]-1][y] != '.'&&(abs(moves[0])+abs(moves[1]-1)<=party[selec].mov)){
                        moves[1]--;
                    }
                    break;
                case 'd':
                    if(field[x+moves[1]+1][y] != '.'&&(abs(moves[0])+abs(moves[1]+1)<=party[selec].mov)){
                        moves[1]++;
                    }
                    break;
                case 'e':
                    cont = false;
                    handler.getWindow().close();
                    break;
                }
            }
            break;
        case Event::KeyPressed:
            if(event.key.code == Keyboard::Enter) {
                    if(!selected)
                    {
                        for(int i = 0; i<4; i++)
                        {
                            if((x == party[i].xpos && y == party[i].ypos) || (x == enemy[i].xpos && y == enemy[i].ypos))
                            {
                                selec = i;
                                selected = 1;
                            }
                        }

                    } else
                    {
                        if(infoMap[x+moves[1]][y+moves[0]] == 'Y' || (party[selec].xpos == x + moves[1] && party[selec].ypos == y+moves[0]))
                        {
                            infoMap[x][y] = 'Y';
                            x += moves[1];
                            y += moves[0];
                            xpos += moves[1]*63;
                            ypos += moves[0]*63;
                            infoMap[x][y] = ((party[selec].xpos == x + moves[1] && party[selec].ypos == y+moves[0])? 'Y' : 'N');
                            party[selec].xpos = x;
                            party[selec].ypos = y;
                            handler.updateBattle(0, moves, infoMap, party[selec].mov, field, xpos, ypos, party, enemy);
                            handler.getWindow().display();
                            attack(handler, party[selec], enemy, x, y);
                        }
                        selected = 0;
                    }
                    moves[0] = 0;
                    moves[1] = 0;
            }
            break;
        default:
            continue;
            break;
        }
        handler.updateBattle(selected, moves, infoMap, party[selec].mov, field, xpos, ypos, party, enemy);
    } while(cont);
}
bool FightHandler::attack(GraphicsHandler &handler, Entity &player, Entity (&enemy)[4], int x, int y)
{
    int selection = 0;

    Entity inRange[4];
    int c = -1;
    for(Entity a : enemy)
    {
        if(abs(a.xpos-x)+abs(a.ypos-y) <= player.range)
        {
            c++;
            inRange[c] = a;
        }
    }
    if(inRange[0].health <=0)
    {
        return false;
    }
    handler.updateAttack(enemy, selection);
    Event event = Event();
    do
    {
        handler.getWindow().waitEvent(event);
        switch(event.type)
        {
        case Event::Closed:
            handler.getWindow().close();
            break;
        case Event::TextEntered:
            char a;
            if (event.text.unicode < 128) { a = static_cast<char>(event.text.unicode); }
            switch(a)
            {
            case 'a':
                if(selection!=0) {selection--; handler.updateAttack(inRange, selection);}

                break;
            case 'd':
                if(selection!=c) {selection++; handler.updateAttack(inRange, selection);}

                break;
            case 'e':
                handler.getWindow().close();
                break;
            }
        case Event::KeyPressed:
            if(event.key.code == Keyboard::Enter)
            {
                battle(player, inRange[selection], handler);
                return true;
            } else if(event.key.code == Keyboard::Escape)
            {
                return true;
            }
            break;
        default:
            continue;
            break;
        }
    } while(handler.getWindow().isOpen());
    return false;
}
bool FightHandler::battle(Entity &player, Entity &enemy, GraphicsHandler &handler)
{
    RenderWindow &window = handler.getWindow();
    float timestep = 1;
    float frames = 10;
    for(int i=1; i<=frames; i++)
    {
        if(updateStep.getElapsedTime().asSeconds() > timestep/frames)
        {
            if(i <= frames)
            {
                updateStep.restart();
                //Play animation;
                window.clear();
                window.draw(handler.getSprite(player.name + "Att" + to_string(i)));

                window.display();
            }
        } else { i--;}
    }
    updateStep.restart();
    while(updateStep.getElapsedTime().asSeconds()<3){}
    return false;
}