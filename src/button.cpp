#include "../include/button.hpp"
#include "../include/game.hpp"
#include "../include/utilities.hpp"

Button::Button(int x, int y, int width, int height,
               const vector<string> &imagePaths, 
               const string &fontPath, 
               const string &name, 
               GameStatus a): 
               m_rect({x, y, width, height}), 
               m_renderer(Game::appWindow->renderer),
               m_currentTextureIndex(0), 
               m_isPressed(false)
{
    action = a;
    for (const auto &imagePath : imagePaths)
    {
        SDL_Surface *surface = load_png(imagePath.c_str());
        SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        SDL_FreeSurface(surface);
        m_textures.push_back(texture);
    }

    m_font = TTF_OpenFont(fontPath.c_str(), 24);
    if (!m_font)
    {
        throw std::runtime_error("Failed to load font: " + fontPath);
    }

    SDL_Color textColor = {255, 255, 255}; // White text color
    SDL_Surface *textSurface = TTF_RenderText_Solid(m_font, name.c_str(), textColor);
    m_textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    SDL_FreeSurface(textSurface);
}

Button::~Button()
{
    for (auto& texture : m_textures)
    {
        SDL_DestroyTexture(texture);
    }
    m_textures.clear(); // Clear the vector after destroying the textures
    SDL_DestroyTexture(m_textTexture);
    m_textTexture = NULL;
    TTF_CloseFont(m_font);
}


void Button::handleEvent(const SDL_Event &event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseX >= m_rect.x && mouseX <= m_rect.x + m_rect.w &&
            mouseY >= m_rect.y && mouseY <= m_rect.y + m_rect.h)
        {
            if(m_currentTextureIndex != 2){
                m_currentTextureIndex = 1;
            }
        }
        else
        {
            m_currentTextureIndex = 0;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseX >= m_rect.x && mouseX <= m_rect.x + m_rect.w &&
            mouseY >= m_rect.y && mouseY <= m_rect.y + m_rect.h)
        {
            m_currentTextureIndex = 2;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if (mouseX >= m_rect.x && mouseX <= m_rect.x + m_rect.w &&
            mouseY >= m_rect.y && mouseY <= m_rect.y + m_rect.h)
        {
            m_currentTextureIndex = 1;
            m_isPressed = !m_isPressed;
            // Play the sound effect when the button is pressed
            if (m_soundEffect && !m_soundId.empty()) {
                m_soundEffect->playSound(m_soundId);
            }
            Game::gameStatus = action;

            
            
        }
    }
}

void Button::render()
{
    SDL_RenderCopy(m_renderer, m_textures[m_currentTextureIndex], NULL, &m_rect);

    // Calculate text position
    int textX, textY, textW, textH;
    SDL_QueryTexture(m_textTexture, NULL, NULL, &textW, &textH);
    if (m_currentTextureIndex == 2)
    {
        textY = m_rect.y + (m_rect.h - textH) / 2 + (m_rect.h / 8);
    }
    else
    {
        textY = m_rect.y + (m_rect.h - textH) / 2;
    }
    textX = m_rect.x + (m_rect.w - textW) / 2;
    SDL_Rect textRect = {textX, textY, textW, textH};

    SDL_RenderCopy(m_renderer, m_textTexture, NULL, &textRect);
}

bool Button::isPressed() const
{
    // std::cout << "isPresse = " << m_isPressed << std::endl;
    return m_isPressed;
    
}

void Button::setSoundEffect(SoundEffect* soundEffect, const std::string& soundId) {
    m_soundEffect = soundEffect;
    m_soundId = soundId;
}