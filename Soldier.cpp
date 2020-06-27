#include "Soldier.h"
#include "Auxiliaries.h"
using namespace mtm;

Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power) :
    Character(team, health, ammo, range, power,
    Soldier::moveDistance, Soldier::ammoNeededForAttack, Soldier::reloadAmount) {}

Character* Soldier::clone() const {
    return new Soldier(getTeam(), getHealth(), getAmmo(), getRange(), getPower());
}

bool Soldier::isTargetInRange(GridPoint src, GridPoint dst) const {
    return GridPoint::distance(src , dst) <= getRange() && (src.row == dst.row ||src.col == dst.col);
}

void Soldier::attackTarget(std::shared_ptr<Character> target) {
    if (target != nullptr) {
        target->takeDamage(getPower());
    }
    ammo -= ammoNeededForAttack;
}

units_t Soldier::getExplosiveRange() const {
    if (getRange()%3 == 1){
        return (getRange()+2)/3;
    }
    if (getRange()%3 == 2){
        return (getRange()+1)/3;
    }
    return getRange()/3;  
}

units_t Soldier::getExplosiveDamage() const {
    if (getPower()%2 != 0){
        return (getPower()+1)/2;
    }
    return getPower()/2;
}
