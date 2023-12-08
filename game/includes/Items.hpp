/*
** EPITECH PROJECT, 2022
** GameJam2023-YingYang
** File description:
** Items.hpp
*/

#pragma once

#include "render.hpp"

class Item {
    public:
        Item();
        ~Item();

        void setModel(const char *path) { _model = LoadModel(path); }

        void drawModel();
        void animate();

        Vector3 getPosition() { return _position; }
        void setPosition(Vector3 position) { _position = position; }

        void setSize(float size) {
            _size = size;
            _scale = {_size, _size, _size};
        }
        float getSize() { return _size * 1.5; }

        float getSpeed() { return _speed; }
        void setSpeed(float speed) { _speed = speed; }

        int getHealth() { return _health; }
        void setHealth(int health) { _health = health; }

        int getDamage() { return _damage; }
        void setDamage(int damage) { _damage = damage; }

        int getKnockback() { return _knockback; }
        void setKnockback(int knockback) { _knockback = knockback; }

    private:
        Model _model;
        Texture2D _texture;

        Vector3 _position;
        Vector3 _rotation;
        float _size;
        Vector3 _scale;
        float _angle_rotation;

        float _speed;
        int _health;
        int _damage;
        int _knockback;
};