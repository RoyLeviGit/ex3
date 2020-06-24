#include "Sniper.h"
#include "Auxiliaries.h"
using namespace mtm;

Sniper::Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power) :
    Character(team, health, ammo, range, power,
    Sniper::moveDistance, Sniper::ammoNeededForAttack) {}

Character* Sniper::clone() const {
    return new Sniper(*this);
}

void Sniper::reload() {
    ammo += reloadAmount;
}

bool Sniper::isTargetInRange(GridPoint src, GridPoint dst) const {
    if(GridPoint::distance(src , dst) <= getRange() &&GridPoint::distance(src , dst) >= std::ceil(getRange()/2)){
        return true;
    }
    return false;
}

void Sniper::attackTarget(std::shared_ptr<Character> target) {
    if(target->getTeam() != getTeam()){
        target->takeDamage(getPower());
    }
}
