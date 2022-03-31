#include "networld.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

//-----------------------------------//
//--        Node                   --//
//-----------------------------------//

// Constructor / Destructor
void Node_construct(Node * self)
{
    Node_set( self, (Vector2){0.f, 0.f}, GRAY);
    self->card= 0;
    self->edges= Edge_newArray( 0 );
    self->soldiers = 1;
    self->playerID = -1;
    Rectangle tmp = {0,0,48,48};
    self->collisionHitbox = tmp;
    self->canAttack = true;
}

Node * Node_new()
{
    Node * p= malloc( sizeof(Node) );
    Node_construct(p);
    return p;
}

Node * Node_newArray(int size)
{
    size= fmaxf(1, size);
    Node * p= malloc( sizeof(Node)*size );
    for(int i=0 ; i < size ; ++i )
    {
        Node_construct( &(p[i]) );
    }
    return p;
}

void Node_delete( Node * node )
{
    Edge_deleteArray( node->card, node->edges );
}

/**
 * @brief    Destructor of an array of nodes.
 */
void Node_deleteArray( int n, Node * array )
{
    for(int i= 0 ; i < n ; ++i ){
        Node_delete((array+i));
    }
    free( array );
}

/**
 * @brief    initialize a node with a number of edges
 */
void Node_initialize( Node * self, int card )
{
    for(int i= 0 ; i < self->card ; ++i )
        Edge_deleteArray( self->card, self->edges );

    self->edges= Edge_newArray( card );
    self->card= card;
}

/**
 * @brief    Resize
 */
void Node_resize( Node * self, int card )
{
    Edge * newEdges= Edge_newArray(card);
    
    int minCard= fminf(self->card, card);
    for( int i = 0 ; i <  minCard ; ++i )
    {
        Edge_copy( &newEdges[i], &(self->edges[i]) );
    }
    Edge_deleteArray( self->card, self->edges );
    self->edges= newEdges;
    self->card= card;
}

void Node_set( Node * self,  Vector2 position, Color color)
{
    self->position= position;
    self->color= color;
}

int Node_connect( Node * self, Node * target )
{
    int i= self->card;
    Node_resize( self, i+1 );
    self->edges[i]._source= self;
    self->edges[i]._target= target;
    self->edges[i].color= self->color;
    self->edges[i]._twin= NULL;
    return i;
}


int Node_biconnect( Node * node1, Node * node2 )
{
    int i1= Node_connect(node1, node2);
    int i2= Node_connect(node2, node1);

    node1->edges[i1]._twin= &(node2->edges[i2]);
    node2->edges[i2]._twin= &(node1->edges[i1]);

    return i1;
}

bool Node_are_connected(Node * self, Node * target){
    for(int index = 0; index < self->card; index++){
        Edge currentEdge = self->edges[index];
        if(currentEdge._target == target){
            return true;
        }
    }
    return false;
}

//-----------------------------------//
//--        Edge                   --//
//-----------------------------------//

// Constructor / Destructor
void Edge_construct( Edge * self, Node * source, Node * target )
{
    self->_source= source;
    self->_target= target;
    self->_twin= NULL;
    self->color= GRAY;
}

Edge * Edge_new( Node * source, Node * target )
{
    Edge * p = malloc( sizeof(Edge) );
    Edge_construct( p, source, target );
    return p;
}

/**
 * @brief    Destructor.
 */
void Edge_delete( Edge * self )
{
    free( self );
}

/**
 * @brief     Allocate 'size' Edges (with NULL target)
 * @return    The pointer to the new array of 'size' Edges.
 */
Edge * Edge_newArray(int size)
{
    size= fmaxf(1, size);
    Edge * p = malloc( sizeof(Edge)*size );
    for( int i = 0 ; i < size ; ++i )
    {
        Edge_construct( &(p[i]), NULL, NULL );
    }
    return p;
}

/**
 * @brief    Destructor.
 */
void Edge_deleteArray( int n, Edge * array )
{
    free(array);
}


/**
 * @brief    Copy an edge from another
 */
void Edge_copy( Edge * copy, Edge * model )
{
    copy->_source= model->_source;
    copy->_target= model->_target;
    copy->_twin= model->_twin;
}

//-----------------------------------//
//--        NetWorld               --//
//-----------------------------------//


// Constructor / Destructor
NetWorld * NetWorld_new(int size, int playerCount)
{
    NetWorld * p = malloc( sizeof(NetWorld) );
    p->size= size;
    p->nodes= Node_newArray( p->size );
    p->currentPlayer = -1;
    p->playerCount = playerCount;
    p->hasWinner = false;
    p->winner = 0;
    return p;
}

void NetWorld_delete(NetWorld * self)
{
    Node_deleteArray( self->size, self->nodes );
    free( self );
}

// To String
void NetWorld_print(NetWorld * self)
{
    for(int i= 0 ; i < self->size ; ++i )
        printf("[%.2f, %.2f]%d\n",
            self->nodes[i].position.x,
            self->nodes[i].position.y,
            self->nodes[i].card);
}

// Managment :

int NetWorld_connect( NetWorld * self, int source, int target )
{
    return Node_connect( &(self->nodes[source]), &(self->nodes[target]) );
}

int NetWorld_biconnect( NetWorld * self, int source, int target )
{
    return Node_biconnect( &(self->nodes[source]), &(self->nodes[target]) );
}

