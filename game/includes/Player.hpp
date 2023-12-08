/*
** EPITECH PROJECT, 2022
** GameJam2023-YingYang
** File description:
** Player.hpp
*/

#pragma once

#include "render.hpp"
#include "Enemies.hpp"
#include "Items.hpp"

class Player {
public:
    Player();
    ~Player();

    void update();
    void drawModel();
    void drawUI(Camera camera);

    std::vector<Enemy> attack(std::vector<Enemy> enemies);

    Vector3 getPosition() const { return _position; }
    void setPosition(Vector3 position) { _position = position; }

    float getSpeed() const { return _speed; }
    void setSpeed(float speed) { _speed = speed; }

    float getAngle() const { return _angle; }
    void setAngle(float angle) { _angle = angle; }

    int getCorruption() const { return _corruption; }
    void setCorruption(int corruption) { _corruption = corruption; }

    int getMaxCorruption() const { return _maxCorruption; }
    void setMaxCorruption(int maxCorruption) { _maxCorruption = maxCorruption; }

    void takeDamage(int damage);
    void heal(int health);

    int getDamage() const { return _damage; }
    void setDamage(int damage) { _damage = damage; }

    float getKnockback() const { return _knockback; }
    void setKnockback(float knockback) { _knockback = knockback; }

    bool getIsInvincible() const { return _isInvincible; }

    void pickUpItem(Item item);

private:
    Vector3 _position;
    float _speed;
    float _angle;

    bool _isInvincible;

    Color _color;
    unsigned char _alpha;
    int _maxCorruption;
    int _corruption;
    int _damage;
    float _knockback;
};
