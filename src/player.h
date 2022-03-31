#ifndef PLAYER_H
#define PLAYER_H

#include "networld.h"

enum turnPhases {init, recruitment, attack};
typedef enum turnPhases TurnPhases;

struct Str_Player{
    //! Player ID
    int ID;
    //! List of node pointers belonging to the player
    Node ** nodes;
    //! Nb of owned nodes
    int nodeCount;
    //! Player Color
    Color color;
    //! Player's turn phase
    TurnPhases turnPhase;
    //! Player soldier count for the recruitement phase
    int soldiers;
    //! Player's selected node for the attack phase
    Node * selectedNode;
    bool hasSelectedNode;
    char* name;
};

typedef struct Str_Player Player;

// Constructor / Destructor
/**
 * @brief     Construct all the elements of an empty Player.
 * @param     self an empty Player not yet constructed.
 * @return    The pointer to the new Player.
 */
void Player_construct(Player * self, int id, Color color, char* name);

/**
 * @brief     Allocate the memory to store a Player
 * @return    The pointer to the new Player.
 */
Player * Player_new();

/**
 * @brief     Allocate 'size' Players.
 * @return    The pointer to the new array of 'size' Player.
 */
Player * Player_newArray(int size, Color colors[], char* names[]);

/**
 * @brief    Destructor.
 */
void Players_delete(
    //! the Player list to delete
    Player * self,
    //! the Player list size to delete
    int size
);

/**
 * @brief  Add a node to the player's territory.
 */
void Player_add_Node(
    //! The player;
    Player * self,
    //! The Node to add
    Node * node

);

/**
 * @brief  Remove a node from the player's territory.
 */
void Player_remove_Node(
    //! The player;
    Player *  self,
    //! The Node to remove
    Node * node
);

/**
 * @brief Start a player's turn and take all actions before player's first input
 */
void Player_start_turn(Player * self);


/**
 * @brief End a player's turn
 */
void Player_end_turn(Player * self);

/**
 * @brief Add a soldier to a player's node
 * @param self The player context
 * @param mousePos the position of the mouse to detect which node has been clicked
 */
void Player_add_soldier(Player * self, Vector2 * mousePos);

/**
 * @brief Remove a soldier from a player's node
 * @param self The player context
 * @param mousePos the position of the mouse to detect which node has been clicked
 */
void Player_remove_soldier(Player * self, Vector2 * mousePos);

/**
 * @brief A player selects a node
 * @param self The player context
 * @param mousePos the position of the mouse to detect which node has been clicked
 */
void Player_select_Node(Player * self, Vector2 * mousePos);

/**
 * @brief A player unselects a node
 * @param self The player context
 * @param mousePos the position of the mouse to detect which node has been clicked
 */
void Player_unselect_Node(Player * self, Vector2 * mousePos);

/**
 * @brief Attack declaration
 * @param self The attacking player
 * @param defender The defending player
 * @param originNode The attacker's node
 * @param targetNode The defender's node
 * @param numberOfAttackers Number of attacking soldiers
 */
 int * Player_attack_Node(Player * self, Player * defender, Node * originNode, Node * targetNode, const int attackersCount);
 
 /**
 * @brief Confirm placement of soldiers
 * @param self The player context
 */
void Player_confirm_recrutement(Player * self);

#endif