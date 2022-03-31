#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "graphical-aspect.h"
#include "networld.h"
#include "controlpanel.h"
#include "player.h"

#include "raylib.h"

void Graphic_ShowPlayerInfo(Player *player, int screenWidth, int screenHeight, Font *font)
{
    Rectangle rec = {0, screenHeight - 250, 250, 250};                                  //Draw current player number on the bottom left
    DrawRectangleLinesEx(rec, 10, player->color);
    char *playerNumber = malloc(20 * sizeof(char));
    sprintf(playerNumber, "%s", player->name);
    DrawTextEx(*font, playerNumber, (Vector2){35, screenHeight - 240}, 30.0, 3.0, player->color);

    char *soldierNumber = malloc(40 * sizeof(char));                                    //Draw current player number of soldiers
    sprintf(soldierNumber, "Soldiers left %d", player->soldiers);
    DrawTextEx(*font, soldierNumber, (Vector2){15, screenHeight - 180}, 24.0, 3.0, player->color);

    int totalTroops = 0;
    for (int i = 0; i < player->nodeCount; i++)
    {
        totalTroops += player->nodes[i]->soldiers;
    }
    char *str_totalTroops = malloc(40 * sizeof(char));                                  //Draw current player number of total troops owned
    sprintf(str_totalTroops, "Total Troops %d", totalTroops);
    DrawTextEx(*font, str_totalTroops, (Vector2){15, screenHeight - 150}, 24.0, 3.0, player->color);

    char *str_nodeCount = malloc(40 * sizeof(char));                                    //Draw current player number of nodes owned
    sprintf(str_nodeCount, "Nodes owned %d", player->nodeCount);
    DrawTextEx(*font, str_nodeCount, (Vector2){15, screenHeight - 120}, 24.0, 3.0, player->color);

    free(playerNumber);
    free(soldierNumber);
    free(str_totalTroops);
    free(str_nodeCount);
}

void Graphic_RecrutementPhase(Player *player, int screenWidth, int screenHeight, Font *font)
{
    Rectangle rec = {screenWidth - 300, 100, 300, 400};                                 //Display recruitment phase rules
    DrawRectangleLinesEx(rec, 10, player->color);
    DrawTextEx(*font, "Recrutement Phase", (Vector2){screenWidth - 275, 120}, 23.0, 3.0, player->color);
    DrawTextRec(*font, "   LEFT click on one of your node to recruit a soldier", (Rectangle){screenWidth - 285, 175, 270, 100}, 20.0, 3.0, true, player->color);
    DrawTextRec(*font, "   RIGHT click on the same node to remove the soldier", (Rectangle){screenWidth - 285, 295, 270, 100}, 20.0, 3.0, true, player->color);
    DrawTextRec(*font, "   click Confirm once finished", (Rectangle){screenWidth - 285, 415, 270, 100}, 20.0, 3.0, true, player->color);
}
void Graphic_AttackPhase(Player *player, int screenWidth, int screenHeight, Font *font)
{
    Rectangle rec = {screenWidth - 300, 100, 300, 450};                                 //Display attack phase rules
    DrawRectangleLinesEx(rec, 10, player->color);
    DrawTextEx(*font, "Attack Phase", (Vector2){screenWidth - 265, 120}, 23.0, 3.0, player->color);
    DrawTextRec(*font, "   FIRST click on the node you want to attack from", (Rectangle){screenWidth - 285, 175, 270, 100}, 20.0, 3.0, true, player->color);
    DrawTextRec(*font, "   THEN click on one of neighbouring node you want to attack", (Rectangle){screenWidth - 285, 295, 270, 100}, 20.0, 3.0, true, player->color);
    DrawTextRec(*font, "   click Next Turn once finished all your attacks", (Rectangle){screenWidth - 285, 415, 270, 100}, 20.0, 3.0, true, player->color);
}

void Graphic_WhoseTurnIsIt(Player *player, int screenWidth, int screenHeight, Font *font)
{
    char *whoseTurn = malloc(20 * sizeof(char));                                        //Display whose turn is it
    sprintf(whoseTurn, "%ss Turn", player->name);
    DrawTextEx(*font, whoseTurn, (Vector2){screenWidth / 2 - (MeasureTextEx(*font, whoseTurn, 50.0, 3.0).x) / 2, 30}, 50.0, 3.0, player->color);
    free(whoseTurn);
}

Rectangle Graphic_ConfirmButton(Font *font)
{                                                                                       //Confirm button for the recruitment phase
    Rectangle nextPhase = {200, 200, 220, 55};
    DrawRectangleRec(nextPhase, GREEN);
    DrawTextEx(*font, "Confirm", (Vector2){220, 210}, 40.0, 3.0, BLACK);
    return nextPhase;
}

void Graphic_MouseHoverNodeRecrutement(Player *player, Vector2 mousePosition, Panel *panel)
{
    for (int nodeIndex = 0; nodeIndex < player->nodeCount; nodeIndex++)
    {
        Node *currentNode = player->nodes[nodeIndex];                                   //Draw a small ring when mouse hover one current player's node
        if (CheckCollisionPointRec(mousePosition, currentNode->collisionHitbox))
        {
            Vector2 screenPosition = Panel_pixelFromPosition(panel, &(currentNode->position));
            DrawRing(screenPosition, 24.0, 28.0, 0.0, 360.0, 0.1, MAGENTA);
            if (player->soldiers > 0)
            {
                DrawText("+1", (int)screenPosition.x + 30, (int)screenPosition.y, 20, MAGENTA);
            }
        }
    }
}

void Graphic_MouseHoverNodeChooseAttacker(Player *player, Vector2 mousePosition, Panel *panel)
{
    for (int nodeIndex = 0; nodeIndex < player->nodeCount; nodeIndex++)
    {
        Node *currentNode = player->nodes[nodeIndex];                                   //Draw a small ring when mouse hover one current player's node
        if (CheckCollisionPointRec(mousePosition, currentNode->collisionHitbox))        //and draw persistent ring when an attacker node is selected
        {                                                                       
            Vector2 screenPosition = Panel_pixelFromPosition(panel, &(currentNode->position));
            if (!player->hasSelectedNode && currentNode->soldiers > 1)
            {
                DrawRing(screenPosition, 24.0, 28.0, 0.0, 360.0, 0.1, GOLD);
                DrawText("attacker", (int)screenPosition.x + 30, (int)screenPosition.y, 20, GOLD);
                Graphic_MouseHoverNodeChooseTarget(currentNode, mousePosition, panel);
            }
        }
    }
    if (player->hasSelectedNode)
    {
        Vector2 screenPosition = Panel_pixelFromPosition(panel, &(player->selectedNode->position));
        DrawRing(screenPosition, 24.0, 28.0, 0.0, 360.0, 0.1, GOLD);
        DrawText("attacker", (int)screenPosition.x + 30, (int)screenPosition.y, 20, GOLD);
    }
}

void Graphic_MouseHoverNodeChooseTarget(Node *originNode, Vector2 mousePosition, Panel *panel)
{
    for (int neighbourIndex = 0; neighbourIndex < originNode->card; neighbourIndex++)       //Draw a ring for all the enemy nodes which can be attacked from the current selected attacker
    {                                                                                           
        Vector2 screenPosition = Panel_pixelFromPosition(panel, &(originNode->edges[neighbourIndex]._target->position));
        if (originNode->edges[neighbourIndex]._target->color.r != originNode->color.r || originNode->edges[neighbourIndex]._target->color.g != originNode->color.g || originNode->edges[neighbourIndex]._target->color.b != originNode->color.b || originNode->edges[neighbourIndex]._target->color.a != originNode->color.a)
        {
            DrawRing(screenPosition, 24.0, 30.0, 0.0, 360.0, 0.1, GREEN);
            if (CheckCollisionPointRec(mousePosition, originNode->edges[neighbourIndex]._target->collisionHitbox) && &(originNode->edges[neighbourIndex]._target->color) != &(originNode->color))
            {
                DrawRing(screenPosition, 30.0, 33.0, 0.0, 360.0, 0.1, MAROON);
            }
        }
    }
}

int Graphic_ChooseNumberOfAttackers(Player *attacker, Player *defender, Node *originNode, Node *targetNode, Font *font)
{
    const int screenWidth = 1700;
    const int screenHeight = 800;
    bool endAnimation = false;
    SetTargetFPS(60);
                                                                    //Display rectangles to choose how many soldiers/dices you want to engage in the fight
    Rectangle nbAttackerRectangle[10];            
    for (int i = 0; i < originNode->soldiers; i++)
    {
        nbAttackerRectangle[i] = (Rectangle){200 + (i - 1) * 250, screenHeight - 500, 150, 70};
    }
    char whoseTurnToAttack[20];
    sprintf(whoseTurnToAttack, "%s attacks ", attacker->name);
    char whoseTurnToDefend[20];
    sprintf(whoseTurnToDefend, "%s", defender->name);

    while (!endAnimation)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Vector2 mousePosition = GetMousePosition();

        DrawTextEx(*font, whoseTurnToAttack, (Vector2){screenWidth / 2 - (MeasureTextEx(*font, whoseTurnToAttack, 50.0, 3.0).x) + 100, 70}, 50.0, 3.0, attacker->color);
        DrawTextEx(*font, whoseTurnToDefend, (Vector2){screenWidth / 2 + 100, 70}, 50.0, 3.0, defender->color);
        DrawText("How many dices do you want to involve in the fight ?", screenWidth / 2 - (MeasureTextEx(*font, "How many dice do you want to involve in the fight ?", 30.0, 3.0).x) / 2 + 50, 150, 30, attacker->color);

        for (int i = 1; i < originNode->soldiers; i++)
        {
            DrawRectangleRec(nbAttackerRectangle[i], BLACK);
            char str_i[5];
            sprintf(str_i, "%d", i);
            DrawTextEx(*font, str_i, (Vector2){nbAttackerRectangle[i].x + 55, nbAttackerRectangle[i].y + 5}, 70.0, 3.0, WHITE);
            if (CheckCollisionPointRec(mousePosition, nbAttackerRectangle[i]))
            {
                DrawRectangleLinesEx(nbAttackerRectangle[i], 5, GREEN);
            }
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                if (CheckCollisionPointRec(mousePosition, nbAttackerRectangle[i]))
                {
                    printf("colision dés choix %d \n", i);
                    return i;
                }
            }
        }
        EndDrawing();
    }
}

void Graphic_diceRolling(Player *attacker, Player *defender, Node *originNode, Node *targetNode, int nbOfAttackers, int nbOfDefenders, int *listOfDices, Font *font)
{

    const int screenWidth = 1700;
    const int screenHeight = 800;
    Image texture = LoadImage("resources/diceRolling.png");
    ImageResize(&(texture), 100, 800);
    Texture2D diceTexture = LoadTextureFromImage(texture);

    int defendersCount = nbOfDefenders;
    int attackersCount = nbOfAttackers;
    char *whoseTurnToAttack = malloc(20 * sizeof(char));
    sprintf(whoseTurnToAttack, "%s ", attacker->name);
    char *whoseTurnToDefend = malloc(20 * sizeof(char));
    sprintf(whoseTurnToDefend, "%s ", defender->name);
    Rectangle skipAnimation = {screenWidth / 2 - 225, 200, 190, 50};
    Rectangle skipResult = {screenWidth / 2 - 205, 200, 150, 50};

    Vector2 *positionDiceAttacker = malloc(20 * sizeof(Vector2));
    Vector2 *positionDiceDefender = malloc(20 * sizeof(Vector2));
    for (int i = 0; i < nbOfAttackers; i++)
    {
        positionDiceAttacker[i] = (Vector2){200 + (i)*150, screenHeight - 500};
    }
    for (int i = 0; i < defendersCount; i++)
    {
        positionDiceDefender[i] = (Vector2){1000 + (i)*150, screenHeight - 500};
    }

    Rectangle frameRec = {0.0f, 0.0f, (float)diceTexture.width, (float)diceTexture.height / 9};
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 7;
    int frameExit = 0;
    bool endAnimationDice = false;
    SetTargetFPS(60);

    while (!endAnimationDice)                   //Animation of dices
    {
        Vector2 mousePosition = GetMousePosition();
        framesCounter++;
        frameExit++;

        if (frameExit == 200)
            endAnimationDice = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePosition, skipAnimation))
            {
                endAnimationDice = true;
            }
        }

        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > 8)
                currentFrame = 0;
            frameRec.y = (float)currentFrame * (float)diceTexture.height / 9;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextEx(*font, whoseTurnToAttack, (Vector2){250, 100}, 40.0, 3.0, attacker->color);
        DrawTextEx(*font, whoseTurnToDefend, (Vector2){screenWidth - 700, 100}, 40.0, 3.0, defender->color);
        DrawTextEx(*font, " attacker", (Vector2){225, 150}, 30.0, 3.0, attacker->color);
        DrawTextEx(*font, " defender", (Vector2){screenWidth - 725, 150}, 30.0, 3.0, defender->color);
        DrawRectangleRec(skipAnimation, BLUE);
        DrawTextEx(*font, "Skip Animation", (Vector2){screenWidth / 2 - 215, 210}, 18.0, 3.0, BLACK);
        for (int i = 0; i < nbOfAttackers; i++)
        {
            DrawTextureRec(diceTexture, frameRec, positionDiceAttacker[i], WHITE);
        }
        for (int i = 0; i < defendersCount; i++)
        {
            DrawTextureRec(diceTexture, frameRec, positionDiceDefender[i], WHITE);
        }

        EndDrawing();
    }

    currentFrame = 0;
    framesCounter = 0;
    bool endDisplayResult = false;

    while (!endDisplayResult)                   //Display result of the dice rolling
    {
        Vector2 mousePosition = GetMousePosition();
        framesCounter++;
        frameExit++;

        if (frameExit == 350)
            endDisplayResult = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePosition, skipResult))
            {
                endDisplayResult = true;
            }
        }

        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame > 8)
                currentFrame = 0;
            frameRec.y = (float)currentFrame * (float)diceTexture.height / 9;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextEx(*font, whoseTurnToAttack, (Vector2){250, 100}, 40.0, 3.0, attacker->color);
        DrawTextEx(*font, whoseTurnToDefend, (Vector2){screenWidth - 700, 100}, 40.0, 3.0, defender->color);
        DrawTextEx(*font, " attacker", (Vector2){225, 150}, 30.0, 3.0, attacker->color);
        DrawTextEx(*font, " defender", (Vector2){screenWidth - 725, 150}, 30.0, 3.0, defender->color);
        DrawRectangleRec(skipResult, BLUE);
        DrawTextEx(*font, "Skip Result", (Vector2){screenWidth / 2 - 200, 210}, 18.0, 3.0, BLACK);
        for (int i = 0; i < nbOfAttackers; i++)
        {
            switch (listOfDices[i])
            {
            case 1:
                frameRec.y = 9 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceAttacker[i], WHITE);
                DrawTextEx(*font, "1", (Vector2){positionDiceAttacker[i].x + 30, positionDiceAttacker[i].y + 100}, 50.0, 3.0, BLACK);
                break;
            case 2:
                frameRec.y = 1 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceAttacker[i], WHITE);
                DrawTextEx(*font, "2", (Vector2){positionDiceAttacker[i].x + 30, positionDiceAttacker[i].y + 100}, 50.0, 3.0, BLACK);
                break;
            case 3:
                frameRec.y = 2 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceAttacker[i], WHITE);
                DrawTextEx(*font, "3", (Vector2){positionDiceAttacker[i].x + 30, positionDiceAttacker[i].y + 100}, 50.0, 3.0, BLACK);
                break;
            case 4:
                frameRec.y = 3 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceAttacker[i], WHITE);
                DrawTextEx(*font, "4", (Vector2){positionDiceAttacker[i].x + 30, positionDiceAttacker[i].y + 100}, 50.0, 3.0, BLACK);
                break;
            case 5:
                frameRec.y = 4 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceAttacker[i], WHITE);
                DrawTextEx(*font, "5", (Vector2){positionDiceAttacker[i].x + 30, positionDiceAttacker[i].y + 100}, 50.0, 3.0, BLACK);
                break;
            case 6:
                frameRec.y = 5 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceAttacker[i], WHITE);
                DrawTextEx(*font, "6", (Vector2){positionDiceAttacker[i].x + 30, positionDiceAttacker[i].y + 100}, 50.0, 3.0, BLACK);
                break;

            default:
                break;
            }
        }
        for (int i = nbOfAttackers; i < nbOfAttackers + defendersCount; i++)
        {
            switch (listOfDices[i])
            {
            case 1:
                frameRec.y = 9 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceDefender[i - nbOfAttackers], WHITE);
                DrawTextEx(*font, "1", (Vector2){positionDiceDefender[i - nbOfAttackers].x + 30, positionDiceDefender[i - nbOfAttackers].y + 100}, 50.0, 3.0, BLACK);
                break;
            case 2:
                frameRec.y = 1 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceDefender[i - nbOfAttackers], WHITE);
                DrawTextEx(*font, "2", (Vector2){positionDiceDefender[i - nbOfAttackers].x + 30, positionDiceDefender[i - nbOfAttackers].y + 100}, 50.0, 3.0, BLACK);
                break;
            case 3:
                frameRec.y = 2 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceDefender[i - nbOfAttackers], WHITE);
                DrawTextEx(*font, "3", (Vector2){positionDiceDefender[i - nbOfAttackers].x + 30, positionDiceDefender[i - nbOfAttackers].y + 100}, 50.0, 3.0, BLACK);
                break;
            case 4:
                frameRec.y = 3 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceDefender[i - nbOfAttackers], WHITE);
                DrawTextEx(*font, "4", (Vector2){positionDiceDefender[i - nbOfAttackers].x + 30, positionDiceDefender[i - nbOfAttackers].y + 100}, 50.0, 3.0, BLACK);
                break;
            case 5:
                frameRec.y = 4 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceDefender[i - nbOfAttackers], WHITE);
                DrawTextEx(*font, "5", (Vector2){positionDiceDefender[i - nbOfAttackers].x + 30, positionDiceDefender[i - nbOfAttackers].y + 100}, 50.0, 3.0, BLACK);
                break;
            case 6:
                frameRec.y = 5 * (float)diceTexture.height / 9;
                DrawTextureRec(diceTexture, frameRec, positionDiceDefender[i - nbOfAttackers], WHITE);
                DrawTextEx(*font, "6", (Vector2){positionDiceDefender[i - nbOfAttackers].x + 30, positionDiceDefender[i - nbOfAttackers].y + 100}, 50.0, 3.0, BLACK);
                break;

            default:
                break;
            }
        }

        int remainingAttackers = attackersCount;
        for (int index = 0; index < fmin(defendersCount, attackersCount); index++)
        {
            if (listOfDices[index] > listOfDices[index + attackersCount])
            {
                DrawTextEx(*font, defender->name, (Vector2){screenWidth / 2 - 300, 600}, 50.0, 3.0, BLACK);
                DrawTextEx(*font, " lose a soldier", (Vector2){screenWidth / 2 -300 + MeasureTextEx(*font, defender->name, 50.0, 3.0).x , 600}, 50.0, 3.0, defender->color);
            }
            else
            {
                DrawTextEx(*font, attacker->name, (Vector2){screenWidth / 2 - 300, 600}, 50.0, 3.0, BLACK);
                DrawTextEx(*font, " lose a soldier", (Vector2){screenWidth / 2 - 300 + MeasureTextEx(*font, attacker->name, 50.0, 3.0).x , 600}, 50.0, 3.0, attacker->color);
            }
        }

        if (targetNode->soldiers <= 0)
        {
            DrawTextEx(*font, "Node has been conquered", (Vector2){screenWidth / 2 - MeasureTextEx(*font, "Node has been conquered", 50.0, 3.0).x / 2 - 50, 700}, 50.0, 3.0, BLACK);
        }

        EndDrawing();
    }
    free(whoseTurnToAttack);
    free(whoseTurnToDefend);
    free(positionDiceAttacker);
    free(positionDiceDefender);
    UnloadImage(texture);
    UnloadTexture(diceTexture);
}
