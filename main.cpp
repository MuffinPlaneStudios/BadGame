#include <SFML/Graphics.hpp>
#include <GraphicsHandler.h>
#include <Map.h>
#include <EventHandler.h>
using namespace std;
using namespace sf;
const int xwin = 15;
const int ywin = 11;
GraphicsHandler handler;
int x = 7;
int xpos = x*63;
int y = 7;
int ypos = y*63;
Clock updateStep;
const float timestep = .5;

int main()
{
    handler.init();
    //game loop
    Event event = Event();
    EventHandler ehand = EventHandler(handler);
    bool ev = true;
    handler.updateMap(xpos,ypos);
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
                    case 'w':
                        if(handler.m.tmap[x][y-1] != "BlankTile"){
                            for(int i=1; i<=63; i++)
                            {
                                if(updateStep.getElapsedTime().asSeconds() > timestep/63.0)
                                {
                                    updateStep.restart();
                                    ypos--;
                                    handler.updateMap(xpos,ypos);
                                } else { i--;}
                            }
                            y--;
                            cout<<ehand.event(handler.m.tmap[x][y]);
                            handler.updateMap(xpos,ypos);
                        }
                        while(ev)
                        {
                            ev = handler.getWindow().pollEvent(event);
                        }
                        ev = true;
                        break;
                    case 's':
                        if(handler.m.tmap[x][y+1] != "BlankTile"){
                            for(int i=1; i<=63; i++)
                            {
                                if(updateStep.getElapsedTime().asSeconds() > timestep/63.0)
                                {
                                    updateStep.restart();
                                    ypos++;
                                    handler.updateMap(xpos,ypos);
                                } else { i--;}
                            }
                            y++;
                            cout<<ehand.event(handler.m.tmap[x][y]);
                            handler.updateMap(xpos,ypos);
                        }
                        while(ev)
                        {
                            ev = handler.getWindow().pollEvent(event);
                        }
                        ev = true;
                        break;
                    case 'a':
                        if(handler.m.tmap[x-1][y] != "BlankTile"){
                            for(int i=1; i<=63; i++)
                            {
                                if(updateStep.getElapsedTime().asSeconds() > timestep/63.0)
                                {
                                    updateStep.restart();
                                    xpos--;
                                    handler.updateMap(xpos,ypos);
                                } else { i--;}
                            }
                            x--;
                            cout<<ehand.event(handler.m.tmap[x][y]);
                            handler.updateMap(xpos,ypos);
                        }
                        while(ev)
                        {
                            ev = handler.getWindow().pollEvent(event);
                        }
                        ev = true;
                        break;
                    case 'd':
                        if(handler.m.tmap[x+1][y] != "BlankTile"){
                            for(int i=1; i<=63; i++)
                            {
                                if(updateStep.getElapsedTime().asSeconds() > timestep/63.0)
                                {
                                    updateStep.restart();
                                    xpos++;
                                    handler.updateMap(xpos,ypos);
                                } else { i--;}
                            }
                            x++;
                            cout<<ehand.event(handler.m.tmap[x][y]);
                            handler.updateMap(xpos,ypos);
                        }
                        while(ev)
                        {
                            ev = handler.getWindow().pollEvent(event);
                        }
                        ev = true;
                        break;
                }
            break;
            default:
            break;
        }
    } while (handler.getWindow().isOpen());

    return 0;
}
