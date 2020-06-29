#include "Medic.h"
#include "Auxiliaries.h"
using namespace mtm;

Medic::Medic(Team team, units_t health, units_t ammo, units_t range, units_t power) :
    Character(team, health, ammo, range, power,
    Medic::moveDistance, Medic::ammoNeededForAttack, Medic::reloadAmount) {}

Character* Medic::clone() const {
    return new Medic(getTeam(), getHealth(), getAmmo(), getRange(), getPower());
}

bool Medic::isTargetInRange(GridPoint src, GridPoint dst) const {
    if(GridPoint::distance(src , dst) <= getRange() && (src.row == dst.row ||src.col == dst.col)){
        return true;
    }
    return false;
}

void Medic::attackTarget(std::shared_ptr<Character> target) {
    if (target != nullptr) {
        target->takeDamage(target->getTeam() == getTeam() ? -getPower() : getPower());
    }
    ammo -= ammoNeededForAttack;
}

bool Medic::canAttackTarget(std::shared_ptr<Character> target, bool isSelfAttacking) const {
    return target != nullptr && !isSelfAttacking; 
}
