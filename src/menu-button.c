#include "menu-button.h"
#include <stdlib.h>
#include <stdio.h>

Menu_Button * Menu_Button_init(Rectangle* button, Rectangle* textBox, char* displayText, Display display){
    Menu_Button * self = malloc(sizeof(Menu_Button));
    self->button = *button;
    self->textBox = *textBox;
    self->displayText = displayText;
    self->displayOnClick = display;
    return self;
}

void Menu_Button_draw(Menu_Button * self, Font * font, const int screenWidth, const int screenHeight, Color colour,int fontSize, int spacing, bool wordWrap){
    DrawRectangleLinesEx(self->button, 3, colour);
    DrawTextRec(*font, self->displayText, self->textBox, fontSize, spacing, wordWrap, BLACK);
}

void Menu_Button_delete(Menu_Button * self){
    free(self);
}
