#ifndef EX3_SOLDIER_H
#define EX3_SOLDIER_H
#include "Character.h"

namespace mtm {
    class Soldier : public Character {
    private:
        static const int moveDistance = 3;
        static const int ammoNeededForAttack = 1;
        static const int reloadAmount = 1;
    public:
        Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power);
        Character* clone() const override;
        void reload() override;
        bool isTargetInRange(GridPoint src, GridPoint dst) const override;
        bool canAttackTarget(std::shared_ptr<Character> target) const override;
        void attackTarget(std::shared_ptr<Character> target) override;
        units_t getExplosiveRange() const override;
        units_t getExplosiveDamage() const override;
        std::string toString() const override;
    };
}

#endif // EX3_SOLDIER_H