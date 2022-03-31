#include "player.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void Player_construct(Player * self, int i, Color color, char* name)
{
    self->ID = i;
    self->nodes = malloc(sizeof(Node*));
    self->nodeCount = 0;
    self->color = color;
    self->turnPhase = init;
    self->soldiers = 0;
    self->selectedNode = malloc(sizeof(Node));
    self->hasSelectedNode = false;
    self->name = name;
}

Player * Player_new()
{
    Player * player= malloc( sizeof(Player) );
    Player_construct(player, 0, BLACK, "Black");
    return player;
}

Player * Player_newArray(int size, Color color[], char* names[])
{
    size= fmaxf(1, size);
    Player * p= malloc( sizeof(Player)*size );
    for(int i=0 ; i < size ; ++i )
    {
        Player_construct( &(p[i]), i, color[i], names[i]);
    }
    return p;
}

void Players_delete(Player * player, int size)
{   
    free(player);
}

void Player_add_Node( Player * self, Node * node )
{
    Node ** newNodes =  malloc(sizeof(Node*)*(self->nodeCount + 1));
    for( int i = 0 ; i < self->nodeCount ; i++ )
    {
        newNodes[i] = self->nodes[i];
    }
    node->color = self->color;
    for (int i = 0 ; i < node->card ; i++){
        node->edges[i].color = self->color;
    }
    node->playerID = self->ID;
    newNodes[self->nodeCount] = node;
    free(self->nodes);
    self->nodes = NULL;
    self->nodes= newNodes;
    self->nodeCount += 1;
}

void Player_remove_Node( Player * self, Node * node )
{
    Node ** newNodes =  malloc(sizeof(Node*)*(self->nodeCount - 1));
    bool nodeFound = false;
    for( int i = 0 ; i < self->nodeCount-1 ; i++ )
    {
        if(!nodeFound && self->nodes[i] == node){
            nodeFound = true;
        }
        if(nodeFound){
            newNodes[i] = self->nodes[i+1];
        }else{
            newNodes[i] = self->nodes[i];
        }
    }
    
    free(self->nodes);
    self->nodes = newNodes;
    node->playerID = -1;
    self->nodeCount -= 1;
}

void Player_start_turn(Player * self){
    if(self->nodeCount == 0){
        self->turnPhase = init;
    }else{
        int totalSoldierCount = 0;
        for(int nodeIndex = 0; nodeIndex < self->nodeCount; nodeIndex++){
            totalSoldierCount += self->nodes[nodeIndex]->soldiers;
        }
        self->soldiers = fmax(3, totalSoldierCount/3);
        self->turnPhase = recruitment;
    }

}

void Player_end_turn(Player * self){
    self->turnPhase = init;
}

void Player_add_soldier(Player * self, Vector2 * mousePos){
    for(int nodeIndex = 0; nodeIndex < self->nodeCount; nodeIndex++){
        Node* currentNode = self->nodes[nodeIndex];
        if(CheckCollisionPointRec(*mousePos, currentNode->collisionHitbox)){
            currentNode->soldiers++;
            self->soldiers--;
            break;
        }
    }
}

void Player_remove_soldier(Player * self, Vector2 * mousePos){
    for(int nodeIndex = 0; nodeIndex < self->nodeCount; nodeIndex++){
        Node* currentNode = self->nodes[nodeIndex];
        if(CheckCollisionPointRec(*mousePos, currentNode->collisionHitbox) && currentNode->soldiers > 0){
            if(currentNode->soldiers > 1){
                currentNode->soldiers--;
                self->soldiers++;
            }
            break;
        }
    }
}

void Player_select_Node(Player * self, Vector2 * mousePos){
    for(int nodeIndex = 0; nodeIndex < self->nodeCount; nodeIndex++){
        Node* currentNode = self->nodes[nodeIndex];
        if(CheckCollisionPointRec(*mousePos, currentNode->collisionHitbox)){
            if(currentNode->soldiers > 1){
                self->hasSelectedNode = true;
                self->selectedNode = currentNode;
            }
            break;
        }
    }
}

void Player_unselect_Node(Player * self, Vector2 * mousePos){
    for(int nodeIndex = 0; nodeIndex < self->nodeCount; nodeIndex++){
        Node* currentNode = self->nodes[nodeIndex];
        if(CheckCollisionPointRec(*mousePos, currentNode->collisionHitbox)){
            self->hasSelectedNode = false;
        }
    }
}

void Player_confirm_recrutement(Player * self){
    for(int nodeIndex = 0; nodeIndex < self->nodeCount; nodeIndex++){
        self->nodes[nodeIndex]->canAttack = true;
    }
};


int * Player_attack_Node(Player * self, Player * defender, Node * originNode, Node * targetNode, const int attackersCount){
    int * listOfDices = malloc(20*sizeof(int));
    int defendersCount = targetNode->soldiers;
    int attDiceRolls[attackersCount];
    int defDiceRolls[defendersCount];

    for(int index = 0; index < attackersCount; index++){
        attDiceRolls[index] = (rand() % 6) + 1;
    }
    for(int index = 0; index < defendersCount; index++){
        defDiceRolls[index] = (rand() % 6) + 1;
    }

    for(int _ = 1; _ < attackersCount; _++){
        for(int index = 0; index < attackersCount - 1; index++){
            if(attDiceRolls[index] < attDiceRolls[index + 1]){
                int tmp = attDiceRolls[index];
                attDiceRolls[index] = attDiceRolls[index + 1];
                attDiceRolls[index + 1] = tmp;
            }
        }
    }

    for(int _ = 1; _ < defendersCount; _++){
        for(int index = 0; index < defendersCount - 1; index++){
            if(defDiceRolls[index] < defDiceRolls[index + 1]){
                int tmp = defDiceRolls[index];
                defDiceRolls[index] = defDiceRolls[index + 1];
                defDiceRolls[index + 1] = tmp;
            }
        }
    }
     for(int index = 0; index < attackersCount; index++){
        listOfDices[index] = attDiceRolls[index];
    }
    for(int index = 0; index < defendersCount; index++){
        listOfDices[index + attackersCount ] = defDiceRolls[index];
    }

    printf("Attackers dice rolls :\t");
    for(int index = 0; index < attackersCount; index++){
        printf("%i\t", attDiceRolls[index]);
    }
    printf("\n");
    printf("Defenders dice rolls :\t");
    for(int index = 0; index < defendersCount; index++){
        printf("%i\t", defDiceRolls[index]);
    }
    printf("\n");

    int remainingAttackers = attackersCount;
    for(int index = 0; index < fmin(defendersCount, attackersCount); index++){
        if(attDiceRolls[index] > defDiceRolls[index]){
            targetNode->soldiers--;
            printf("Defenders lose a soldier\n");

        }else{
            originNode->soldiers--;
            remainingAttackers--;
            printf("Attackers lose a soldier\n");
        }
    }
    
    if(targetNode->soldiers <= 0){
        printf("Node has been conquered\n");
        Player_remove_Node(defender, targetNode);
        Player_add_Node(self, targetNode);
        targetNode->soldiers = attackersCount;
        originNode->soldiers -= attackersCount;
    }

    originNode->canAttack = false;
    return listOfDices;
}

void Delete_Player_attack_Node(int * listOfDices){
    free(listOfDices);
}
