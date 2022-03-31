#include "options-menu.h"
#include <stdlib.h>
#include <stdio.h>

Options_Menu * Options_Menu_init(int * playerCount, int * nodeCount, const int screenWidth, const int screenHeight){
    Options_Menu * self = malloc(sizeof(Options_Menu));

    //Input for the player count
    Rectangle playerCountInputBox = {(screenWidth*32)/100, (screenHeight*35)/100, (screenWidth*30)/100, (screenHeight*5)/100};
    Int_Input * playerCountInput = Int_Input_init("Nb. of Players : ", playerCount, &playerCountInputBox);

    //Input for the node count
    Rectangle nodeCountInputBox = {(screenWidth*32)/100, (screenHeight*45)/100, (screenWidth*30)/100, (screenHeight*5)/100};
    Int_Input * nodeCountInput = Int_Input_init("Nb. of Nodes : ", nodeCount, &nodeCountInputBox);

    self->inputCount = 2;
    self->inputs = malloc(sizeof(Int_Input) * self->inputCount);
    self->inputs[0] = playerCountInput;
    self->inputs[1] = nodeCountInput;
    self->inputBox[0] = playerCountInputBox;
    self->inputBox[1] = nodeCountInputBox;

    //Save and exit btn
    Rectangle saveBtn = {0, (screenHeight*95)/100, (screenWidth*20)/100, (screenHeight*10)/100};
    Rectangle smallerSaveBtn = {3, 3 +(screenHeight*95)/100, -6 + (screenWidth*20)/100, -6 + (screenHeight*10)/100};
    self->saveReturnBtn = saveBtn;
    self->smallerSaveReturnBtn = smallerSaveBtn;
    
    return self;
}

bool Options_Menu_check_save_click(Options_Menu * self, Vector2 * mousePos){
    return CheckCollisionPointRec(*mousePos, self->saveReturnBtn);
}

void Options_Menu_check_input_click(Options_Menu * self, Vector2 * mousePos){
    for(int index = 0; index < self->inputCount; index++){
        self->inputs[index]->inputActive = CheckCollisionPointRec(*mousePos, self->inputs[index]->inputBox);
    }
}

void Options_Menu_delete(Options_Menu * self){
    for(int index = 0; index < self->inputCount; index++){
        Int_Input_delete(self->inputs[index]);
    }
    free(self->inputs);
    free(self);
}