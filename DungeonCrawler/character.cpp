#include "character.h"
#include <iostream>
#include "terminalui.h"
#include "graphicalui.h"
using std::cin;
using std::cout;

Character::Character(string texture, int moveDirection, Controller *controller, int strength, int stamina, bool isHuman)
    : isHuman(isHuman), texture(texture), controller(controller), moveDirection(moveDirection), strength(strength), stamina(stamina)
{
    hitpoints = getMaxHP();
}

Tile *Character::getTile() const
{
    return tile;
}

void Character::setTile(Tile *newTile)
{
    tile = newTile;
}

const string &Character::getTexture() const
{
    return texture;
}

int Character::move()
{
    return controller->move();
}

int Character::getMaxHP()
{
    return 20 + (stamina * 5);
}

int Character::getMoveDirection() const
{
    return moveDirection;
}

void Character::setMoveDirection(int value)
{
    moveDirection = value;
}

int Character::getHitpoints() const
{
    return hitpoints;
}

int Character::getStrength() const
{
    return strength;
}

void Character::setStrength(int value)
{
    strength = value;
}

int Character::getStamina() const
{
    return stamina;
}

void Character::setStamina(int value)
{
    stamina = value;
}

bool Character::getIsHuman() const
{
    return isHuman;
}

void Character::setIsHuman(bool value)
{
    isHuman = value;
}

Controller *Character::getController() const
{
    return controller;
}

void Character::setController(Controller *value)
{
    controller = value;
}

void Character::setHitpoints(int value)
{
    hitpoints = value;
}

void Character::fight(Character *enemy)
{
    enemy->setHitpoints(enemy->getHitpoints() - this->strength);

    if (enemy->getHitpoints() <= 0)
    {
        enemy->getTile()->setCharacterDied(true);
        enemy->getTile()->setCharacter(nullptr);
        enemy->setTile(this->getTile());
    }

    if (this->getHitpoints() <= 0)
    {
        this->getTile()->setCharacterDied(true);
        this->getTile()->setCharacter(nullptr);
    }
}
