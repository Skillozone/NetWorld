#include "mission.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool Player_conquer_threshold(NetWorld * world, Player * players, const int playerID, const int threshold){
    return players[playerID].nodeCount >= threshold;
}

bool Player_eliminated(NetWorld * world, Player * players, const int playerID, const int targetPlayer){
    return players[targetPlayer].nodeCount == 0;

}

void Mission_init(Mission * self, const int playerID, NetWorld * world, Player * players){
    char* displayText = malloc(sizeof(char)*50);    
    
    self->playerID = playerID;

    switch(rand()%2){
        case 0:
            self->mission = &Player_conquer_threshold;
            self->target = world->size/2 + ((rand()%(world->size/5)) + (world->size/10));
            sprintf(displayText, "Conquer %d nodes", self->target);
            self->displayText = displayText;
            break;
        case 1:
            self->mission = &Player_eliminated;
            self->target = rand()%world->playerCount;
            while(self->target == self->playerID){
                self->target = rand()%world->playerCount;
            }
            sprintf(displayText, "Eliminate %s", players[self->target].name);
            self->displayText = displayText;
            break;
    }
    //return self;
}

Mission * Mission_newArray(const int playerCount, NetWorld * world, Player * players){
    Mission * missionArray = malloc(sizeof(Mission) * playerCount);
    for(int i = 0; i < playerCount; i++){
        Mission_init((missionArray+i),i ,world, players);
    }
    return missionArray;
}



bool Mission_check(Mission * self, NetWorld * world, Player * players){
    return self->mission(world, players, self->playerID, self->target);
}

void Mission_deleteArray(Mission * array, int playerCount){
    free(array);
}