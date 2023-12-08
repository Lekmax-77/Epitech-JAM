/*
** EPITECH PROJECT, 2022
** GameJam2023-YingYang
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include <thread>

Player::Player()
{
    _position = {0, 1.0f, 0};
    _speed = 0.2f;
    _angle = 0;
    _maxCorruption = 100;
    _corruption = 0;
    _color = (Color){255, 255, 255, 255};
    _isInvincible = false;

    _damage = 5;
    _knockback = 0.7f;
}

Player::~Player()
{
}

void Player::update()
{
    if (IsKeyDown(KEY_W)) {
        _position.z += _speed / 2;
        _position.x += _speed / 2;
    }
    if (IsKeyDown(KEY_S)) {
        _position.z -= _speed / 2;
        _position.x -= _speed / 2;
    }
    if (IsKeyDown(KEY_A)) {
        _position.z -= _speed / 2;
        _position.x += _speed / 2;
    }
    if (IsKeyDown(KEY_D)) {
        _position.z += _speed / 2;
        _position.x -= _speed / 2;
    }

    if (_corruption >= _maxCorruption) {
        _corruption = _maxCorruption;
        // TODO: Game over
    }

}

std::vector<Enemy> Player::attack(std::vector<Enemy> enemies)
{
    if (IsCursorOnScreen()) {
        Vector2 mousePosition = GetMousePosition();
        Vector2 screenCenter = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
        Vector2 direction = {mousePosition.x - screenCenter.x, mousePosition.y - screenCenter.y};
        float angle = atan2(direction.y, direction.x);
        // offset the angle a bit by 40 degrees
        angle += 40 * PI / 180;
        Vector3 attackPosition = {_position.x - sin(angle) * 2, _position.y, _position.z + cos(angle) * 2};
        DrawLine3D(_position, attackPosition, RED);
        DrawCube(attackPosition, 0.5, 0.5, 0.5, RED);
        for (int i = 0; i < enemies.size(); i++) {
            if (CheckCollisionBoxes((BoundingBox){(Vector3){attackPosition.x - 0.5f, attackPosition.y - 0.5f, attackPosition.z - 0.5f}, (Vector3){attackPosition.x + 0.5f, attackPosition.y + 0.5f, attackPosition.z + 0.5f}},
                                    (BoundingBox){(Vector3){enemies[i].getPosition().x - enemies[i].getSize() / 2, enemies[i].getPosition().y - enemies[i].getSize() / 2, enemies[i].getPosition().z - enemies[i].getSize() / 2}, (Vector3){enemies[i].getPosition().x + enemies[i].getSize() / 2, enemies[i].getPosition().y + enemies[i].getSize() / 2, enemies[i].getPosition().z + enemies[i].getSize() / 2}}
                                    )) {
                enemies[i].takeDamage(_damage, _knockback);
            }
        }
    }
    return enemies;
}

void Player::pickUpItem(Item item)
{
    std::cout << "Picked up item" << std::endl;
    _damage += item.getDamage();
    //_knockback += item.getKnockback();
    heal(item.getHealth());
    _speed += item.getSpeed();
}

void Player::drawUI(Camera camera)
{
    int x = 20;
    int y = 80;
    int width = _maxCorruption * 2;
    int height = 40;

    int width2 = _corruption * 2;

    DrawText("Corruption", 20, 20, 40, BLACK);
    // Draw the corruption bar
    DrawRectangle(x - 3, y - 3, width + 6, height + 6, DARKGRAY);
    DrawRectangle(x, y, width, height, WHITE);
    DrawRectangle(x, y, width2, height, BLACK);

    // Draw the speed, damage and knockback
    DrawText("Speed", 20, 140, 40, DARKGRAY);
    DrawText(std::to_string(_speed).c_str(), 20, 180, 40, DARKGRAY);
    DrawText("Damage", 20, 240, 40, DARKGRAY);
    DrawText(std::to_string(_damage).c_str(), 20, 280, 40, DARKGRAY);
    DrawText("Knockback", 20, 340, 40, DARKGRAY);
    DrawText(std::to_string(_knockback).c_str(), 20, 380, 40, DARKGRAY);
}

void Player::drawModel()
{
    // Temporary : Draw a cube for the player
    // The more closer the the _maxCorruption, the darker the color
    unsigned char r = (_isInvincible) ? 255 : 255 - _corruption * 2.55;
    unsigned char g = (_isInvincible) ?  50 : 255 - _corruption * 2.55;
    unsigned char b = (_isInvincible) ?  50 : 255 - _corruption * 2.55;
    _color = (Color){r, g, b, _alpha};

    DrawCube(_position, 1, 1, 1, _color);
    DrawCubeWires(_position, 1, 1, 1, BLACK);
}

void Player::takeDamage(int damage)
{
    if (damage <= 0)
        return;
    if (!_isInvincible) {
        _isInvincible = true;
        std::thread t1([this]() {
            for (int i = 0; i < 5; i++) {
                _alpha = 150;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                _alpha = 255;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
            _isInvincible = false;
            _alpha = 255;
        });
        t1.detach();
        if (_corruption + damage > _maxCorruption)
            _corruption = 100;
        else {
            _corruption += damage;
        }
    }
}

void Player::heal(int damage)
{
    if (_corruption - damage < 0)
        _corruption = 0;
    else
        _corruption -= damage;
}
