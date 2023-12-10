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

bool Level::checkPropCollisions(Player player)
{
    // for (size_t i = 0; i < _props.size(); i++) {
    //     if (CheckCollisionBoxes((BoundingBox){(Vector3){player.getPosition().x - 0.5f, player.getPosition().y - 0.5f, player.getPosition().z - 0.5f}, (Vector3){player.getPosition().x + 0.5f, player.getPosition().y + 0.5f, player.getPosition().z + 0.5f}},
    //                             (BoundingBox){(Vector3){_props[i].position.x - _props[i].scale.x / 2, _props[i].position.y - _props[i].scale.y / 2, _props[i].position.z - _props[i].scale.z / 2}, (Vector3){_props[i].position.x + _props[i].scale.x / 2, _props[i].position.y + _props[i].scale.y / 2, _props[i].position.z + _props[i].scale.z / 2}}
    //                             )) {
    //         return true;
    //     }
    // }
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

    level.addWall(Wall((Vector3){20.0f, 1.5f, 10.0f}, (Vector3){40.0f, 3.0f, 1.0f})); // Left Big
    level.addWall(Wall((Vector3){0.0f, 1.5f, 0.0f}, (Vector3){1.0f, 3.0f, 20.0f}));
    level.addWall(Wall((Vector3){40.0f, 1.5f, 0.0f}, (Vector3){1.0f, 3.0f, 20.0f}));

    level.addWall(Wall((Vector3){30.0f, 1.5f, -10.0f}, (Vector3){20.0f, 3.0f, 1.0f})); // Bottom Right
    level.addWall(Wall((Vector3){20.0f, 1.5f, -20.0f}, (Vector3){1.0f, 3.0f, 20.0f}));
    level.addWall(Wall((Vector3){0.0f, 1.5f, -20.0f}, (Vector3){1.0f, 3.0f, 20.0f}));

    level.addWall(Wall((Vector3){10.0f, 1.5f, -30.0f}, (Vector3){20.0f, 3.0f, 1.0f})); // Far Right

    // Props
    Model model = LoadModel("assets/models/Office Chair.glb");
    Prop prop1((Vector3){-3.0f, 0.0f, -3.0f}, (Vector3){150.0f, 150.0f, 150.0f}, model);
    prop1.rotation_angle = (Vector3){1, 0, 0};
    prop1.rotation = -90;
    level.addProp(prop1);

    Model coffe = LoadModel("assets/coffe_machine.glb");
    Prop coffe_prop((Vector3){2.0f, 2.0f, -8.0f}, (Vector3){1.0f, 1.0f, 1.0f}, coffe);

    // coffe_prop.rotation_angle = (Vector3){1, 0, 0};
    coffe_prop.rotation_angle = (Vector3){0, 1, 1};
    level.addProp(coffe_prop);

    Model model2 = LoadModel("assets/models/mess_office.glb");
    Prop prop2((Vector3){3.0f, 0.0f, 3.0f}, (Vector3){10.0f, 10.0f, 10.0f}, model2);
    level.addProp(prop2);

    return level;
}