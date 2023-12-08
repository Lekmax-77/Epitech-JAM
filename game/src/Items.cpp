/*
** EPITECH PROJECT, 2022
** GameJam2023-YingYang
** File description:
** Items.cpp
*/

#include "Items.hpp"
#include <thread>
#include <future>

Item::Item()
{
    _model = LoadModel("assets/models/iron.glb");
    //_texture = LoadTexture("assets/models/Items/healthpack.png");
    _position = {0, 0, 0};
    _rotation = {0, 1, 0};
    _size = 1;
    _scale = {_size, _size, _size};
    _speed = 0;
    _health = 0;
    _damage = 0;
    _angle_rotation = 0.0f;
}

Item::~Item()
{
}

void Item::animate()
{
    std::thread t([this]() {
        while (true) {
            if (_angle_rotation >= 360.0f)
                _angle_rotation = 0.0f;
            _angle_rotation += 1.0f;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    });
    t.detach();
}

void Item::drawModel()
{
    DrawModelEx(_model, _position, _rotation, _angle_rotation, _scale, WHITE);
}