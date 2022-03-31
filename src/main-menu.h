#ifndef MAINMENU_H
#define MAINMENU_H

#include "menu-button.h"

struct Str_Main_Menu{
    //! Button pointer list
    Menu_Button ** buttons;
    //! Nb of buttons
    int buttonCount;
};

typedef struct Str_Main_Menu Main_Menu;

/**
 * @brief     Initialise a new Main_Menu object
 * @param     screenWidth the width of the screen
 * @param     screenHeight the height of the screen
 * @return    A pointer to the new Main_Menu
 */
Main_Menu * Main_Menu_init(const int screenWidth, const int screenHeight);

/**
 * @brief     Initialise a new Main_Menu object for the rules menu
 * @param     screenWidth the width of the screen
 * @param     screenHeight the height of the screen
 * @return    A pointer to the new Main_Menu
 */
Main_Menu * Rules_Menu_init(const int screenWidth, const int screenHeight);

/**
 * @brief     Detect if any buttons have been clicked
 * @param     self the Main_Menu context
 * @param     mousePos the position of the mouse on click
 * @return    An enum element indicating which screen to display in the next frame
 */
Display Main_Menu_detect_click(Main_Menu * self, Vector2 * mousePos);


/**
 * @brief     Delete a Main_Menu
 * @param     self the menu to void
 */
void Main_Menu_delete(Main_Menu * self);

#endif