/*
** EPITECH PROJECT, 2022
** GameJam2023-YingYang
** File description:
** Enemies.cpp
*/

#include "Enemies.hpp"
#include <cstddef>

Enemy::Enemy()
{
    _position = {0, 1.0f, 0};
    _target = {0, 0, 0};
    _speed = 0.1f;
    _size = 1;
    _angle = 0;
    _distance = 0;
    _distanceToTarget = 0;
    _maxHealth = 10;
    _health = 10;
    _name = "Undefined";
    _damage = 3;
}

Enemy::~Enemy()
{
}

void Enemy::update(std::vector<Wall> walls)
{
    _distanceToTarget = Vector3Distance(_position, _target);
    _angle = atan2(_target.x - _position.x, _target.z - _position.z);
    if (_distanceToTarget > 1.0f && _distanceToTarget < 20.0f) {
        // Move towards the target and avoid walls
        _position.x += sin(_angle) * _speed;
        _position.z += cos(_angle) * _speed;
        for (size_t i = 0; i < walls.size(); i++) {
            if (CheckCollisionBoxes((BoundingBox){(Vector3){_position.x - _size / 2, _position.y - _size / 2, _position.z - _size / 2}, (Vector3){_position.x + _size / 2, _position.y + _size / 2, _position.z + _size / 2}},
                                    (BoundingBox){(Vector3){walls[i].position.x - walls[i].size.x / 2, walls[i].position.y - walls[i].size.y / 2, walls[i].position.z - walls[i].size.z / 2}, (Vector3){walls[i].position.x + walls[i].size.x / 2, walls[i].position.y + walls[i].size.y / 2, walls[i].position.z + walls[i].size.z / 2}})) {
                _position.x -= sin(_angle) * _speed;
                _position.z -= cos(_angle) * _speed;
            }
        }
    }
}

void Enemy::takeDamage(int damage, float knockback)
{
    _health -= damage;
    // Take knockback
    float n_knockback = knockback / _size - 0.2;
    _position.x -= sin(_angle) * n_knockback;
}

void Enemy::drawUI(Camera camera)
{
    std::string uistring = _name + " " + std::to_string(_health) + "/" +
        std::to_string(_maxHealth);
    Vector2 healthScreenPosition = GetWorldToScreen(
        (Vector3){
            static_cast<float>(_position.x + uistring.length() * 0.2),
            _position.y + _size,
            _position.z
        },
        camera
    );

    DrawText(
        uistring.c_str(),
        healthScreenPosition.x,
        healthScreenPosition.y,
        25,
        RED
    );
}

void Enemy::drawModel()
{
    if (_health > 0) {
        DrawCube(_position, _size, _size, _size, DARKGRAY);
        DrawCubeWires(_position, _size, _size, _size, GRAY);
    }
}
