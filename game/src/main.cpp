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

void updatesState(Player &player)
{
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


        //check if player is in the black box
        if (player.getPosition().x >= -2 && player.getPosition().x <= 2 && player.getPosition().z >= -2 && player.getPosition().z <= 2)
            if (player.getStress() <= 98)
                player.setStress(player.getStress() + 2);
            else
                player.setStress(100);

        //check if player is in the red box
        if (player.getPosition().x >= 8 && player.getPosition().x <= 10 && player.getPosition().z >= 8 && player.getPosition().z <= 10)
            if (player.getFood() <= 95)
                player.setFood(player.getFood() + 5);
            else
                player.setFood(100);

        //check if player is in the blue box
        if (player.getPosition().x >= 8 && player.getPosition().x <= 10 && player.getPosition().z >= -10 && player.getPosition().z <= -8)
            if (player.getWater() <= 95)
                player.setWater(player.getWater() + 5);
            else
                player.setWater(100);

        //check if player is in the yellow box
        if (player.getPosition().x >= -10 && player.getPosition().x <= -8 && player.getPosition().z >= 8 && player.getPosition().z <= 10)
            if (player.getToilet() >= 5)
                player.setToilet(player.getToilet() - 5);
            else
                player.setToilet(0);

        if (player.getPosition().x >= -10 && player.getPosition().x <= -8 && player.getPosition().z >= -10 && player.getPosition().z <= -8)
            if (player.getStress() >= 5)
                player.setStress(player.getStress() - 5);
            else
                player.setStress(0);

    }

}


void drawBoxWork(Player& player)
{
    DrawCube({1, 1, 0}, 1, 1, 2, BLACK);
    DrawCube({9, 0, 9}, 1, 1, 1, RED);
    DrawCube({9, 0, -9}, 1, 1, 1, BLUE);
    DrawCube({-9, 0, 9}, 1, 1, 1, YELLOW);
    DrawCube({-9, 0, -9}, 1, 1, 1, BROWN);


}

int main()
{
    const int screenWidth = 1600;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Game");
    SetTargetFPS(60);

    Camera camera = createCamera();
    Player player = Player();

    Level level = generateRoom();

    Vector3 oldPosition;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Updates
        oldPosition = player.getPosition();
        updatesState(player);

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
        if (level.checkCollisions(player))
            player.setPosition(oldPosition);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
            drawBoxWork(player);

            player.drawModel();
            DrawGrid(20, 1.0f);
            level.drawWalls();
            level.drawProps();

            EndMode3D();
            player.drawUI(camera);

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}