#ifndef NETWORLD_H
#define NETWORLD_H

#include "raylib.h"
//-----------------------------------//
//--        Node                   --//
//-----------------------------------//

struct Str_Edge;


struct Str_Node {
    //! position (x, y) of the node
    Vector2 position;
    //! color (r, g, b, a) of the node
    Color color;
    struct Str_Edge * edges;
    //! cardinality of the node (i.e. number of edges)
    int card;
    // Content:
    //! Number of soldiers at the node
    int soldiers;
    //! Player the node belongs to
    int playerID;
    //! Click hitbox for the node
    Rectangle collisionHitbox;
    //! Boolean indicating if a node has attacked this turn
    bool canAttack;
};

/**
 * @brief                NetWorld Node.
 */
typedef struct Str_Node Node;

// Constructor / Destructor
/**
 * @brief     Construc all the element of an empty Node.
 * @param     self an empty Node ot yet constructed.
 * @return    The pointer to the new NetWorld.
 */
void Node_construct(Node * self);

/**
 * @brief     Allocate the memory to store a Node
 * @return    The pointer to the new NetWorld.
 */
Node * Node_new();

/**
 * @brief     Allocate 'size' Nodes.
 * @return    The pointer to the new array of 'size' Nodes.
 */
Node * Node_newArray(int size);

/**
 * @brief    Destructor.
 */
void Node_delete(
    //! the NetWorld to delete
    Node * self
);


/**
 * @brief    Destructor of an array of nodes.
 */
void Node_deleteArray(
    //! the number of nodes to delete
    int n,
    //! the Nodes
    Node * array
);


/**
 * @brief    initialize a node with a number of edges
 */
void Node_initialize(
    //! the node to initialize
    Node * self, 
    //! the number of outgoing edges
    int card
);

/**
 * @brief    Resize
 */
void Node_resize(
    //! the node to resize
    Node * self, 
    //! the new number of outgoing edges
    int card
);

// Managment :

/**
 * @brief    set
 */
void Node_set(
    //! the node to set
    Node * self, 
    //! position
    Vector2 position,
    //! color
    Color color
);

/**
 * @brief    connect tow node together
 * @return   the index of the edge in the node edges' array
 */
int Node_connect(
    //! the source Node to modify
    Node * self,
    //! the target node
    Node * target
);


/**
 * @brief    connect tow node together (bidirectional)
 * @return   the index of the edge in the node edges' array
 */
int Node_biconnect(
    //! the source Node to modify
    Node * node1,
    //! the target node
    Node * node2
);

/**
 * @brief     Text if 2 nodes are connected
 * @param     self The origin node
 * @param     target The target node
 * @return    A boolean
 */
bool Node_are_connected(Node * self, Node * target);


//-----------------------------------//
//--        Edge                   --//
//-----------------------------------//

struct Str_Edge {
    //! pointer to the source node.
    Node * _source;
    //! pointer to the connected node.
    Node * _target;
    //! pointer to the twin edge in case of bidirectional edge.
    struct Str_Edge * _twin;
    //! color (r, g, b, a) of the node
    Color color;
};

/**
 * @brief                NetWorld Edge.
 */
typedef struct Str_Edge Edge;

// Constructor / Destructor
/**
 * @brief     Construc all the element of an empty Edge.
 * @param     self an empty Edge ot yet constructed.
 * @param     source the source Node the edge start from (default NULL)
 * @param     target the target Node to connect (default NULL)
 * @return    The pointer to the new NetWorld.
 */
void Edge_construct( Edge * self, Node * source, Node * target );

/**
 * @brief     Allocate the memory to store a NetWorld.
 * @return    The pointer to the new NetWorld.
 */
Edge * Edge_new(
    //! the source Node to connect
    Node * source,
    //! the target Node to connect (NULL if unknown)
    Node * target
);

/**
 * @brief    Destructor.
 */
void Edge_delete(
    //! the NetWorld to delete
    Edge * self
);

/**
 * @brief     Allocate 'size' Edges (with NULL target)
 * @return    The pointer to the new array of 'size' Edges.
 */
Edge * Edge_newArray(int size);

/**
 * @brief    Destructor.
 */
void Edge_deleteArray(
    //! the number of edges
    int n,
    //! the NetWorld to delete
    Edge * array
);

// Copying
/**
 * @brief    Copy an edge from another
 */
void Edge_copy(
    //! the edge to modify
    Edge * copy,
    //! the edge to copy
    Edge * model
);

//-----------------------------------//
//--        NetWorld               --//
//-----------------------------------//

struct Str_NetWorld {
    //! number of nodes composing the NetWorld
    int size;
    //! Array of 'size' nodes
    Node * nodes;
    //! Current Player ID
    int currentPlayer;
    //! Total Player count;
    int playerCount;
    //! Does the game have a winner
    bool hasWinner;
    //! ID of the game's winner 
    int winner;
};
typedef struct Str_NetWorld NetWorld;


// Constructor / Destructor
/**
 * @brief     Allocate the memory to store a NetWorld.
 * @return    The pointer to the new NetWorld.
 */
NetWorld * NetWorld_new(
    //! the number of Nodes composing the new NetWorld
    int aSize,
    //! the number of players in the game
    int playerCount
);

/**
 * @brief    Destructor.
 */
void NetWorld_delete(
    //! the NetWorld to delete
    NetWorld * self
);

// To String

/**
 * @brief    print
 */
void NetWorld_print(
    //! the NetWorld to modify
    NetWorld * self
);

// Managment :

/**
 * @brief    connect tow node together
 * @return   the index of the edge in the node edges' array
 */
int NetWorld_connect(
    //! the NetWorld to modify
    NetWorld * self,
    //! index of the source node
    int source,
    //! index of the target node
    int target
);

/**
 * @brief    connect tow node together (bidirectional)
 * @return   the index of the edge in the node edges' array
 */
int NetWorld_biconnect(
    //! the NetWorld to modify
    NetWorld * self,
    //! index of the source node
    int source,
    //! index of the target node
    int target
);


#endif //NETWORLD_H