#ifndef EX3_CHARACTER_H
#define EX3_CHARACTER_H
#include "Auxiliaries.h"
#include <string>

namespace mtm {
    class Character {
    private:
        enum Team team;
        units_t range;
        units_t power;
        units_t moveDistance;
        units_t ammoNeededForAttack;
    protected:
        units_t health;
        units_t ammo;
        Character(Team team, units_t health, units_t ammo, units_t range,
            units_t power, units_t moveDistance, units_t ammoNeededForAttack);
    public:
        virtual ~Character();
        virtual Character* clone() const = 0;
        virtual void reload() = 0;
        virtual std::string toString() const = 0;
        virtual bool isTargetInRange(GridPoint src, GridPoint dst) const = 0;
        virtual void attackTarget(std::shared_ptr<Character> target) = 0;

        virtual bool canAttackTarget(std::shared_ptr<Character> target) const;
        virtual units_t getExplosiveRange() const;
        virtual units_t getExplosiveDamage() const;
        void takeDamage(units_t damage);
        bool isDead() const;
        enum Team getTeam() const;
        units_t getHealth() const;
        units_t getRange() const;
        units_t getPower() const;
        units_t getMoveDistance() const;
        units_t getAmmo() const;
        units_t getAmmoNeededForAttack() const;
    };
}

#endif // EX3_CHARACTER_H
