#ifndef EX3_MEDIC_H
#define EX3_MEDIC_H
#include "Character.h"

namespace mtm {
    class Medic : public Character {
    private:
        static const int moveDistance = 5;
        static const int ammoNeededForAttack = 1;
        static const int reloadAmount = 5;
    public:
        Medic(Team team, units_t health, units_t ammo, units_t range, units_t power);
        Character* clone() const override;
        void reload() override;
        bool isTargetInRange(GridPoint src, GridPoint dst) const override;
        bool canAttackTarget(std::shared_ptr<Character> target) const override;
        void attackTarget(std::shared_ptr<Character> target) override;
        std::string toString() const override;
    };
}

#endif // EX3_MEDIC_H