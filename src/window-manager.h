#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "networld.h"
#include "controlpanel.h"
#include "mission.h"

struct Str_Window_Manager{
    //! frame to display
    Display display;
    //! Reference to the panel context
    Panel * panel;
    //! Reference to the main menu context
    Main_Menu * menu;
    //! Reference to the rules menu context
    Main_Menu * rules;
    //! Reference to the options context
    Options_Menu * options; 
};

typedef struct Str_Window_Manager Window_Manager;

/**
 * @brief Initialise a Window_Manager
 * @param panel Reference to the panel context
 * @param menu Reference to the main menu context
 * @param optionsMenu Reference to the options menu context
 */
Window_Manager *  Window_Manager_new(Panel * panel, Main_Menu * menu, Main_Menu * rules, Options_Menu * optionsMenu);


/**
 * @brief Void a Window Manager
 * @param self The element to void
 */
void Window_Manager_delete(Window_Manager * manager);

/**
 * @brief Displays the appropriate frame
 * @param self The manager context
 */
void Window_Manager_display(Window_Manager * self, NetWorld * world, Player * players, Mission * missions);

#endif
