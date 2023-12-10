/*
** EPITECH PROJECT, 2023
** yin-yang
** File description:
** Main Menu class
*/

#include "Menu.hpp"
#include "raylib.h"

using std::string;

Menu::Menu()
    : _play_button(
          string("Play"),
          {736, 100},
          {128, 64},
          RED,
          DARKGRAY,
          WHITE,
          20),
      _quit_button(
          string("Quit"),
          {736, 300},
          {128, 64},
          RED,
          DARKGRAY,
          WHITE,
          20),
      _background_texture(LoadTexture(BACKGROUND_IMAGE_PATH)),
      _jo_texture(LoadTexture("assets/jo.png"))
{
}

Menu::~Menu()
{
    UnloadTexture(_background_texture);
}

void Menu::loop()
{
    while (!WindowShouldClose())
    {
        // clear black
        ClearBackground(BLACK);
        Vector2 jo_pos = {
            static_cast<float>(GetMouseX() * COEF + 355),
            static_cast<float>(GetMouseY() * COEF + 200)};
        Vector2 background_position = {
            static_cast<float>(GetMouseX() * COEF - 25),
            static_cast<float>(GetMouseY() * COEF - 25)};
        Vector2 play_button_position = {
            static_cast<float>(720 + GetMouseX() * COEF * 2),
            static_cast<float>(100 + GetMouseY() * COEF * 2)};
        Vector2 quit_button_position = {
            static_cast<float>(720 + GetMouseX() * COEF * 2),
            static_cast<float>(300 + GetMouseY() * COEF * 2)};

        if (IsKeyPressed(KEY_ESCAPE) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                                         CheckCollisionPointRec(
                                             GetMousePosition(),
                                             {_quit_button.position.x - _quit_button.size.x / 2,
                                              _quit_button.position.y - _quit_button.size.y / 2,
                                              _quit_button.size.x,
                                              _quit_button.size.y})))
            break;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(
                GetMousePosition(),
                {_play_button.position.x - _play_button.size.x / 2,
                 _play_button.position.y - _play_button.size.y / 2,
                 _play_button.size.x,
                 _play_button.size.y}))
            return;
        _play_button.position = play_button_position;
        _quit_button.position = quit_button_position;

        BeginDrawing();

        DrawTextureEx(_background_texture, background_position, 0, 0.35, WHITE);

        DrawTextureEx(_jo_texture, jo_pos, -17, 1, WHITE);
        _play_button.draw();
        _quit_button.draw();
        EndDrawing();
    }
    exit(0);
}
