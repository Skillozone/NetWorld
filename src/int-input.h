#ifndef INTINPUT_H
#define INTINPUT_H

#include "raylib.h"

struct Str_Int_Input{
    //! Text to display
    char* name;
    //! Pointer to the value to change
    int * targetInt;
    //! Current stored value
    char* value;
    //! char count of value
    int valueLength;
    //! Panel input box
    Rectangle inputBox;
    bool inputActive;
};

typedef struct Str_Int_Input Int_Input;

/**
 * @brief     Initialise an input field.
 * @param     name the text to display
 * @param     targetInt pointer to the value to change
 * @param     inputBox panel input box
 * @return    The pointer to the new Int_Input.
 */
Int_Input * Int_Input_init(char* name, int * targetInt, Rectangle *inputBox);

/**
 * @brief     Free an Int_Input
 * @param     self the element to void
 */
void Int_Input_delete(Int_Input * self);

/**
 * @brief     Add a char to the current value
 * @param     self the Int_Input to add to
 * @param     key the character to add
 */

void Int_Input_add_char(Int_Input * self, int * key);

/**
 * @brief     Remove a char from the current value
 * @param     self the Int_Input to remove from
 */

void Int_Input_remove_char(Int_Input * self);

/**
 * @brief     Save the stored input value in the actual game parameter
 * @param     self the Int_Input to save in
 */

void Int_Input_save_value(Int_Input * self);

/**
 * @brief     Draw the Int_Input on the panel
 * @param     self the Int_Input to draw
 * @param     font the text font to use
 * @param     screenWidth the width of the screen
 * @param     screenHeight the height of the screen
 */
void Int_Input_draw(Int_Input * self, Font * font, const int screenWidth, const int screenHeight);

#endif