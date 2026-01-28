#include "Inventory.h"
#include "OnGroundItemHandler.h"
#include "Item.h"
#include "Texture.h"

Inventory::Inventory()
{
    mTexture = std::make_unique<Texture>();
    SDL_Rect mHitbox = {0, 0, 0, 0};
    int mSlotsPerRow = 0;
    int mMaxSlots = 0;
}
Inventory::~Inventory()
{
}
bool Inventory::init(SDL_Renderer *renderer, const int windowWidth, const int windowHeight, const int *logLevel, int *messageDepth, int maxSlots)
{
    mHitbox.w = 200;
    mHitbox.h = 250;
    mHitbox.x = windowWidth - mHitbox.w;
    mHitbox.y = windowHeight - mHitbox.h;

    mMaxSlots = maxSlots;
    mSlotsPerRow = mHitbox.w / mSlotSidelength;
    if (maxSlots == -1) // Fill entire inv with slots
        mMaxSlots = (mHitbox.h / mSlotSidelength) * mSlotsPerRow;

    // Initialise the slots as empty
    for (int i = 0; i < mMaxSlots; i++)
    {
        mInvSlots.push_back(nullptr);
    }

    return loadTexture(renderer, logLevel, messageDepth);
}
void Inventory::render(SDL_Renderer *renderer)
{
    mTexture->render(renderer, mHitbox.x, mHitbox.y);
    renderItems(renderer);
}
void Inventory::close(const int *logLevel, int *messageDepth)
{
    mTexture->close(logLevel, messageDepth);
}
void Inventory::handleEvent(const SDL_Event &e, std::unique_ptr<OnGroundItemHandler> &onGroundItems, const SDL_Rect &playerHitbox)
{
    if (e.type != SDL_MOUSEBUTTONDOWN)
    {
        return;
    }
    int mouseX = -1000, mouseY = -1000;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Check if in inv, then all slots.

    SDL_Rect slotRect = {mHitbox.x + mPadding, mHitbox.y + mPadding, mSlotSidelength, mSlotSidelength};
    for (auto iter = std::begin(mInvSlots); iter != std::end(mInvSlots); iter++)
    {
        if (Global::isInRect(mouseX, mouseY, slotRect))
        {
            int slotInx = std::distance(std::begin(mInvSlots), iter);

            // Removeitem returns an rvalue, addItemOnGround takes ownership
            onGroundItems->addItemOnGround(removeItem(slotInx), groundItemX(playerHitbox), groundItemY(playerHitbox));
            mInvSlots[slotInx] = nullptr;
            return;
        }
        slotRect.x += mSlotSidelength;
        if (slotRect.x >= mHitbox.x + mPadding + mSlotsPerRow * mSlotSidelength)
        {
            slotRect.x = mHitbox.x + mPadding;
            slotRect.y += mSlotSidelength;
        }
    }
}
bool Inventory::canPickUp()
{
    return getFirstFreeInvSlot() != -1;
}
void Inventory::addItem(std::unique_ptr<Item> &item)
{

    int firstFreeSlot = getFirstFreeInvSlot(); // Index in vector.
    if (firstFreeSlot == -1) // Inv is full
    {
        printf("\n\n***\nItem was added to inventory without checking if inventory is full!!!\n***\n\n");
    }

    int x = 0, y = 0;
    setSlotXYFromIndex(firstFreeSlot, x, y); // The coordinates in inventory.
    x = mHitbox.x + mPadding + (mSlotSidelength*x);
    y = mHitbox.y + mPadding + (mSlotSidelength*y);

    item->setX(x);
    item->setY(y);

    mInvSlots[firstFreeSlot] = std::move(item);
}
std::unique_ptr<Item> Inventory::removeItem(int slot)
{
    std::unique_ptr<Item> item = std::move(mInvSlots[slot]);
    mInvSlots[slot] = nullptr;
    return std::move(item);
}

bool Inventory::loadTexture(SDL_Renderer *renderer, const int *logLevel, int *messageDepth)
{
    return mTexture->loadTexture(mImagePath, renderer, mHitbox.w, mHitbox.h, logLevel, messageDepth);
}

void Inventory::renderItems(SDL_Renderer *renderer)
{
    for (auto iter = std::begin(mInvSlots); iter != std::end(mInvSlots); iter++)
    {
        if ((*iter) == nullptr)
            continue;
        (*iter)->renderOnScreen(renderer);
    }
}
int Inventory::groundItemX(const SDL_Rect &playerHitbox)
{
    return playerHitbox.x + (playerHitbox.w - mSlotSidelength) / 2;
}
int Inventory::groundItemY(const SDL_Rect &playerHitbox)
{
    return playerHitbox.y + playerHitbox.h - mSlotSidelength;
}
int Inventory::getFirstFreeInvSlot()
{
    for (auto iter = mInvSlots.begin(); iter != mInvSlots.end(); iter++)
    {
        if (*iter == nullptr)
        {
            return std::distance(mInvSlots.begin(), iter);
        }
    }
    return -1;
}
void Inventory::setSlotXYFromIndex(const int slot, int& x, int& y)
{
    y = slot / mSlotsPerRow;
    x = slot - (y*mSlotsPerRow);
}
