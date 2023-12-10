/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** main.cpp
*/

#include "Menu.hpp"
#include "render.hpp"
#include "Player.hpp"
#include "Enemies.hpp"
#include "Level.hpp"

#include <cstdlib>
#include <thread>

#define MAX_COLUMNS 20

Camera createCamera(void)
{
    Camera camera = { 0 };
    camera.position = (Vector3){ 0, 0, 0};              // Camera position
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 70.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    return camera;
}

void updatesState(Player &player, Boxes boxes)
{
    BoundingBox blackBox = boxes.blackBox;
    BoundingBox redBox = boxes.redBox;
    BoundingBox blueBox = boxes.blueBox;
    BoundingBox yellowBox = boxes.yellowBox;
    BoundingBox brownBox = boxes.brownBox;

    if (GetTime() - player.getTick() >= 1) {
        player.setTick(GetTime());
        if (player.getFood() <= 0)
            player.setHp(player.getHp() - 0.01);
        else {
            player.setFood(player.getFood() - 0.01);
        }
        if (player.getWater() <= 0)
            player.setHp(player.getHp() - 0.01);
        else {
            player.setWater(player.getWater() - 0.01);
            if (player.getToilet() >= 100)
                player.setHp(player.getHp() - 0.01);
            else
                player.setToilet(player.getToilet() + 1);
        }
        if (player.getStress() >= 100)
            player.setHp(player.getHp() - 1);
        if (player.getFood() >= 25 && player.getWater() >= 25 && player.getToilet() <= 95)
            if (player.getHp() <= 98)
                player.setHp(player.getHp() + 2);

        // Check if player is in the black box
        if (CheckCollisionBoxes(player.getBoundingBox(), blackBox)) {
            if (player.getStress() <= 98)
                player.setStress(player.getStress() + 2);
            else
                player.setStress(100);
        }

        // Check if player is in the red box
        if (CheckCollisionBoxes(player.getBoundingBox(), redBox)) {
            if (player.getFood() <= 95)
                player.setFood(player.getFood() + 5);
            else
                player.setFood(100);
        }

        // Check if player is in the blue box
        if (CheckCollisionBoxes(player.getBoundingBox(), blueBox)) {
            if (player.getWater() <= 95)
                player.setWater(player.getWater() + 5);
            else
                player.setWater(100);
        }

        // Check if player is in the yellow box
        if (CheckCollisionBoxes(player.getBoundingBox(), yellowBox)) {
            if (player.getToilet() >= 5)
                player.setToilet(player.getToilet() - 5);
            else
                player.setToilet(0);

            if (player.getStress() >= 5)
                player.setStress(player.getStress() - 5);
            else
                player.setStress(0);
        }

        // Check if player is in the brown box
        if (CheckCollisionBoxes(player.getBoundingBox(), brownBox)) {
            if (player.getToilet() >= 5)
                player.setToilet(player.getToilet() - 5);
            else
                player.setToilet(0);

            if (player.getStress() >= 5)
                player.setStress(player.getStress() - 5);
            else
                player.setStress(0);
        }
    }
}

void drawBoxWork(Boxes boxes)
{
    DrawCube({1, 1, 0}, 1, 1, 2, BLACK);
    DrawCube({9, 0, 9}, 1, 1, 1, RED);
    DrawCube({9, 0, -9}, 1, 1, 1, BLUE);
    DrawCube({-9, 0, 9}, 1, 1, 1, YELLOW);
    DrawCube({-9, 0, -9}, 1, 1, 1, BROWN);
}

BoundingBox createBoundingBoxForCube(Vector3 position, float width, float height, float length)
{
    BoundingBox box;
    box.min = (Vector3){position.x - width/2, position.y - height/2, position.z - length/2};
    box.max = (Vector3){position.x + width/2, position.y + height/2, position.z + length/2};
    return box;
}

Boxes createBoxes(void)
{
    Boxes boxes;

    boxes.blackBox = createBoundingBoxForCube({1, 1, 0}, 1, 1, 2);
    boxes.redBox = createBoundingBoxForCube({9, 0, 9}, 1, 1, 1);
    boxes.blueBox = createBoundingBoxForCube({9, 0, -9}, 1, 1, 1);
    boxes.yellowBox = createBoundingBoxForCube({-9, 0, 9}, 1, 1, 1);
    boxes.brownBox = createBoundingBoxForCube({-9, 0, -9}, 1, 1, 1);

    return boxes;
}

int main()
{
    const int screenWidth = 1600;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Game");
    SetTargetFPS(60);

    Camera camera = createCamera();
    Player player = Player();
    Boxes boxes = createBoxes();

    Level level = generateRoom();

    Vector3 oldPosition;

    Menu menu;
    menu.loop();

    // Main game loop
    while (!WindowShouldClose())
    {
        // Updates
        oldPosition = player.getPosition();
        updatesState(player, boxes);

        // inscre the stress when i work
        if (player.getHp() <= 0)
            break;// FAIRE UN  GAME OVER QUAND IL A PLUS DE VIE
        camera.target = oldPosition;
        camera.position = (Vector3){
            static_cast<float>(player.getPosition().x + 0.5),
            static_cast<float>(player.getPosition().y + 15),
            static_cast<float>(player.getPosition().z)
        };

        player.update();
        // if (level.checkCollisions(player))
        //     player.setPosition(oldPosition);

        // if (level.checkPropCollisions(player))
        //     player.setPosition(oldPosition);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
            drawBoxWork(boxes);

            player.drawModel();

            level.drawWalls();
            level.drawProps();

            EndMode3D();
            player.drawUI(camera);

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}