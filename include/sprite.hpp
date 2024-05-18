#ifndef SPRITE_HPP
#define SPRITE_HPP
#include <SDL2/SDL.h>
#include "spritesheet.hpp"
#include "utilities.hpp"
#include "effect.hpp"

class Sprite
{
public:

    Sprite(const char* path_to_sprite, float ratio_);
    ~Sprite();

    void update();
    void draw();
    void move(double x1, double y1);

    Direction m_direction;
    Direction m_direction_prev;
    std::vector<SDL_Rect> &get_boxes();
    void move_boxes();
    void meleeAttack();
    int id;
    double x;
    double y;
    void change_skin(const char* path);

protected:
    
    Spritesheet m_spritesheet;
    Effect *effect;
    int m_spritesheet_column;
    std::vector<SDL_Rect> bb; // boundings boxes
    std::vector<std::vector<int>> bb_off; // boundings boxes offset
    std::vector<SDL_Rect> bb_att; // boundings boxes
    std::vector<std::vector<int>> bb_att_off; // boundings boxes offset
    SDL_Rect m_position;
    Direction att_dir;
    bool hit;
    bool block;
    int strength;
    bool alive;
    SDL_Renderer *renderer;
    float ratio;
};
#endif