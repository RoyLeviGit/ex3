#include "Medic.h"
#include "Auxiliaries.h"
using namespace mtm;

Medic::Medic(Team team, units_t health, units_t ammo, units_t range, units_t power) :
    Character(team, health, ammo, range, power,
    Medic::moveDistance, Medic::ammoNeededForAttack, Medic::reloadAmount) {}

Character* Medic::clone() const {
    return new Medic(*this);
}

bool Medic::isTargetInRange(GridPoint src, GridPoint dst) const {
    if(GridPoint::distance(src , dst) <= getRange()){
        return true;
    }
    return false;
}

void Medic::attackTarget(std::shared_ptr<Character> target) {
    if (target != nullptr) {
        if (target->getTeam() != getTeam()) {
            ammo -= ammoNeededForAttack;
        }
        target->takeDamage(target->getTeam() == getTeam() ? -getPower() : getPower());
    }
}

bool Medic::canAttackTarget(std::shared_ptr<Character> target, GridPoint src_coordinates, GridPoint dst_coordinates) const {
    return target != nullptr && !(src_coordinates == dst_coordinates); 
}
