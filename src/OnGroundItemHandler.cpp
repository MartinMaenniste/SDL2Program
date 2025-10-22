#include "OnGroundItemHandler.h"
#include "Player.h"
#include "Item.h"

OnGroundItemHandler::OnGroundItemHandler()
{
}
OnGroundItemHandler::~OnGroundItemHandler()
{
}

bool OnGroundItemHandler::addNewItemOnGround(const int *logLevel, int *messageDepth, SDL_Renderer *renderer, const int x, const int y)
{
    std::unique_ptr<Item> item = std::make_unique<Item>();
    if (!item->init(renderer, logLevel, messageDepth, x, y, 16, 16, 0, 0, 1))
        return false;
    mOnGroundItems.push_back(std::move(item));

    return true;
}
//              Take ownership of item unique pointer. Remove item that uses this gives an rvalue!
void OnGroundItemHandler::addItemOnGround(std::unique_ptr<Item> item, const int x, const int y)
{
    item->setX(x);
    item->setY(y);
    mOnGroundItems.push_back(std::move(item)); // Give ownership from function to the vector.
}
void OnGroundItemHandler::render(SDL_Renderer *renderer, SDL_Rect &camera)
{
    for (auto iter = std::begin(mOnGroundItems); iter != std::end(mOnGroundItems); ++iter)
    {
        (*iter)->renderOnGround(renderer, camera);
    }
}
void OnGroundItemHandler::handleEvent(const SDL_Event &e, Player &player, const SDL_Rect &camera)
{
    if (e.type != SDL_MOUSEBUTTONDOWN)
    {
        return;
    }
    int mouseX = 0, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);

    mouseX += camera.x; // Correct for camera - user clicked at (mouseX, mouseY), from top left, which is (camera.x, camera.y)
    mouseY += camera.y;

    for (auto iter = std::begin(mOnGroundItems); iter != std::end(mOnGroundItems); iter++)
    {
        if (!Global::isInRect(mouseX, mouseY, (*iter)->getHitBox()))
            continue;

        moveItemToInventory(std::distance(std::begin(mOnGroundItems), iter), player);
        break; // movetoinv removed the element from vector. We don't want to break things, just break out of the current loop. User can only click on one item at a time anyways!
    }
}

void OnGroundItemHandler::moveItemToInventory(const int index, Player &player)
{
    player.addItemToInventory(mOnGroundItems[index]);

    mOnGroundItems[index] = nullptr;
    mOnGroundItems.erase(std::begin(mOnGroundItems) + index);
}