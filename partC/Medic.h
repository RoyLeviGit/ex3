#ifndef EX3_MEDIC_H
#define EX3_MEDIC_H
#include "Character.h"

namespace mtm {
    class Medic : public Character {
    private:
        static const units_t moveDistance = 5; //how far Medic can move in 1 move action.
        static const units_t ammoNeededForAttack = 1; //ammo cost for attacking enemies
        static const units_t reloadAmount = 5; //ammo points gain from reload
    public:
        /**
         * Constructor
         * @param team the team of the medic.
         * @param health health points. cannot be zero or lower.
         * @param ammo ammo the medic has.
         * @param range range of attack for the medic.
         * @param power attack damage of the medic.
         * @return new Medic instance.
         */
        Medic(Team team, units_t health, units_t ammo, units_t range, units_t power);

        /**
         * Virtual copy function for polymorphism
         * @return Shared_ptr of a new medic instance equal to this medic.
         */
        Character* clone() const override;

        /**
         * @param src position of the medic
         * @param dst target position for the attack
         * @return True if the target is in the character's range, False otherwise.
         */
        bool isTargetInRange(GridPoint src, GridPoint dst) const override;

        /**
         * Apply the medic's attack, removing health from targets.
         * @param target the target of the current attack
         */     
        void attackTarget(std::shared_ptr<Character> target) override;

        /**
         * @param target the target of the current attack.
         * @param src_coordinates positions of this medic.
         * @param dst_coordinates position of the target.
         * @return True if it is legal for the medic to attack the target, False otherwise.
         */
        bool canAttackTarget(std::shared_ptr<Character> target, GridPoint src_coordinates, GridPoint dst_coordinates) const override;

        /**
         * @return string representation of the medic.
         */
        std::string toString() const override {
            return getTeam() == CPP ? "M" : "m";
        }
    };
}

#endif // EX3_MEDIC_H