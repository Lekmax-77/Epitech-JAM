/*
** EPITECH PROJECT, 2023
** yin-yang
** File description:
** Main Menu class
*/

#pragma once

#include "Button.hpp"

#include "raylib.h"

#define BACKGROUND_IMAGE_PATH "assets/background.png"
#define COEF 0.01

class Menu {
    public:
        Menu();
        ~Menu();

        void loop();
    private:
        Button _play_button;
        Button _quit_button;
        Texture2D _background_texture;
        Texture2D _jo_texture;
};

