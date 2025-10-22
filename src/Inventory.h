#pragma once

#include "GlobalFunctions.h"
class Item;
class OnGroundItemHandler;
class Texture;

class Inventory
{
public:
    Inventory();
    ~Inventory();

    bool init(SDL_Renderer *renderer, const int windowWidth, const int windowHeight, const int *logLevel, int *messageDepth, int maxSlots = -1); // Default to inv full of slots.
    void render(SDL_Renderer *renderer);
    void close(const int *logLevel, int *messageDepth);
    void handleEvent(const SDL_Event &e, std::unique_ptr<OnGroundItemHandler> &onGroundItems, const SDL_Rect &playerHitbox);

    bool canPickUp();
    void addItem(std::unique_ptr<Item> &item);

private:
    SDL_Rect mHitbox; // To handle mouse action.
    const char *mImagePath = "./assets/Inventory.png";
    std::unique_ptr<Texture> mTexture;
    const int mSlotSidelength = 20;
    const int mPadding = 2;
    int mSlotsPerRow;
    int mMaxSlots;
    std::vector<std::unique_ptr<Item>> mInvSlots; // Slot vector that holds items!!

    bool loadTexture(SDL_Renderer *renderer, const int *logLevel, int *messageDepth);
    void renderItems(SDL_Renderer *renderer);
    std::unique_ptr<Item> removeItem(int slot);
    int groundItemX(const SDL_Rect &playerHitbox);
    int groundItemY(const SDL_Rect &playerHitbox);
    int getFirstFreeInvSlot();
    void setSlotXYFromIndex(const int slot, int &x, int &y);
};
