/*
** EPITECH PROJECT, 2022
** GameJam2023-YingYang
** File description:
** Level.cpp
*/

#include "Level.hpp"
#include <cstddef>

Level::Level()
{
    startPosition = {0, 1.0f, 0};
}

void Level::drawEnemies()
{
    for (size_t i = 0; i < _enemies.size(); i++) {
        if (_enemies[i].getHealth() <= 0) {
            _enemies.erase(_enemies.begin() + i);
            continue;
        }
        _enemies[i].update(_walls);
        _enemies[i].drawModel();
    }
}

void Level::drawEnemiesUI(Camera camera)
{
    for (size_t i = 0; i < _enemies.size(); i++)
        _enemies[i].drawUI(camera);
}

void Level::drawWalls()
{
    for (size_t i = 0; i < _walls.size(); i++) {
        DrawCubeV(_walls[i].position, _walls[i].size, GRAY);
        DrawCubeWiresV(_walls[i].position, _walls[i].size, BLACK);
    }
}

bool Level::checkCollisions(Player player)
{
    for (size_t i = 0; i < _walls.size(); i++) {
        if (CheckCollisionBoxes((BoundingBox){(Vector3){player.getPosition().x - 0.5f, player.getPosition().y - 0.5f, player.getPosition().z - 0.5f}, (Vector3){player.getPosition().x + 0.5f, player.getPosition().y + 0.5f, player.getPosition().z + 0.5f}},
                                (BoundingBox){(Vector3){_walls[i].position.x - _walls[i].size.x / 2, _walls[i].position.y - _walls[i].size.y / 2, _walls[i].position.z - _walls[i].size.z / 2}, (Vector3){_walls[i].position.x + _walls[i].size.x / 2, _walls[i].position.y + _walls[i].size.y / 2, _walls[i].position.z + _walls[i].size.z / 2}}
                                )) {
            return true;
        }
    }
    return false;
}

int Level::checkHit(Player player)
{
    for (size_t i = 0; i < _enemies.size(); i++) {
        if (CheckCollisionBoxes((BoundingBox){(Vector3){player.getPosition().x - 0.5f, player.getPosition().y - 0.5f, player.getPosition().z - 0.5f}, (Vector3){player.getPosition().x + 0.5f, player.getPosition().y + 0.5f, player.getPosition().z + 0.5f}},
                                (BoundingBox){(Vector3){_enemies[i].getPosition().x - _enemies[i].getSize() / 2, _enemies[i].getPosition().y - _enemies[i].getSize() / 2, _enemies[i].getPosition().z - _enemies[i].getSize() / 2}, (Vector3){_enemies[i].getPosition().x + _enemies[i].getSize() / 2, _enemies[i].getPosition().y + _enemies[i].getSize() / 2, _enemies[i].getPosition().z + _enemies[i].getSize() / 2}}
                                )) {
            return _enemies[i].getDamage();
        }
    }
    return -1;
}

void Level::drawProps()
{
    for (size_t i = 0; i < _props.size(); i++) {
        DrawModelEx(_props[i].model, _props[i].position, _props[i].rotation_angle, _props[i].rotation, _props[i].scale, WHITE);
    }
}

Level generateRoom(void)
{
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


    // Props
    Model model = LoadModel("assets/models/Office Chair.glb");
    Prop prop1((Vector3){-3.0f, 0.0f, -3.0f}, (Vector3){150.0f, 150.0f, 150.0f}, model);
    prop1.rotation_angle = (Vector3){1, 0, 0};
    prop1.rotation = -90;
    level.addProp(prop1);

    Model model2 = LoadModel("assets/models/mess_office.glb");
    Prop prop2((Vector3){3.0f, 0.0f, 3.0f}, (Vector3){10.0f, 10.0f, 10.0f}, model2);
    level.addProp(prop2);

    return level;
}