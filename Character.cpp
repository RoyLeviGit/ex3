#include "Character.h"
using namespace mtm;

Character::Character(Team team, units_t health, units_t ammo, units_t range,
    units_t power, units_t moveDistance, units_t ammoNeededForAttack, units_t reloadAmount) :
    team(team), range(range), power(power), moveDistance(moveDistance),
    ammoNeededForAttack(ammoNeededForAttack), reloadAmount(reloadAmount),
    health(health), ammo(ammo) {}

void Character::takeDamage(units_t damage) {
    health -= damage;
}

bool Character::isDead() const {
    return health <= 0;
}

enum Team Character::getTeam() const {
    return team;
}

units_t Character::getRange() const {
    return range;
}
units_t Character::getHealth() const {
    return health;
}

units_t Character::getAmmo() const {
    return ammo;
}

units_t Character::getPower() const {
    return power;
}

units_t Character::getMoveDistance() const {
    return moveDistance;
}

units_t Character::getAmmoNeededForAttack() const {
    return ammoNeededForAttack;
}

void Character::reload() {
    ammo += reloadAmount;
}

bool Character::canAttackTarget(std::shared_ptr<Character> target, bool isSelfAttacking) const {
    return true;
}

units_t Character::getExplosiveRange() const {
    return 0;
}

units_t Character::getExplosiveDamage() const {
    return 0;
}
