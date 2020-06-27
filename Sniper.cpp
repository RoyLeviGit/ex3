#include "Sniper.h"
#include "Auxiliaries.h"
using namespace mtm;

Sniper::Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power) :
    Character(team, health, ammo, range, power,
    Sniper::moveDistance, Sniper::ammoNeededForAttack, Sniper::reloadAmount), shotsCounter(0) {}

Character* Sniper::clone() const {
    return new Sniper(*this);
}

bool Sniper::isTargetInRange(GridPoint src, GridPoint dst) const {
    if(GridPoint::distance(src , dst) <= getRange() &&GridPoint::distance(src , dst) >= std::ceil(getRange()/2)){
        return true;
    }
    return false;
}

bool Sniper::canAttackTarget(std::shared_ptr<Character> target, bool isSelfAttacking) const {
    return target != nullptr && target->getTeam() != getTeam();
}

void Sniper::attackTarget(std::shared_ptr<Character> target) {
    if (target != nullptr) {
        target->takeDamage(shotsCounter%3 == 2 ? 2 * getPower() : getPower());
        shotsCounter++;
    }
    ammo -= ammoNeededForAttack;
}
