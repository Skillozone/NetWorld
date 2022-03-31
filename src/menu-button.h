#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "raylib.h"

enum displays {game_ui, options, rules, exitRoute, main_menu, win};
typedef enum displays Display;

struct Str_Menu_Button{
    //! Panel elements
    Rectangle button;
    Rectangle textBox;
    //! Text to display in the button
    char* displayText;
    //! Menu to display if the button is clicked
    Display displayOnClick;
};

typedef struct Str_Menu_Button Menu_Button;


/**
 * @brief     Init a Menu_Button
 * @param     button Button hitbox
 * @param     textBox Container for displayText
 * @param     displayText Text to display
 * @param     Display Enum element referencing to a screen display
 * @return    A pointer to the new button
 */
Menu_Button * Menu_Button_init(Rectangle* button, Rectangle* textBox, char* displayText, Display display);

/**
 * @brief     Draw the Menu_Button
 * @param     self The button to draw
 * @param     font The font to use
 * @param     screenWidth Width of the screen
 * @param     screenHeight Height of the screen
 */
void Menu_Button_draw(Menu_Button * self, Font * font, const int screenWidth, const int screenHeight, Color colour, int fontSize, int spacing, bool wordWrap);

/**
 * @brief     Void a Menu_button
 * @param     self The button to void
 */
void Menu_Button_delete(Menu_Button * self);

#endif