/*
** EPITECH PROJECT, 2022
** La Game jam ouais ouais
** File description:
** render.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#define EXIT_ERROR 84

class Wall {
    public:
        Wall(Vector3 position, Vector3 size) : position(position), size(size) {}
        ~Wall() = default;

        Vector3 position;
        Vector3 size;
};

class Prop {
    public:
        Prop(Vector3 position, Vector3 scale, Model model) : position(position), scale(scale), model(model) {}
        ~Prop() = default;

        Vector3 position;
        Vector3 rotation_angle = (Vector3){0, 0, 0};
        int rotation = 0;
        Vector3 scale;
        Model model;
};

struct Boxes {
    BoundingBox blackBox;
    BoundingBox redBox;
    BoundingBox blueBox;
    BoundingBox yellowBox;
    BoundingBox brownBox;
};
