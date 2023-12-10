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
    _hp = 0;
}

Player::~Player()
{
}

void Player::update()
{
    if (IsKeyDown(KEY_W)) {
        _position.x -= _speed / 2;
    }
    if (IsKeyDown(KEY_S)) {
        _position.x += _speed / 2;
    }
    if (IsKeyDown(KEY_A)) {
        _position.z += _speed / 2;
    }
    if (IsKeyDown(KEY_D)) {
        _position.z -= _speed / 2;
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

void Player::drawUI(Camera camera)
{
    int x = 30;
    int y = 30;

    // Draw the player's health bar
    DrawRectangle(x, y, 200, 20, WHITE);
    DrawRectangle(x, y, _hp * 2, 20, RED);
    DrawRectangleLines(x, y, 200, 20, BLACK);

    // Draw the player's food bar
    DrawRectangle(x, y + 50, 200, 20, WHITE);
    DrawRectangle(x, y + 50, _food * 2, 20, GREEN);
    DrawRectangleLines(x, y + 50, 200, 20, BLACK);

    // Draw the player's water bar
    DrawRectangle(x, y + 100, 200, 20, WHITE);
    DrawRectangle(x, y + 100, _water * 2, 20, BLUE);
    DrawRectangleLines(x, y + 100, 200, 20, BLACK);

    // Draw the player's stress bar
    DrawRectangle(x, y + 150, 200, 20, WHITE);
    DrawRectangle(x, y + 150, _stress * 2, 20, YELLOW);
    DrawRectangleLines(x, y + 150, 200, 20, BLACK);

    // Draw the player's toilet bar
    DrawRectangle(x, y + 200, 200, 20, WHITE);
    DrawRectangle(x, y + 200, _toilet * 2, 20, BROWN);
    DrawRectangleLines(x, y + 200, 200, 20, BLACK);

    // Draw Text
    DrawText("Health", x, y - 20, 20, BLACK);
    DrawText("Food", x, y + 30, 20, BLACK);
    DrawText("Water", x, y + 80, 20, BLACK);
    DrawText("Stress", x, y + 130, 20, BLACK);
    DrawText("Toilet", x, y + 180, 20, BLACK);
}

void Player::drawModel()
{
    // Temporary : Draw a cube for the player
    // The more closer the the _maxHp, the darker the color
    unsigned char r = (_isInvincible) ? 255 : 255 - _hp * 2.55;
    unsigned char g = (_isInvincible) ?  50 : 255 - _hp * 2.55;
    unsigned char b = (_isInvincible) ?  50 : 255 - _hp * 2.55;
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
        if (_hp + damage > _maxHp)
            _hp = 100;
        else {
            _hp += damage;
        }
    }
}

void Player::heal(int damage)
{
    if (_hp - damage < 0)
        _hp = 0;
    else
        _hp -= damage;
}
