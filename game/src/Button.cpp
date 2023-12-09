/*
** EPITECH PROJECT, 2023
** yin-yang [SSH: mac-os]
** File description:
** Button
*/

#include "Button.hpp"
#include "raylib.h"

using std::string;

Button::Button(
    const string &text,
    Vector2 position,
    Vector2 size,
    Color color_pressed,
    Color color_release,
    Color text_color,
    int font_size
)
    : position(position),
    size(size),
    color_pressed(color_pressed),
    color_release(color_release),
    text_color(text_color),
    font_size(font_size),
    is_pressed(false),
    _text(text)
{
    Image text_image = ImageText(_text.c_str(), font_size, text_color);
    Image background_image_pressed =
        GenImageColor(size.x, size.y, color_pressed);
    Image background_texture_released =
        GenImageColor(size.x, size.y, color_release);

    _text_texture = LoadTextureFromImage(text_image);
    _background_texture_pressed =
        LoadTextureFromImage(background_image_pressed);
    _background_texture_released =
        LoadTextureFromImage(background_texture_released);
}

Button::~Button()
{
    UnloadTexture(_text_texture);
    UnloadTexture(_background_texture_pressed);
    UnloadTexture(_background_texture_released);
}

void Button::draw()
{
    Vector2 text_position = {
        position.x - _text_texture.width / 2 + size.x / 2,
        position.y - _text_texture.height / 2 + size.y / 2
    };

    Vector2 background_position = {
        position.x - _background_texture_released.width / 2 + size.x / 2,
        position.y - _background_texture_released.height / 2 + size.y / 2
    };

    DrawTextureV(
        _background_texture_released,
        background_position,
        WHITE
    );
    DrawTextureV(_text_texture, text_position, WHITE);
}
