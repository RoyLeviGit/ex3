#include "Character.h"
using namespace mtm;

Character::Character(Team team, units_t health, units_t ammo, units_t range,
    units_t power, units_t moveDistance, units_t ammoNeededForAttack) :
    team(team), health(health), ammo(ammo), range(range), power(power),
    moveDistance(moveDistance), ammoNeededForAttack(ammoNeededForAttack) {
}

void Character::takeDamage(units_t damage) {
    health -= damage;
}

bool Character::isDead() const {
    if(health <= 0){
        return true;
    }
    return false;
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

bool Character::canAttackTarget(std::shared_ptr<Character> target) const {
    return true;
}

units_t Character::getExplosiveRange() const {
    return 0;
}

units_t Character::getExplosiveDamage() const {
    return 0;
}
