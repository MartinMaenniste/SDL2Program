#include "GlobalFunctions.h"
class Texture;

class Interactable
{
public:
    Interactable();
    Interactable(const int x, const int y);
    ~Interactable();

    bool init(SDL_Renderer* renderer, const int x, const int y, const int* logLevel, int* messageDepth, const bool canWalkThrough = false);
    void update(SDL_Rect playerHitbox);
    void render(SDL_Renderer* renderer, SDL_Rect& camera);

    bool getCanWalkThrough();
    SDL_Rect getHitbox();

private:
    SDL_Rect mSolidHitbox;
    SDL_Rect mFullHitbox;

    std::unique_ptr<Texture> mTextureSheet;
    SDL_Rect mSheetRect;

    const char* mPathToTextureSheet = "./assets/Interactables.png";

    bool mCanWalkThrough;
    bool mRenderTransparent;

    bool loadTexture(SDL_Renderer* renderer, const int* logLevel, int* messageDepth);
};