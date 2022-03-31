#include "window-manager.h"
#include "controlpanel.h"
#include <stdlib.h>
#include <stdio.h>

Window_Manager * Window_Manager_new(Panel * panel, Main_Menu * menu, Main_Menu * rules, Options_Menu * optionsMenu){
    Window_Manager * self = malloc(sizeof(Window_Manager));
    self->panel = panel;
    self->display = (Display) main_menu;
    self->menu = menu;
    self->rules = rules;
    self->options = optionsMenu;
    return self;
}

void Window_Manager_delete(Window_Manager * manager){
    free(manager);
}

void Window_Manager_display(Window_Manager * self, NetWorld * world, Player * players, Mission * missions){
    switch(self->display){
        case main_menu: 
            Panel_drawMainMenu(self->panel, self->menu); 
            break;
        case options:
            Panel_drawOptionsMenu(self->panel, self->options);
            break;
        case game_ui:
            Panel_drawGame(self->panel);
            break;
        case rules:
            Panel_drawRules(self->panel, self->rules);
            break;
        case win:
            Panel_drawWin(self->panel, players+world->winner, missions+world->winner);
            break;
        default:
            break;
    }
}