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
    for (size_t i = 0; i < _walls.size(); i++)
        DrawCubeV(_walls[i].position, _walls[i].size, BLACK);
}

void Level::animateItems()
{
    for (size_t i = 0; i < _items.size(); i++)
        _items[i].animate();
}

void Level::drawItems()
{
    for (size_t i = 0; i < _items.size(); i++)
        _items[i].drawModel();
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

void Level::checkItemCollisions(Player *player)
{
    for (size_t i = 0; i < _items.size(); i++) {
        if (CheckCollisionBoxes((BoundingBox){(Vector3){player->getPosition().x - 0.5f, player->getPosition().y - 0.5f, player->getPosition().z - 0.5f}, (Vector3){player->getPosition().x + 0.5f, player->getPosition().y + 0.5f, player->getPosition().z + 0.5f}},
                                (BoundingBox){(Vector3){_items[i].getPosition().x - _items[i].getSize() / 2, _items[i].getPosition().y - _items[i].getSize() / 2, _items[i].getPosition().z - _items[i].getSize() / 2}, (Vector3){_items[i].getPosition().x + _items[i].getSize() / 2, _items[i].getPosition().y + _items[i].getSize() / 2, _items[i].getPosition().z + _items[i].getSize() / 2}}
                                )) {
            player->pickUpItem(_items[i]);
            _items.erase(_items.begin() + i);
        }
    }
}
