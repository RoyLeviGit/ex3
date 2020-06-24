#ifndef EX3_SNIPER_H
#define EX3_SNIPER_H
#include "Character.h"

namespace mtm {
    class Sniper : public Character {
    private:
        static const int moveDistance = 4;
        static const int ammoNeededForAttack = 1;
        static const int reloadAmount = 2;
    public:
        Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power);
        Character* clone() const override;
        void reload() override;
        bool isTargetInRange(GridPoint src, GridPoint dst) const override;
        bool canAttackTarget(std::shared_ptr<Character> target) const override;
        void attackTarget(std::shared_ptr<Character> target) override;
        std::string toString() const override;
    };
}

#endif // EX3_SNIPER_H