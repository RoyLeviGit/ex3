#ifndef EX3_SNIPER_H
#define EX3_SNIPER_H
#include "Character.h"

namespace mtm {
    class Sniper : public Character {
    private:
        static const units_t moveDistance = 4;
        static const units_t ammoNeededForAttack = 1;
        static const units_t reloadAmount = 2;
        units_t shotsCounter;
    public:
        Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power);
        Character* clone() const override;
        bool isTargetInRange(GridPoint src, GridPoint dst) const override;
        bool canAttackTarget(std::shared_ptr<Character> target, bool isSelfAttacking) const override;
        void attackTarget(std::shared_ptr<Character> target) override;
        std::string toString() const override {
            return getTeam() == CPP ? "N" : "n";
        }
    };
}

#endif // EX3_SNIPER_H