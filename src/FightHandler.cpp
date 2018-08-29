#include <FightHandler.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <GraphicsHandler.h>
#include <Entity.h>
#include <cstdlib>
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
    bool isPlayerTurn = true;
    Entity party[4];
    party[0] = Entity("TestPlayer", 5, 3, 1, 2, 2, 5, 3, 2);
    party[0].setPos(4,4);
    party[1] = Entity("TestPlayer", 5, 3, 1, 2, 2, 5, 3, 2);
    party[1].setPos(6,4);
    Entity enemy[4];
    enemy[0] = Entity("TestEnemy", 5, 3, 1, 2, 2, 5, 3, 2);
    enemy[0].setPos(6,7);
    enemy[1] = Entity("TestEnemy", 5, 3, 1, 2, 2, 5, 3, 2);
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
        infoMap[party[i].xpos][party[i].ypos] = party[i].isAlive?'N':'Y';
        infoMap[enemy[i].xpos][enemy[i].ypos] = enemy[i].isAlive?'N':'Y';
    }
    handler.updateBattle(selected, moves, infoMap, 0, field, xpos, ypos, party, enemy);
    //Fight loop
    do
    {
        do
        {
            isPlayerTurn = false;
            for(Entity pla : party)
            {
                if(!pla.hasMoved&&pla.isAlive)
                {
                    isPlayerTurn = true;
                }
            }
            if(!isPlayerTurn) {break;}
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
                        isPlayerTurn =false;
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
                        isPlayerTurn = false;
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
                                if((x == party[i].xpos && y == party[i].ypos)&&!party[i].hasMoved)
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
                                infoMap[x][y] = 'N';
                                party[selec].xpos = x;
                                party[selec].ypos = y;
                                bool ret = attack(handler, party[selec], enemy, x, y,party);
                                if(ret)
                                {
                                    infoMap[x][y] = 'Y';
                                    x -= moves[1];
                                    y -= moves[0];
                                    xpos -= moves[1]*63;
                                    ypos -= moves[0]*63;
                                    infoMap[x][y] = ((party[selec].xpos == x - moves[1] && party[selec].ypos == y-moves[0])? 'N' : 'Y');
                                    party[selec].xpos = x;
                                    party[selec].ypos = y;
                                } else { party[selec].hasMoved = true;}
                                handler.updateBattle(0, moves, infoMap, party[selec].mov, field, xpos, ypos, party, enemy);
                                handler.getWindow().display();
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
        } while(isPlayerTurn&&cont);
        cont = false;
    } while(cont);
}
bool FightHandler::attack(GraphicsHandler &handler, Entity &player, Entity (&enemy)[4], int x, int y, Entity (&party)[4])
{
    handler.getWindow().display();
    int selection = 0;
    int inRange[4];
    int c = -1;
    for(int i = 0; i<4;i++)
    {
        if((abs(enemy[i].xpos-x)+abs(enemy[i].ypos-y)) <= player.range)
        {
            if(enemy[i].isAlive)
            {
                c++;
                inRange[c] = i;

            }
        }
    }
    cout<<c;
    if(c==-1)
    {
        return false;
    }
    handler.updateBattle(infoMap,field,party,enemy,inRange[selection]);
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
                if(selection!=0) {selection--; handler.updateBattle(infoMap,field,party,enemy,inRange[selection]);}

                break;
            case 'd':
                if(selection!=c) {selection++; handler.updateBattle(infoMap,field,party,enemy,inRange[selection]);}

                break;
            case 'e':
                handler.getWindow().close();
                break;
            }
        case Event::KeyPressed:
            if(event.key.code == Keyboard::Enter)
            {
                pBattle(player, enemy[inRange[selection]], handler);
                return false;
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
    return true;
}
bool FightHandler::pBattle(Entity &player, Entity &enemy, GraphicsHandler &handler)
{
    RenderWindow &window = handler.getWindow();
    float timestep = 1;
    float frames = 10;
    float wait = .5;
    string edir, pdir;
    pdir = "N";
    Event e = Event();
    while(true)
    {
        window.clear();
        window.draw(handler.getSprite("TestBattleBackground"));
        window.draw(handler.getSprite(enemy.name + "DefendN"));
        window.draw(handler.getSprite(player.name + "Att" + pdir + "1"));
        window.display();
        window.waitEvent(e);
        if(e.type == Event::KeyPressed)
        {
            if(e.key.code == Keyboard::Enter)
            {
                if(pdir!="N") { break;}
            }
            if(Keyboard::isKeyPressed(Keyboard::Right))
            {
                if(Keyboard::isKeyPressed(Keyboard::Up))
                {
                    pdir = "UR";
                } else if(Keyboard::isKeyPressed(Keyboard::Down))
                {
                    pdir = "DR";
                } else
                {
                    pdir = "R";
                }
            } else if(Keyboard::isKeyPressed(Keyboard::Left))
            {
                if(Keyboard::isKeyPressed(Keyboard::Up))
                {
                    pdir = "UL";
                } else if(Keyboard::isKeyPressed(Keyboard::Down))
                {
                    pdir = "DL";
                } else
                {
                    pdir = "L";
                }
            } else if(Keyboard::isKeyPressed(Keyboard::Up))
            {
                pdir = "U";
            }
        }
    }
    edir = pickRandDefence(enemy);
    for(int i=1; i<=frames; i++)
    {
        //Play animation;
        if(updateStep.getElapsedTime().asSeconds() > timestep/frames)
        {
            if(i <= frames)
            {
                updateStep.restart();
                window.clear();
                window.draw(handler.getSprite("TestBattleBackground"));
                if(player.pierce>enemy.hard)
                {
                    window.draw(handler.getSprite(player.name + "Att" + pdir + to_string(i)));
                    window.draw(handler.getSprite(enemy.name + "Defend" + edir));
                } else
                {
                    window.draw(handler.getSprite(enemy.name + "Defend" + edir));
                    window.draw(handler.getSprite(player.name + "Att" + pdir + to_string(i)));
                }
                window.display();
            }
        } else { i--;}
    }
    player.attack(enemy,pdir,edir);
    updateStep.restart();
    while(updateStep.getElapsedTime().asSeconds()<wait){}
    return false;
}
string FightHandler::pickRandDefence(Entity &enemy)
{
    int ran;
    for(int x = 0; x<13;x++)
    {
        ran = rand()%6;
    }
    switch(ran)
    {
    case 0:
        return "R";
        break;
    case 1:
        return "U";
        break;
    case 2:
        return "D";
        break;
    case 3:
        return "L";
        break;
    case 4:
        return "DL";
        break;
    case 5:
        return "UL";
        break;
    default:
        return "L";
    }
}
