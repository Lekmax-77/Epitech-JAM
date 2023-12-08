/*
** EPITECH PROJECT, 2022
** GameJam2023-YingYang
** File description:
** Level.hpp
*/

#pragma once

#include "Enemies.hpp"
#include "Player.hpp"
#include "Items.hpp"

#include "render.hpp"
#include <cstddef>

class Level {
    public:
        Level();
        ~Level() = default;

        int getId() const { return _id; }
        void setId(int id) { _id = id; }

        void addEnemy(Enemy enemy) { _enemies.push_back(enemy); }
        void removeEnemy(int index) { _enemies.erase(_enemies.begin() + index); }

        std::vector<Enemy> getEnemies() { return _enemies; }
        void setEnemies(std::vector<Enemy> enemies) { _enemies = enemies; }
        void drawEnemies();
        void drawEnemiesUI(Camera camera);

        void setEnemiesTarget(Vector3 target) {
            for (size_t i = 0; i < _enemies.size(); i++) {
                _enemies[i].setTarget(target);
            }
        }

        void addWall(Wall wall) { _walls.push_back(wall); }
        void removeWall(int index) { _walls.erase(_walls.begin() + index); }
        std::vector<Wall> getWalls() { return _walls; }
        void drawWalls();

        void addItem(Item item) { _items.push_back(item); }
        void removeItem(int index) { _items.erase(_items.begin() + index); }
        std::vector<Item> getItems() { return _items; }
        void animateItems();
        void drawItems();

        bool checkCollisions(Player player);
        int checkHit(Player player);

        void checkItemCollisions(Player *player);

        Vector3 startPosition;
        Vector3 endPosition;

    private:
        int _id;
        std::vector<Enemy> _enemies;
        std::vector<Wall> _walls;
        std::vector<Item> _items;
};

Level proceduralGeometry(void);
