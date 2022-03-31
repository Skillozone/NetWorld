#ifndef OPTIONSBUTTON_H
#define OPTIONSBUTTON_H

#include "raylib.h"
#include "int-input.h"

struct Str_Options_Menu{
    //! List of input fields
    Int_Input ** inputs;
    //! Nb of input fields
    int inputCount;
    //Return btn
    Rectangle saveReturnBtn;
    Rectangle smallerSaveReturnBtn;
    Rectangle inputBox[2];
};

typedef struct Str_Options_Menu Options_Menu;

/**
 * @brief     Initialise a new Options_Menu
 * @param     playerCount Reference to the playerCount game variable
 * @param     nodeCount Reference to the nodeCount game variable
 * @param     screenWidth Width of the screen
 * @param     screenHeight Height of the screen
 * @return    A pointer to the Options_Menu element
 */
Options_Menu * Options_Menu_init(int * playerCount, int * nodeCount, const int screenWidth, const int screenHeight);

/**
 * @brief     Check if the save btn has been clicked
 * @param     self The options menu context
 * @param     mousePos The position of the mouse on click
 * @return    A boolean
 */
bool Options_Menu_check_save_click(Options_Menu * self, Vector2 * mousePos);

/**
 * @brief     Activate/Deactivate inputs on click
 * @param     self The options menu context
 * @param     mousePos The position of the mouse on click
 */
void Options_Menu_check_input_click(Options_Menu * self, Vector2 * mousePos);

/**
 * @brief     Delete an Options_Menu
 * @param     self The object to void
 */
void Options_Menu_delete(Options_Menu * self);

#endif