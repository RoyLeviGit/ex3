#ifndef EX3_SOLDIER_H
#define EX3_SOLDIER_H
#include "Character.h"

namespace mtm {
    class Soldier : public Character {
    private:
        static const units_t moveDistance = 3; //how far Soldier can move in 1 move action.
        static const units_t ammoNeededForAttack = 1; //ammo cost for attacking
        static const units_t reloadAmount = 3; //ammo points gain from reload
    public:
        /**
         * Constructor
         * @param team the team of the soldier.
         * @param health health points. cannot be zero or lower.
         * @param ammo ammo the soldier has.
         * @param range range of attack for the soldier.
         * @param power attack damage of the soldier.
         * @return new soldier instance.
         */
        Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power);

        /**
         * Virtual copy function for polymorphism
         * @return Shared_ptr of a new soldier instance equal to this soldier.
         */
        Character* clone() const override;

        /**
         * @param src position of the soldier
         * @param dst target position for the attack
         * @return True if the target is in the character's range, False otherwise.
         */
        bool isTargetInRange(GridPoint src, GridPoint dst) const override;

        /**
         * @param target the target of the current attack.
         * @param src_coordinates positions of this medic.
         * @param dst_coordinates position of the target.
         * @return True if it is legal for the soldier to attack the target, False otherwise.
         */
        bool canAttackTarget(std::shared_ptr<Character> target, GridPoint src_coordinates, GridPoint dst_coordinates) const override;

        /**
         * Apply the soldier's attack, removing health from targets.
         * @param target the target of the current attack
         */
        void attackTarget(std::shared_ptr<Character> target) override;

        /**
         * @return the explode range of the current soldier's attack.
         */
        units_t getExplosiveRange() const override;
        
        /**
         * @return the explode damage of the current soldier's attack.
         */
        units_t getExplosiveDamage() const override;

        /**
         * @return string representation of the soldi.
         */
        std::string toString() const override {
            return getTeam() == CPP ? "S" : "s";
        }
    };
}

#endif // EX3_SOLDIER_H