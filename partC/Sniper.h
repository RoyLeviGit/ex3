#ifndef EX3_SNIPER_H
#define EX3_SNIPER_H
#include "Character.h"

namespace mtm {
    class Sniper : public Character {
    private:
        static const units_t moveDistance = 4; //how far Sniper can move in 1 move action.
        static const units_t ammoNeededForAttack = 1; //ammo cost for attacking
        static const units_t reloadAmount = 2; //ammo points gain from reload
        units_t shotsCounter;
    public:
        /**
         * Constructor
         * @param team the team of the sniper.
         * @param health health points. cannot be zero or lower.
         * @param ammo ammo the sniper has.
         * @param range range of attack for the sniper.
         * @param power attack damage of the sniper.
         * @return new Sniper instance.
         */
        Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power);

        /**
         * Virtual copy function for polymorphism
         * @return Shared_ptr of a new soldier instance equal to this soldier.
         */
        Character* clone() const override;

        /**
         * @param src position of the sniper
         * @param dst target position for the attack
         * @return True if the target is in the sniper's range, False otherwise.
         */
        bool isTargetInRange(GridPoint src, GridPoint dst) const override;

        /**
         * @param target the target of the current attack.
         * @param src_coordinates positions of this medic.
         * @param dst_coordinates position of the target.
         * @return True if it is legal for the sniper to attack the target, False otherwise.
         */
        bool canAttackTarget(std::shared_ptr<Character> target, GridPoint src_coordinates, GridPoint dst_coordinates) const override;

        /**
         * Apply the sniper's attack, removing health from targets.
         * @param target the target of the current attack
         */
        void attackTarget(std::shared_ptr<Character> target) override;

        /**
         * @return string representation of the sniper.
         */
        std::string toString() const override {
            return getTeam() == CPP ? "N" : "n";
        }
    };
}

#endif // EX3_SNIPER_H
