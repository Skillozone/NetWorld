/*******************************************************************************************
*
*   NetWorld basic viewer
*   Copyright (c) 2020-2020 Guillaume Lozenguez
*
********************************************************************************************/

#include "raylib.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "networld.h"
#include "player.h"
#include "controlpanel.h"
#include "random-map.h"
#include "graphical-aspect.h"
#include "window-manager.h"
#include "main-menu.h"
#include "options-menu.h"
#include "mission.h"

// Program attributes
//-------------------
const int screenWidth = 1700;
const int screenHeight = 800;
const int targetFPS = 60;

int game_update(NetWorld * world, Player * players, Mission * missions, Font *font, Panel * panel);

// Game attributes
//-----------------
bool game_end = false;

int main(int nbArg, char ** arg)
{
    int nodeCount = 10;
    int playerCount = 3;

    NetWorld * world = malloc(sizeof(NetWorld));
    Player * players = malloc(sizeof(Player));
    Mission * missions = malloc(sizeof(Mission));

    // Raylib Initialization
    //----------------------
    InitWindow(screenWidth, screenHeight, "NetWorld basic viewer");
    SetTargetFPS(targetFPS);
    
    Font gameFont = LoadFont("resources/GAMERIA.ttf");
    
    // Main game loop

    //UI elements
    Panel * panel = Panel_new();
    Panel_initialize(panel, world, screenWidth, screenHeight);
    
    Main_Menu * menu = Main_Menu_init(screenWidth, screenHeight);
    Main_Menu * rulesMenu = Rules_Menu_init(screenWidth, screenHeight);
    Options_Menu * optionsMenu = Options_Menu_init(&playerCount, &nodeCount, screenWidth, screenHeight);
    Window_Manager * manager = Window_Manager_new(panel, menu, rulesMenu, optionsMenu);

    Rectangle gameReturnBtn = {0,0, (screenWidth*13)/100, (screenHeight*5)/100};
    Rectangle gameReturnTextBox = {3,3, -6 +(screenWidth*13)/100, -6 +(screenHeight*5)/100};
    Menu_Button*  gameReturn = Menu_Button_init(&gameReturnBtn, &gameReturnTextBox, "Main Menu", main_menu);

    while (!game_end && !WindowShouldClose())    // Detect window close button or ESC key
    {
        DrawFPS(screenWidth - 100,screenHeight - 50);
        Window_Manager_display(manager, world, players, missions);
        Vector2 mousePos;
        int key;
        switch (manager->display)
        {
        case main_menu:
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                mousePos = GetMousePosition();
                manager->display = Main_Menu_detect_click(menu, &mousePos);
                if(manager->display == game_ui){
                    //Initialising a new game with inputted parameters 
                    *world = *NetWorld_new(nodeCount, playerCount);
                    Random_map(world);
                    Color colors[] = {BLACK, RED, BLUE, BROWN, PURPLE, PINK, YELLOW};
                    char* names[] = {"Black", "Red", "Blue", "Brown", "Purple", "Pink", "Yellow"}; 
                    players = Player_newArray(playerCount, colors, names);
                    missions = Mission_newArray(playerCount, world, players);
                    //Distribute nodes to players evenly
                    for(int index = 0; index < world->size; index++){
                        Player_add_Node(&(players[index % playerCount]), &(world->nodes[index]));
                    }
                    world->currentPlayer = 0;
                    Player_start_turn(&(players[world->currentPlayer]));
                }
            }
            break;
        case game_ui:
            Panel_control(panel);
            Menu_Button_draw(gameReturn, &gameFont, screenWidth, screenHeight, RED, (screenHeight*4)/100, (screenWidth/400), true);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                mousePos = GetMousePosition();
                if(CheckCollisionPointRec(mousePos, gameReturn->button)){
                    manager->display = gameReturn->displayOnClick;
                }
            }
            //Draw the hitboxes for each node
            for(int index = 0; index < world->size; index++){
                Vector2 screenPosition= Panel_pixelFromPosition(panel, &(world->nodes[index]).position);
                world->nodes[index].collisionHitbox.x = screenPosition.x - 24;
                world->nodes[index].collisionHitbox.y = screenPosition.y - 24;
            }

            world->winner = game_update(world, players, missions, &gameFont, panel);
            if(world->hasWinner){
                manager->display = win;
            }
            break;
        case options:
            //Activate/Deactivate inputs on click and detect click on the save btn
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                mousePos = GetMousePosition();
                if(Options_Menu_check_save_click(optionsMenu, &mousePos)){
                    manager->display = main_menu;
                    for(int index = 0; index < optionsMenu->inputCount; index++){
                        Int_Input_save_value(optionsMenu->inputs[index]);
                    }
                }
                Options_Menu_check_input_click(optionsMenu, &mousePos);
            }
            key = GetKeyPressed();
            //Check key inputs for active input fields (only accepts numerical characters)
            for(int index = 0; index < optionsMenu->inputCount; index++){
                if(optionsMenu->inputs[index]->inputActive){
                    DrawRectangleLinesEx((Rectangle){optionsMenu->inputBox[index].x-3,optionsMenu->inputBox[index].y-3,optionsMenu->inputBox[index].width+5,optionsMenu->inputBox[index].height+5}, 5, BLACK);
                    if ((key >= 48) && (key <= 57) && (optionsMenu->inputCount < 3)){
                        Int_Input_add_char(optionsMenu->inputs[index], &key);
                    }
                    if (IsKeyPressed(KEY_BACKSPACE)){
                        Int_Input_remove_char(optionsMenu->inputs[index]);
                    }
                }
            }
            break;
        case rules:
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                mousePos = GetMousePosition();
                manager->display = Main_Menu_detect_click(rulesMenu, &mousePos);
            }
            break;
        case win:
            Menu_Button_draw(gameReturn, &gameFont, screenWidth, screenHeight, RED, (screenHeight*4)/100, (screenWidth/400), true);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                mousePos = GetMousePosition();
                if(CheckCollisionPointRec(mousePos, gameReturn->button)){
                    manager->display = gameReturn->displayOnClick;
                }
            }
            break;
        case exitRoute:
            game_end = true;
            break;
        default:
            break;
        }
    }

    // proper closing
    //---------------

    Players_delete(players, playerCount);
    Mission_deleteArray(missions,playerCount);
    NetWorld_delete(world);
    Main_Menu_delete(menu);
    Main_Menu_delete(rulesMenu);
    Menu_Button_delete(gameReturn);
    Options_Menu_delete(optionsMenu);
    Window_Manager_delete(manager);
    Panel_delete(panel);
    UnloadFont(gameFont); 
    
    CloseWindow();   // Close window and OpenGL context
 
    return 0;
}

int game_update(NetWorld * world, Player * players, Mission * missions, Font* font, Panel * panel)
{
    //Game frame init
    int winner = 0;
    Vector2 mousePosition = GetMousePosition();
    Player * currentPlayer = &(players[world->currentPlayer]);
    Graphic_ShowPlayerInfo(currentPlayer, screenWidth, screenHeight, font);
    Graphic_WhoseTurnIsIt(currentPlayer, screenWidth, screenHeight, font);
    int playerCount = world->playerCount;

    Rectangle missionDisplay = {screenWidth*30/100, screenHeight*95/100, screenWidth*40/100, screenHeight*10/100};
    Rectangle missionTextBox = {missionDisplay.x + missionDisplay.width/5, missionDisplay.y, missionDisplay.width, missionDisplay.height};
    
    DrawTextRec(*font, missions[currentPlayer->ID].displayText, missionTextBox, (screenHeight*4)/100, (screenWidth/400), true, BLACK);
    
    switch(currentPlayer->turnPhase){            
        case recruitment:
            Graphic_RecrutementPhase(currentPlayer, screenWidth, screenHeight, font);   
            Graphic_MouseHoverNodeRecrutement(currentPlayer, mousePosition, panel);
            if(currentPlayer->soldiers > 0){
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    Player_add_soldier(currentPlayer, &mousePosition);
                }
            }else{
                //Finish the recruitment phase
                Rectangle nextPhaseButton = Graphic_ConfirmButton(font);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    if(CheckCollisionPointRec(mousePosition, nextPhaseButton)){
                        Player_confirm_recrutement(currentPlayer);
                        currentPlayer->turnPhase = attack;
                    }
                }
            }
            if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
                Player_remove_soldier(currentPlayer, &mousePosition);
            }
            break;
        case attack:
            Graphic_AttackPhase(currentPlayer, screenWidth, screenHeight, font);
            Graphic_MouseHoverNodeChooseAttacker(currentPlayer, mousePosition, panel);
            if(currentPlayer->hasSelectedNode){
                Graphic_MouseHoverNodeChooseTarget(currentPlayer->selectedNode, mousePosition, panel);
                if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
                    Player_unselect_Node(currentPlayer, &mousePosition);
                }
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    Node * originNode = currentPlayer->selectedNode;
                    //Detect if the player declared an attack
                    for(int nodeIndex = 0; nodeIndex < world->size; nodeIndex++){
                        Node* currentNode = &(world->nodes[nodeIndex]);
                        
                        if(CheckCollisionPointRec(mousePosition, currentNode->collisionHitbox)){
                            int nodePlayerID = currentNode->playerID;
                            if(nodePlayerID == currentPlayer->ID){
                                currentPlayer->selectedNode = currentNode;
                            }
                            else if(Node_are_connected(originNode, currentNode) && (originNode->soldiers > 1) && originNode->canAttack){
                                printf("Engagine attack on target Node\n");
                                int nbOfAttackers = Graphic_ChooseNumberOfAttackers(currentPlayer, &(players[nodePlayerID]), originNode, currentNode, font);
                                int nbOfDefenders = currentNode->soldiers;
                                printf("nbOfAtackers %d \n", nbOfAttackers);
                                printf("nbOfdefenders %d \n", nbOfDefenders);
                                int * listOfDices = Player_attack_Node(currentPlayer, &(players[nodePlayerID]), originNode, currentNode, nbOfAttackers);           
                                for(int  i = 0; i< nbOfDefenders+nbOfAttackers; i++){
                                    printf("listOfdices3 [%d] : %d \n",i,listOfDices[i]);
                                     }
                                Graphic_diceRolling(currentPlayer, &(players[nodePlayerID]), originNode, currentNode, nbOfAttackers ,nbOfDefenders, listOfDices, font);
                                currentPlayer->hasSelectedNode = false;
                                free(listOfDices);
                            }
                        }
                    }
                }
            }else{
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    Player_select_Node(currentPlayer, &mousePosition);
                }
            }
            //End turn btn
            Rectangle nextPhase = {200, 200, 270, 55};     
            DrawRectangleRec(nextPhase, GREEN);
            DrawTextEx(*font, "Next Turn",(Vector2){220 , 210} , 40.0, 3.0, BLACK); 
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                if(CheckCollisionPointRec(mousePosition, nextPhase)){
                    currentPlayer->turnPhase = init;
                }
            }
            break;
        case init :
            //Check on missions
            if(Mission_check(&missions[currentPlayer->ID], world, players)){
                world->hasWinner = true;
                winner = currentPlayer->ID;
            }
            //Switch turns
            Player_end_turn(currentPlayer);
            world->currentPlayer = (world->currentPlayer + 1) % playerCount;
            Player_start_turn(&(players[world->currentPlayer]));
            break;
        default:
            break;
    }
    return winner;
}
