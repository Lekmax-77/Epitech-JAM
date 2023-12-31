/*
** EPITECH PROJECT, 2022
** GameJam2023-YingYang
** File description:
** Player.hpp
*/

#pragma once

#include "render.hpp"
#include "Enemies.hpp"

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

    int getHp() const { return _hp; }
    void setHp(int Hp) { _hp = Hp; }

    int getMaxHp() const { return _maxHp; }
    void setMaxHp(int maxHp) { _maxHp = maxHp; }

    void takeDamage(int damage);
    void heal(int health);

    int getDamage() const { return _damage; }
    void setDamage(int damage) { _damage = damage; }

    float getKnockback() const { return _knockback; }
    void setKnockback(float knockback) { _knockback = knockback; }

    bool getIsInvincible() const { return _isInvincible; }

    int getFood() const { return _food; }
    void setFood(int food) { _food = food; }

    int getWater() const { return _water; }
    void setWater(int water) { _water = water; }

    int getStress() const { return _stress; }
    void setStress(int stress) { _stress = stress; }

    int getToilet() const { return _toilet; }
    void setToilet(int toilet) {
        _toilet = toilet;
    }

    int getTick() const { return _tick; }
    void setTick(int tick) { _tick = tick; }

    BoundingBox getBoundingBox() const { return (BoundingBox){(Vector3){_position.x - 0.5f, _position.y - 0.5f, _position.z - 0.5f}, (Vector3){_position.x + 0.5f, _position.y + 0.5f, _position.z + 0.5f}}; }

private:
    Vector3 _position;
    float _speed;
    float _angle;

    bool _isInvincible;

    Color _color;
    unsigned char _alpha;
    int _maxHp;
    int _hp;
    int _damage;
    float _knockback;

    int _food;
    int _water;
    int _stress;
    int _toilet;
    int _tick;


};
