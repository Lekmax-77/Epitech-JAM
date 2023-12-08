/*
** EPITECH PROJECT, 2022
** GameJam2023-YingYang
** File description:
** Enemies.hpp
*/

#pragma once

#include "render.hpp"

class Enemy {
    public:
        Enemy();
        ~Enemy();

        void update(std::vector<Wall> walls);
        void drawModel();
        void drawUI(Camera camera);

        Vector3 getPosition() const { return _position; }
        void setPosition(Vector3 position) { _position = position; }

        Vector3 getTarget() const { return _target; }
        void setTarget(Vector3 target) { _target = target; }

        float getSpeed() const { return _speed; }
        void setSpeed(float speed) { _speed = speed; }

        float getSize() const { return _size; }
        void setSize(float size) { _size = size; }

        float getAngle() const { return _angle; }
        void setAngle(float angle) { _angle = angle; }

        float getDistance() const { return _distance; }
        void setDistance(float distance) { _distance = distance; }

        float getDistanceToTarget() const { return _distanceToTarget; }
        void setDistanceToTarget(float distanceToTarget) { _distanceToTarget = distanceToTarget; }

        int getHealth() const { return _health; }
        void setHealth(int health) { if (health > _maxHealth) _health = _maxHealth; else _health = health;}
        void takeDamage(int damage, float knockback);

        int getMaxHealth() const { return _maxHealth; }
        void setMaxHealth(int maxHealth) { _maxHealth = maxHealth; }

        int getDamage() const { return _damage; }
        void setDamage(int damage) { _damage = damage; }

        std::string getName() const { return _name; }
        void setName(std::string name) { _name = name; }

    private:
        Vector3 _position;
        Vector3 _target;

        float _speed;
        float _size;
        float _angle;
        float _distance;
        float _distanceToTarget;

        std::string _name;
        int _maxHealth;
        int _health;
        int _damage;
};
