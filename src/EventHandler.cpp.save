#include <EventHandler.h>
#include <SFML/Graphics.hpp>
#include <Event.h>
#include <Events.h>
#include <iostream>
#include <FightHandler.h>
#include <GraphicsHandler.h>
using namespace std;

map<string, Events> events;
GraphicsHandler *ghandler;

EventHandler::EventHandler()
{
    init();
}
EventHandler::EventHandler(GraphicsHandler &handler)
{
    ghandler = &handler;
    init();
}
void EventHandler::init()
{
    events["NormalTile"] = Events("NormalEvent",1);
    events["ShopTile"] = Events("ShopEvent",2);
    events["RandTile"] = Events("RandEvent",3);
    events["RestTile"] = Events("RestEvent",4);
    events["BossTile"] = Events("BossEvent",5);
    events["MysteryTile"] = Events("MysteryEvent",6);
}

int EventHandler::event(string eve)
{
    cout<<"eventstart";
    fhandler.fight(*ghandler);
    cout<<"eventover";
    return events[eve].dew();
}
