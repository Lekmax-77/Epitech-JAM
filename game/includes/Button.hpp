/*
** EPITECH PROJECT, 2023
** yin-yang [SSH: mac-os]
** File description:
** Button
*/

#pragma once

#include "raylib.h"
#include <string>

class Button {
public:
    Button(
        const std::string &text,
        Vector2 position,
        Vector2 size,
        Color color_pressed,
        Color color_release,
        Color text_color,
        int font_size
    );
    ~Button();

    void draw();

    Vector2 position;
    Vector2 size;
    Color color_pressed;
    Color color_release;
    Color text_color;
    int font_size;
    bool is_pressed;
private:
    std::string _text;
    Texture2D _text_texture;
    Texture2D _background_texture_pressed;
    Texture2D _background_texture_released;
};
