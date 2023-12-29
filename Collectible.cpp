#include "collectible.h"


collectible::collectible(point r_position, float r_velocityX, float r_velocityY, int r_radius, game* r_pGame) :
    collidable(r_position, r_radius * 2, r_radius * 2, r_pGame),
    position(r_position), velx(r_velocityX), vely(r_velocityY), radius(r_radius)
{
}

collectible::~collectible()
{
}

void collectible::update()
{
    position.x += velx;
    position.y += vely;
}

void collectible::draw()
{
    pGame->getWind()->SetPen(PURPLE);
    pGame->getWind()->SetBrush(PURPLE);
    pGame->getWind()->DrawCircle(position.x, position.y, 7);
}