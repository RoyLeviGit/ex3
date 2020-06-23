#ifndef EX3_CHARACTER_H
#define EX3_CHARACTER_H
#include "Auxiliaries.h"
#include <string>

namespace mtm {
    class Character {
    private:
        Team team;
        units_t health;
        units_t ammo;
        units_t range;
        units_t power;
        units_t moveDistance;
        units_t ammoNeededForAttack;
    protected:
        Character(Team team, units_t health, units_t ammo, units_t range,
            units_t power, units_t moveDistance, units_t ammoNeededForAttack);
    public:
        virtual Character& clone() = 0;
        virtual void reload() = 0;
        virtual std::string toString() = 0;
        virtual bool isTargetInRange(GridPoint src, GridPoint dst) = 0;
        virtual bool canAttackTarget(std::shared_ptr<Character> target) = 0;
        virtual void attackTarget(std::shared_ptr<Character> target) = 0;
        virtual units_t getExplosiveRange() = 0;
        virtual units_t getExplosiveDamage() = 0;
        void takeDamage(units_t damage);
        units_t getRange();
        units_t getMoveDistance();
        units_t getAmmo();
        units_t getAmmoNeededForAttack();
    };
}

#endif // EX3_CHARACTER_H
