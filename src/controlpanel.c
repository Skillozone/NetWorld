#include "controlpanel.h"

#include "raylib.h"
#include "raymath.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Tools
void printVector2( Vector2 v )
{
    printf( "[%3f, %3f]", v.x, v.y );
}

// Constructor / Destructor
Panel * Panel_new()
{
    Panel * p = malloc( sizeof(Panel) );
    return p;
}

void Panel_delete(Panel * self)
{
    free(self);
}

// Initialization
void Panel_initialize(Panel * self, NetWorld * world, const int screenWidth, const int screenHeight)
{
    self->world= world;
    self->camera.x= 0.f;
    self->camera.y= 0.f;
    self->screenCenter.x= screenWidth/2;
    self->screenCenter.y= screenHeight/2;
    self->scale= 10.f; //pixel per meters
    self->screenWidth = screenWidth;
    self->screenHeight = screenHeight;
}

// To String
void Panel_print(Panel * self)
{
    printf( "Panel camera(x-%f, y-%f, scale-%f)\n",
            self->camera.x,
            self->camera.y,
            self->scale);
}

// Rendering

void Panel_drawMainMenu(Panel * self, Main_Menu * menu){
    Font font = GetFontDefault();
    BeginDrawing();
    
    DrawText("RISK", (self->screenWidth*35)/100 , (self->screenHeight*10)/100 , (self->screenWidth*10)/100,BLACK);
    //Draw each button
    for(int index = 0; index < menu->buttonCount; index++){
        Menu_Button_draw(menu->buttons[index], &font, self->screenWidth, self->screenHeight, RED, (self->screenHeight*4)/100, (self->screenWidth/75), true);
    }    
    ClearBackground(RAYWHITE);
    UnloadFont(font);
    EndDrawing(); 
}

void Panel_drawOptionsMenu(Panel * self, Options_Menu * menu){
    Font font = GetFontDefault();
    BeginDrawing();
    
    DrawText("OPTIONS", (self->screenWidth*35)/100 , (self->screenHeight*15)/100 , (self->screenWidth*5)/100,BLACK);
    //Draw each input field
    for(int index = 0; index < menu->inputCount; index++){
        Int_Input_draw(menu->inputs[index], &font, self->screenWidth, self->screenHeight);
    }

    DrawRectangleRec(menu->saveReturnBtn, GREEN);
    DrawRectangleRec(menu->smallerSaveReturnBtn, WHITE);
    DrawTextRec(font, "\tSave and Exit", menu->saveReturnBtn,(self->screenHeight*5)/100, (self->screenWidth/400), true, BLACK);
    ClearBackground(RAYWHITE);
    UnloadFont(font);
    EndDrawing();
}

void Panel_drawRules(Panel * self, Main_Menu * rules){
    Font font = GetFontDefault();
    BeginDrawing();
    DrawText("RULES", (self->screenWidth*40)/100 , (self->screenHeight*15)/100 , (self->screenWidth*5)/100,BLACK);

    Menu_Button_draw(rules->buttons[0], &font, self->screenWidth, self->screenHeight, GREEN, (self->screenHeight*4)/100, (self->screenWidth/400), true);
    Menu_Button_draw(rules->buttons[1], &font, self->screenWidth, self->screenHeight, BLACK, self->screenHeight/40, (self->screenWidth/400), true);
    
    ClearBackground(RAYWHITE);
    UnloadFont(font);
    EndDrawing();
}

void Panel_drawWin(Panel * self, Player * player, Mission * mission){
    BeginDrawing();
    Font font = GetFontDefault();

    DrawText("VICTORY", (self->screenWidth*35)/100 , (self->screenHeight*15)/100 , (self->screenWidth*5)/100,BLACK);

    char * victoryText = malloc(sizeof(char)*100);
    sprintf(victoryText, "%s has completed their mission and won the game\nTheir mission was : %s", player->name, mission->displayText);
    DrawText(victoryText, (self->screenWidth*20)/100, (self->screenHeight*45)/100, (self->screenWidth*2)/100, BLACK);
    free(victoryText);
    
    UnloadFont(font);
    ClearBackground(RAYWHITE);
    EndDrawing();
}

void Panel_drawGame(Panel * self)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    // Draw the edges for each nodes:
    for(int i= 0 ; i < self->world->size ; ++i )
    {
        Node * n= &(self->world->nodes[i]);
        for(int j= 0 ; j < n->card ; ++j )
            Panel_drawEdge( self, &(n->edges[j]) );
    }

    // Draw the nodes
    for(int i= 0 ; i < self->world->size ; ++i )
    {
        Panel_drawNode( self, &(self->world->nodes[i]) );
    }
    //Panel_drawBasis(self);
    EndDrawing(); 
}

void Panel_drawBasis(Panel * self)
{
    Vector2 screen00= {0.f, 0.f};
    screen00= Panel_pixelFromPosition(self, &( screen00 ) );
    Vector2 screen10= {1.f, 0.f};
    screen10= Panel_pixelFromPosition(self, &( screen10 ) );
    Vector2 screen01= {0.f, 1.f}; 
    screen01= Panel_pixelFromPosition(self, &( screen01 ) );
    DrawCircleV( screen00, 4, BLUE );   
    DrawLineV( screen00, screen10, RED );
    DrawLineV( screen00, screen01, BLUE );
}

void Panel_drawNode(Panel * self, Node * n)
{
    Vector2 screenPosition= Panel_pixelFromPosition(self, &(n->position) );
    DrawCircleV(screenPosition, 24, n->color);
    DrawCircleV(screenPosition, 20, RAYWHITE);
    char * soldierText = malloc(20*sizeof(char));
    sprintf(soldierText, "%d", n->soldiers);
    DrawText(soldierText, (int)screenPosition.x - MeasureText(soldierText, 20)/2, (int)screenPosition.y, 20, n->color);
    free(soldierText);
}

void Panel_drawEdge(Panel * self, Edge * e)
{
    Vector2 source= Panel_pixelFromPosition(self, &(e->_source->position) );
    Vector2 target= Panel_pixelFromPosition(self, &(e->_target->position) );

    Vector2 ortho= (Vector2){ target.x-source.x, target.y-source.y }; // Vector from Source to Target

    float ratio= 10.f / Vector2Length( ortho );
    ortho= (Vector2){ -ortho.y*ratio, ortho.x*ratio };// 10 ortho-normal vector from v 

    Vector2 source1= (Vector2){source.x-ortho.x, source.y-ortho.y};
    Vector2 source2= (Vector2){source.x+ortho.x, source.y+ortho.y};

    DrawTriangle(source1, source2, target, e->color);
}

Vector2 Panel_pixelFromPosition(Panel * self, Vector2 * p)
{
    Vector2 pixel= {
        self->screenCenter.x + (p->x - self->camera.x ) * self->scale,
        self->screenCenter.y - (p->y - self->camera.y ) * self->scale
    };
    return pixel;
}

Vector2 Panel_positionFromPixel(Panel * self, Vector2 * p)
{
    Vector2 position= { p->x, p->y };
    return position;
}

void Panel_control(Panel * self)
{
    Panel_controlCamera(self);
}

void Panel_controlCamera(Panel * self)
{
    // KEYBOARD Control:
    float step= 3.0f / self->scale;
    if (IsKeyDown(KEY_RIGHT)) self->camera.x += step;
    if (IsKeyDown(KEY_LEFT)) self->camera.x -= step;
    if (IsKeyDown(KEY_UP)) self->camera.y += step;
    if (IsKeyDown(KEY_DOWN)) self->camera.y -= step;

    self->scale += (GetMouseWheelMove()*1.f);
    self->scale = fmaxf( self->scale, 0.001f );
}