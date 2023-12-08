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

struct Wall {
    Vector3 position;
    Vector3 size;
};