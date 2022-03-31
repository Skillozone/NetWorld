#ifndef MISSION_H
#define MISSION_H

#include "networld.h"
#include "player.h"

struct Str_Mission{
    //! Boolean function to check if the mission is accomplished
    bool (*mission)(NetWorld*, Player*, const int, const int);
    //! Player needing to accomplish the mission
    int playerID;
    //! Relevant target int for mission (node count, player ID, ...)
    int target;
    //! Mission Description
    char* displayText;
};

typedef struct Str_Mission Mission;

/**
 * @brief     Initialise a new Mission.
 * @return    The pointer to the new Mission.
 */
void Mission_init(Mission * self, const int playerID, NetWorld * world, Player * players);

/**
 * @brief     Check if the missions is completed.
 * @return    A boolean.
 */
bool Mission_check(Mission * self, NetWorld * world, Player * players);

/**
 * @brief     Void a mission array
 */
void Mission_deleteArray(Mission * array, int playerCount);

/**
 * @brief     Initialise a new Mission array
 * @return    The pointer to the new Mission array.
 */
Mission * Mission_newArray(const int playerCount, NetWorld * world, Player * players);

#endif