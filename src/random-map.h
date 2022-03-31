#ifndef RANDOMMAP_H
#define RANDOMMAP_H

#include "raylib.h"
#include "networld.h"



//random function
double randfrom(double min, double max);       

//distance between 2 points(Vector2)
double dist(Vector2 vector1, Vector2 vector2);  

//distance between 2 nodes
double distNode(Node node1, Node node2);

//generation of a random map following Gabriel Graph theory
void Random_map(NetWorld * world);

#endif