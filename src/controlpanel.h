#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "networld.h"
#include "main-menu.h"
#include "options-menu.h"
#include "player.h"
#include "mission.h"
// Tools
void printVector2( Vector2 v );


//-----------------------------------//
//--        Control Panel           --//
//-----------------------------------//

struct Str_Panel {
    Vector2 camera, screenCenter;
    int screenWidth, screenHeight;
    float scale; // meter per pixel
    NetWorld * world;
};

typedef struct Str_Panel Panel;

// Constructor / Destructor
Panel * Panel_new();
void Panel_delete(Panel * self);

// Initialization
void Panel_initialize(Panel * self, NetWorld * world, const int screenWidth, const int screenHeight);

// To String
void Panel_print(Panel * self);

// Rendering the game
void Panel_drawGame(Panel * self);
void Panel_drawBasis(Panel * self);
void Panel_drawNode(Panel * self, Node * n);
void Panel_drawEdge(Panel * self, Edge * e);
Vector2 Panel_pixelFromPosition(Panel * self, Vector2 * p);
Vector2 Panel_positionFromPixel(Panel * self, Vector2 * p);

//Rendering the main menu
void Panel_drawMainMenu(Panel * self, Main_Menu * menu);

//Rendering the options menu
void Panel_drawOptionsMenu(Panel * self, Options_Menu * menu);

//Rendering the rules menu
void Panel_drawRules(Panel * self, Main_Menu * rules);

//Rendering the victory screen
void Panel_drawWin(Panel * self, Player * player, Mission * mission);

// Control
void Panel_control(Panel * self);
void Panel_controlCamera(Panel * self);

#endif //CONTROLPANEL_H