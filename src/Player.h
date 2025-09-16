#include "Texture.h"

class Player
{
public:
    Player();
    Player(int startX, int startY, int width, int height);
    ~Player();

    bool loadAssets(SDL_Renderer *renderer, int *logLevel, int *messageDepth);
    void close(int *logLevel, int *messageDepth);
    void render(SDL_Renderer *renderer);
    int getXPosition();
    int getYPosition();
    void setXPosition(int xPosition);
    void setYPosition(int yPosition);

private:
    std::unique_ptr<Texture> mTexture;
    const char *mImagePath = "./assets/player.png";
    int mPosX, mPosY;
    int mWidth, mHeight;
};