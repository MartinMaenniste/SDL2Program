#pragma once

#include "GlobalFunctions.h"
class Player;
class Item;

class OnGroundItemHandler
{
public:
    OnGroundItemHandler();
    ~OnGroundItemHandler();

    bool addNewItemOnGround(const int *logLevel, int *messageDepth, SDL_Renderer *renderer, const int x, const int y);
    //              Take ownership! removeitem passes rvalue.
    void addItemOnGround(std::unique_ptr<Item> item, int x, int y);
    void render(SDL_Renderer *renderer, SDL_Rect &camera);
    void handleEvent(const SDL_Event &e, Player &player, const SDL_Rect &camera);

private:
    std::vector<std::unique_ptr<Item>> mOnGroundItems;

    void moveItemToInventory(const int index, Player &player);
};