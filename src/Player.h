#include "Texture.h"
#include "Window.h"

class Player
{
public:
    Player();
    Player(int startX, int startY, int width, int height);
    ~Player();

    bool loadAssets(SDL_Renderer *renderer, int *logLevel, int *messageDepth);
    void handleEvents(SDL_Event &event);
    void render(std::unique_ptr<Window> &window);
    void close(int *logLevel, int *messageDepth);
    int getXPosition();
    int getYPosition();
    void setXPosition(int xPosition);
    void setYPosition(int yPosition);

private:
    std::unique_ptr<Texture> mTexture;
    const char *mImagePath = "./assets/player.png";
    int mPosX, mPosY;
    int mVelX, mVelY;
    int mWidth, mHeight;
    int mPlayerSpeed;

    void movePlayerSprite(int windowWidth, int windowHeight);
};