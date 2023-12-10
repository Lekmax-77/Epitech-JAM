/*
** EPITECH PROJECT, 2022
** GameJam2023-YingYang
** File description:
** Level.hpp
*/

#pragma once

#include "Enemies.hpp"
#include "Player.hpp"

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

        void addProp(Prop prop) { _props.push_back(prop); }
        void removeProp(int index) { _props.erase(_props.begin() + index); }
        std::vector<Prop> getProps() { return _props; }
        void drawProps();

        bool checkCollisions(Player player);
        int checkHit(Player player);

        bool checkPropCollisions(Player player);

        Vector3 startPosition;
        Vector3 endPosition;

    private:
        int _id;
        std::vector<Enemy> _enemies;
        std::vector<Wall> _walls;
        std::vector<Prop> _props;
};

Level generateRoom(void);