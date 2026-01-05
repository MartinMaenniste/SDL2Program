#include "Texture.h"

class Tile
{
public:
    Tile();
    void render(SDL_Renderer* renderer, SDL_Rect& cameraRect, std::unique_ptr<Texture>& stylesheetTexture, int& scale);
    void setValues(const int stylesheetX, const int stylesheetY, const int sideLength, const bool canWalkthrough, const int posX, const int posY, const int scale);

    bool getWalkThrough();
    SDL_Rect getHitbox();
    
private:
    SDL_Rect mStylesheetRect;
    SDL_Rect mHitbox;
    bool mCanWalkThrough;
};