#include "main-menu.h"
#include <stdlib.h>
#include <stdio.h>

Main_Menu * Main_Menu_init(const int screenWidth, const int screenHeight){

    Main_Menu * self = malloc(sizeof(Main_Menu));

    //Init of the play game btn
    Rectangle playGameBtn = {(screenWidth*32)/100, (screenHeight*35)/100, (screenWidth*30)/100, (screenHeight*5)/100};
    Rectangle smallPlayGameBtn = {3 + (screenWidth*32/100), 3 + (screenHeight*35/100), (screenWidth*30/100) - 6, (screenHeight*5/100) - 6};
    Rectangle playGameTextBox = {smallPlayGameBtn.x + smallPlayGameBtn.width/3, smallPlayGameBtn.y, smallPlayGameBtn.width, smallPlayGameBtn.height};
    Menu_Button * playGame = Menu_Button_init(&playGameBtn, &playGameTextBox, "PLAY", game_ui);

    //Init of the options btn
    Rectangle optionsBtn = {(screenWidth*32)/100, (screenHeight*45)/100, (screenWidth*30)/100, (screenHeight*5)/100};
    Rectangle smallOptionsBtn = {3 + (screenWidth*32/100), 3 + (screenHeight*45/100), (screenWidth*30/100) - 6, (screenHeight*5/100) - 6};
    Rectangle optionsTextBox = {smallOptionsBtn.x + smallOptionsBtn.width/4, smallOptionsBtn.y, smallOptionsBtn.width, smallOptionsBtn.height};
    Menu_Button * optionsMenu = Menu_Button_init(&optionsBtn, &optionsTextBox, "OPTIONS", options);

    //Init of the rules btn
    Rectangle rulesBtn = {(screenWidth*32)/100, (screenHeight*55)/100, (screenWidth*30)/100, (screenHeight*5)/100};
    Rectangle smallRulesBtn = {3 + (screenWidth*32/100), 3 + (screenHeight*55/100), (screenWidth*30/100) - 6, (screenHeight*5/100) - 6};
    Rectangle rulesTextBox = {smallRulesBtn.x + smallRulesBtn.width*4/13, smallRulesBtn.y, smallRulesBtn.width, smallRulesBtn.height};
    Menu_Button * rulesMenu = Menu_Button_init(&rulesBtn, &rulesTextBox, "RULES", rules);

    //Init of the exit btn
    Rectangle exitBtn = {0, (screenHeight*95)/100, (screenWidth*10)/100, (screenHeight*10)/100};
    Rectangle smallerExitBtn = {3, 3 +(screenHeight*95)/100, -6 + (screenWidth*10)/100, -6 + (screenHeight*10)/100};
    Rectangle exitTextBox = {smallerExitBtn.x + smallerExitBtn.width/10, smallerExitBtn.y, smallerExitBtn.width, smallerExitBtn.height};
    Menu_Button * terminateBtn = Menu_Button_init(&exitBtn, &exitTextBox, "EXIT", exitRoute);

    self->buttonCount = 4;
    self->buttons = malloc(sizeof(Menu_Button) * self->buttonCount);
    self->buttons[game_ui] = playGame;
    self->buttons[options] = optionsMenu;
    self->buttons[rules] = rulesMenu;
    self->buttons[exitRoute] = terminateBtn;

    return self;
}

Main_Menu * Rules_Menu_init(const int screenWidth, const int screenHeight){

    Main_Menu * self = malloc(sizeof(Main_Menu));

    //Init of the return btn
    Rectangle returnBtn = {0, (screenHeight*95)/100, (screenWidth*15)/100, (screenHeight*10)/100};
    Rectangle smallerReturnBtn = {3, 3 +(screenHeight*95)/100, -6 + (screenWidth*15)/100, -6 + (screenHeight*10)/100};
    Rectangle returnTextBox = {smallerReturnBtn.x + smallerReturnBtn.width/7, smallerReturnBtn.y, smallerReturnBtn.width, smallerReturnBtn.height};
    Menu_Button * rulesMenu = Menu_Button_init(&returnBtn, &returnTextBox, "Main Menu", main_menu);

    //Init of the rules text box
    Rectangle rulesBox = {(screenWidth*25)/100, (screenHeight*30)/100, (screenWidth*50)/100, (screenHeight*60)/100};
    Rectangle smallerRulesBox = {3 + (screenWidth*25)/100, 3 +(screenHeight*30)/100, -6 + (screenWidth*50)/100, -6 + (screenHeight*60)/100};
    Rectangle rulesTextBox = {5 + (screenWidth*25)/100, 5 +(screenHeight*30)/100, -10 + (screenWidth*50)/100, -10 + (screenHeight*60)/100};
    Menu_Button * rulesText = Menu_Button_init(&rulesBox, &rulesTextBox,
    "This game is an adapted and computerized version of the board game Risk.\nEach player will be given a set of territories (nodes) and a mission to win the game.\nSuccessively, each player will play their turns which happens in 2 phases :\n-\tThe recruitment phase, in which a player is given reinforcements to place on his node, and move existing soldiers, although any given nodes needs at least 1 soldier at all times.\n-\tThe attack phase, in which a player may attack neighboring nodes that he doesnt own. He will have to engage up to 3 soldiers in a fight, which resolves in throwing one die per soldier engage. The outcome will be determined by the head to head comparison of the results from the attacker and the defender.\nA player wins by accomplishing their mission.",
    rules);

    self->buttonCount = 2;
    self->buttons = malloc(sizeof(Menu_Button) * self->buttonCount);
    self->buttons[0] = rulesMenu;
    self->buttons[1] = rulesText;

    return self;
}

Display Main_Menu_detect_click(Main_Menu * self, Vector2 * mousePos){
    for(int index = 0; index < self->buttonCount; index++){
        Menu_Button * currentBtn = self->buttons[index];
        if(CheckCollisionPointRec(*mousePos, currentBtn->button)){
            return currentBtn->displayOnClick;
        }
    }
    return main_menu;
}

void Main_Menu_delete(Main_Menu * self){
    for(int index = 0; index < self->buttonCount; index++){
        Menu_Button_delete(self->buttons[index]);
    }
    free(self->buttons);
    free(self);
}

