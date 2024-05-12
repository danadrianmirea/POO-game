#include "../include/spritesheet.hpp"
#include <iostream>

Spritesheet::Spritesheet(char const *path, int row, int column, SDL_Renderer *renderer)
{
    m_spritesheet_image = load_bmp(path);
    m_spritesheet_image_texture = SDL_CreateTextureFromSurface(renderer, m_spritesheet_image);

    m_clip.w = m_spritesheet_image->w / column;
    m_clip.h = m_spritesheet_image->h / row;
    // std::cerr << m_clip.w << " " << m_clip.h << std::endl;
    SDL_FreeSurface(m_spritesheet_image);
    flip = SDL_FLIP_NONE;
}

Spritesheet::~Spritesheet()
{
    // SDL_FreeSurface(m_spritesheet_image);
    SDL_DestroyTexture(m_spritesheet_image_texture);
}

void Spritesheet::select_sprite(int x, int y)
{
    m_clip.x = x * m_clip.w;
    m_clip.y = y * m_clip.h;
}

void Spritesheet::draw_selected_sprite(SDL_Renderer *renderer, SDL_Rect *position)
{
    
    SDL_RenderCopyEx(renderer, m_spritesheet_image_texture, &m_clip, position, 0, nullptr, flip);
    // SDL_BlitSurface(m_spritesheet_image, &m_clip, window_surface, position);
}


