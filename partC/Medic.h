#ifndef EX3_MEDIC_H
#define EX3_MEDIC_H
#include "Character.h"

namespace mtm {
    class Medic : public Character {
    private:
        static const units_t moveDistance = 5;
        static const units_t ammoNeededForAttack = 1;
        static const units_t reloadAmount = 5;
    public:
        Medic(Team team, units_t health, units_t ammo, units_t range, units_t power);
        Character* clone() const override;
        bool isTargetInRange(GridPoint src, GridPoint dst) const override;
        void attackTarget(std::shared_ptr<Character> target) override;
        bool canAttackTarget(std::shared_ptr<Character> target, GridPoint src_coordinates, GridPoint dst_coordinates) const override;
        std::string toString() const override {
            return getTeam() == CPP ? "M" : "m";
        }
    };
}

#endif // EX3_MEDIC_H