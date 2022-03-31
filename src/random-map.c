#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "networld.h"
#include "controlpanel.h"
#include "random-map.h"

#include "raylib.h"


double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

double dist(Vector2 vector1, Vector2 vector2)
{
    return (sqrt((vector2.x - vector1.x) * (vector2.x - vector1.x) + (vector2.y - vector1.y) * (vector2.y - vector1.y)));
}

double distNode(Node node1, Node node2)
{
    return (dist(node1.position, node2.position));
}


const double rangeForXcoordinates = 30.0;
const double rangeForYcoordinates = 30.0;
const double minimumDistance = 8.0;

void Random_map(NetWorld *world)
{
    int nbNode = world->size;
    float randomX, randomY;

    /* Intializes random number generator */
    srand(time(NULL));

    /* Generate nbNode*2 random numbers for y-coordinates and x-coordinates of the nodes*/
    for (int i = 0; i < nbNode; i++)
    {
        if (i > 0)
        {
            bool continueLoop = true;
            while (continueLoop)        //loop until the minimum distance between the new node and the others is respected
            {
                continueLoop = false;
                randomX = randfrom(-rangeForXcoordinates, rangeForXcoordinates);
                randomY = randfrom(-rangeForYcoordinates, rangeForYcoordinates);
                Vector2 newPosition = (Vector2){randomX, randomY};

                for (int j = 0; j < i; j++)
                {
                    if (dist(world->nodes[j].position, newPosition) < minimumDistance)  
                    {
                        continueLoop = true;
                    }
                }
            } 
            //har *name; name = malloc(20*sizeof(char)); sprintf(name, "name : %d", i);
            Node_set(&(world->nodes[i]), (Vector2){randomX, randomY}, RED);
            //free(name);
        }
        else
        {
            randomX = randfrom(-15.0, 15.0);
            randomY = randfrom(-15.0, 15.0);
            //char name[20]; sprintf(name, "name : %d", i);        
            Node_set(&(world->nodes[i]), (Vector2){randomX, randomY}, RED);
        }
    }
    //Gabriel graph sort
    for (int i = 0; i < nbNode - 1; i++)
    {
        for (int j = i + 1; j < nbNode; j++)
        {
            int compteurPointDansLeCercle = 0;
            float xm = 0.5 * (world->nodes[i].position.x + world->nodes[j].position.x);
            float ym = 0.5 * (world->nodes[i].position.y + world->nodes[j].position.y);
            Vector2 M = {xm, ym};
            float distNodeCenterOfij = dist(world->nodes[i].position, M);
            for (int k = 0; k < nbNode; k++)
            {
                if (dist(world->nodes[k].position, M) < distNodeCenterOfij - 0.05)
                {
                    compteurPointDansLeCercle++;
                }
            }
            if (compteurPointDansLeCercle == 0)
            {
                NetWorld_biconnect(world, i, j);
            }
        }
    }   
}