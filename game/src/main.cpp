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

Level init_world()
{
    Level level;

    return level;
}

int main()
{
    const int screenWidth = 1600;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Game");
    SetTargetFPS(60);

    Camera camera = createCamera();
    camera.projection == CAMERA_ORTHOGRAPHIC;
    Player player = Player();

    Level level = Level();
    int roomWidth = 20;
    int roomLength = 20;

    // Front and back walls
    Wall wall1((Vector3){0.0f, 1.5f, (float)roomLength / 2.0f}, (Vector3){(float)roomWidth, 3.0f, 1.0f});
    level.addWall(wall1);

    Wall wall2((Vector3){0.0f, 1.5f, -(float)roomLength / 2.0f}, (Vector3){(float)roomWidth, 3.0f, 1.0f});
    level.addWall(wall2);

    // Left and right walls
    Wall wall3((Vector3){(float)roomWidth / 2.0f, 1.5f, 0.0f}, (Vector3){1.0f, 3.0f, (float)roomLength});
    level.addWall(wall3);

    Wall wall4((Vector3){-(float)roomWidth / 2.0f, 1.5f, 0.0f}, (Vector3){1.0f, 3.0f, (float)roomLength});
    level.addWall(wall4);

    Vector3 oldPosition;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Updates
        oldPosition = player.getPosition();

        camera.target = oldPosition;
        camera.position = (Vector3){player.getPosition().x + 0.5, player.getPosition().y + 15, player.getPosition().z};

        player.update();
        if (level.checkCollisions(player))
            player.setPosition(oldPosition);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);

            player.drawModel();
            DrawGrid(20, 1.0f);
            level.drawWalls();

            EndMode3D();
            player.drawUI(camera);

        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
