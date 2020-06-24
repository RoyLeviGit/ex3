#include "Soldier.h"
#include "Auxiliaries.h"
using namespace mtm;

Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power) :
    Character(team, health, ammo, range, power,
    Soldier::moveDistance, Soldier::ammoNeededForAttack) {}

Character* Soldier::clone() const {
    return new Soldier(getTeam(), getHealth(), getAmmo(), getRange(), getPower());
}

void Soldier::reload() {
    ammo += reloadAmount;
}

bool Soldier::isTargetInRange(GridPoint src, GridPoint dst) const {
    if(GridPoint::distance(src , dst) <= getRange() && (src.row == dst.row ||src.col == dst.col)){
        return true;
    }
    return false;
}

void Soldier::attackTarget(std::shared_ptr<Character> target) {
    target->takeDamage(getPower());
}

units_t Soldier::getExplosiveRange() const {
    return std::ceil(getRange()/3);    
}

units_t Soldier::getExplosiveDamage() const {
    return std::ceil(getPower()/2);
}
