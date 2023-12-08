/*
** EPITECH PROJECT, 2022
** GameJam2023-YingYang
** File description:
** Generation.cpp
*/

#include "render.hpp"

#include "Level.hpp"
#include "Enemies.hpp"
#include "Items.hpp"

Level proceduralGeometry()
{
    Level level;
    Enemy enemy;
    Item item;

    Wall wall;
    // Create random rooms
    //int numRooms = GetRandomValue(2, 5);

    int roomWidth = GetRandomValue(20, 40);
    int roomLength = GetRandomValue(20, 40);

    // Front and back walls
    wall.size = (Vector3){(float)roomWidth, 3.0f, 1.0f};
    wall.position = (Vector3){0.0f, 1.5f, (float)roomLength / 2.0f};
    level.addWall(wall);

    wall.size = (Vector3){(float)roomWidth, 3.0f, 1.0f};
    wall.position = (Vector3){0.0f, 1.5f, -(float)roomLength / 2.0f};
    level.addWall(wall);

    // Left and right walls
    wall.size = (Vector3){1.0f, 3.0f, (float)roomLength};
    wall.position = (Vector3){(float)roomWidth / 2.0f, 1.5f, 0.0f};
    level.addWall(wall);

    wall.size = (Vector3){1.0f, 3.0f, (float)roomLength};
    wall.position = (Vector3){-(float)roomWidth / 2.0f, 1.5f, 0.0f};
    level.addWall(wall);


    // Set the starting position so that it's not in a wall and dont use random either
    level.startPosition = (Vector3){0.0f, 1.0f, 0.0f};

    // Randomly add between 1 and 5 enemies
    for (int i = 0; i < GetRandomValue(1, 5); i++) {
        enemy.setPosition((Vector3){(float)GetRandomValue(-10, 10), 1.0f, (float)GetRandomValue(-10, 10)});
        enemy.setTarget((Vector3){(float)GetRandomValue(-10, 10), 1.0f, (float)GetRandomValue(-10, 10)});
        enemy.setSize((float)GetRandomValue(1, 4));
        enemy.setMaxHealth((int)enemy.getSize() * 10);
        enemy.setHealth(enemy.getMaxHealth());
        enemy.setName("Enemy");
        enemy.setDamage(3);
        level.addEnemy(enemy);
    }

    // Randomly select the model of the item from the following list :
    std::vector<std::string> modelList= {"iron.glb", "gold.glb", "emerald.glb", "diamond_apple.glb" };
    std::string model;

    // Randomly add between 1 and 3 items
    for (int i = 0; i < GetRandomValue(1, 3); i++) {
        std::string model = "assets/models/" + modelList[GetRandomValue(0, modelList.size() - 1)];
        item.setModel(model.c_str());
        item.setPosition((Vector3){(float)GetRandomValue(-10, 10), 1.0f, (float)GetRandomValue(-10, 10)});
        item.setSize(0.4f);
        item.setHealth(GetRandomValue(5, 20));
        item.setSpeed(GetRandomValue(0.05f, 0.1f));
        level.addItem(item);
    }

    level.animateItems();

    return level;
}