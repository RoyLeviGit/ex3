#ifndef EX3_MEDIC_H
#define EX3_MEDIC_H
#include "Character.h"

namespace mtm {
    class Medic : public Character {
    private:
    public:
        Medic(Team team, units_t health, units_t ammo, units_t range, units_t power);
        Character& clone();
        void reload();
        bool isTargetInRange(GridPoint src, GridPoint dst);
        bool canAttackTarget(std::shared_ptr<Character> target);
        void attackTarget(std::shared_ptr<Character> target);
        units_t getExplosiveRange();
        units_t getExplosiveDamage();
        std::string toString();
    };
}

#endif // EX3_MEDIC_H