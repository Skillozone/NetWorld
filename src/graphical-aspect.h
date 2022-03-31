#ifndef GRAPHICALASPECT_H
#define GRAPHICALASPECT_H

#include "raylib.h"
#include "networld.h"
#include "player.h"
#include "controlpanel.h"


//Graphical view
//Display players' number of nodes owned, number of total troops and number of soldier to place on the bottom left of the screen
void Graphic_ShowPlayerInfo(Player * player, const int screenWidth, const int screenHeight, Font * font);

//Display recrutement phase rules on the right of the screen
void Graphic_RecrutementPhase(Player * player, const int screenWidth, const int screenHeight, Font * font);

//Display attack phase rules on the right of the screen
void Graphic_AttackPhase(Player * player, const int screenWidth, const int screenHeight, Font * font);

//Display whose turn is it on the top of the screen
void Graphic_WhoseTurnIsIt(Player * player, const int screenWidth, const int screenHeight, Font * font);

//Confirm button for the recruitment phase
Rectangle Graphic_ConfirmButton(Font * font);

//Animation when mouse hover node during recruitment phase
void Graphic_MouseHoverNodeRecrutement(Player * self, Vector2 mousePosition, Panel * panel);

//Animation when mouse hover node when choosing attacker node during attack phase
void Graphic_MouseHoverNodeChooseAttacker(Player * player, Vector2 mousePosition, Panel * panel);

//Animation when mouse hover node when choosing target node during attack phase
void Graphic_MouseHoverNodeChooseTarget(Node * originNode, Vector2 mousePosition, Panel * panel);

//Display a window to choose number of dices to involve in a fight + return the number chosen
int Graphic_ChooseNumberOfAttackers(Player * attacker, Player * defender, Node * originNode, Node * targetNode, Font * font);

//Display animation of dice rolling + results of the dice rolling
void Graphic_diceRolling(Player * attacker, Player * defender, Node * originNode, Node * targetNode, int nbOfAttackers, int nbOfDefenders, int * listOfDices, Font * font);



#endif