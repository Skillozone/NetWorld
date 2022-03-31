#include "int-input.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Int_Input * Int_Input_init(char* name, int * targetInt, Rectangle * inputBox){
    Int_Input * self = malloc(sizeof(Int_Input));
    self->name = name;
    self->targetInt = targetInt;
    self->value = malloc(sizeof(char)*50);
    sprintf(self->value, "%d", *targetInt);
    self->valueLength = strlen(self->value);
    self->inputBox = *inputBox;
    self->inputActive = false;

    return self;
}

void Int_Input_delete(Int_Input * self){
    free(self->value);
    free(self);
}

void Int_Input_add_char(Int_Input * self, int * key){
    self->value[self->valueLength] = (char) *key;
    self->valueLength++;
    self->value[self->valueLength] = '\0';
}

void Int_Input_remove_char(Int_Input * self){
    self->valueLength--;
    if (self->valueLength < 0) self->valueLength = 0;
    self->value[self->valueLength] = '\0';
}

void Int_Input_save_value(Int_Input * self){
    if(self->valueLength > 0){
        *(self->targetInt) = atoi(self->value);
    }
}

void Int_Input_draw(Int_Input * self, Font * font, const int screenWidth, const int screenHeight){
    DrawRectangleRec(self->inputBox, LIGHTGRAY);
    DrawText(self->name, self->inputBox.x/2, self->inputBox.y, (screenHeight*4)/100, BLACK);
    DrawTextRec(*font, self->value, self->inputBox, (screenHeight*4)/100, (screenWidth/75), true, BLACK);
}