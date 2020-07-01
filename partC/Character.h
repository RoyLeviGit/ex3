#ifndef EX3_CHARACTER_H
#define EX3_CHARACTER_H
#include "Auxiliaries.h"
#include <string>
#include <memory>

namespace mtm {
    /**
     * Abstract class for game character.
     */
    class Character {
    private:
        enum Team team;
        units_t range;
        units_t power;
        units_t moveDistance;
        units_t ammoNeededForAttack;
        units_t reloadAmount;
    protected:
        units_t health;
        units_t ammo;
        /**
         * Constructor
         * @param team the team of the character.
         * @param health health points. cannot be zero or lower.
         * @param ammo ammo the character has.
         * @param range range of attack for the character.
         * @param power attack damage of the character.
         * @param moveDistance move distance of the character.
         * @param ammoNeededForAttack ammo needed for each attack of the character.
         * @param reloadAmount reload amount of the character.
         */
        Character(Team team, units_t health, units_t ammo, units_t range,
            units_t power, units_t moveDistance, units_t ammoNeededForAttack, units_t reloadAmount);
    public:
        /**
         * Default destructor.
         */
        virtual ~Character() = default;

        /**
         * Virtual copy function for polymorphism
         * @return pointer of a new Character instance equal to this character.
         */
        virtual Character* clone() const = 0;

        /**
         * @return string representation of the character.
         */
        virtual std::string toString() const = 0;
        
        /**
         * @param src position of the character
         * @param dst target position for the attack
         * @return True if the target is in the character's range, False otherwise.
         */
        virtual bool isTargetInRange(GridPoint src, GridPoint dst) const = 0;

        /**
         * Apply the character's attack, removing health from targets.
         * @param target the target of the current attack
         */
        virtual void attackTarget(std::shared_ptr<Character> target) = 0;
        
        /**
         * @param target the target of the current attack.
         * @param src_coordinates position of the character
         * @param dst_coordinates target position for the attack
         * @return True if it is illegal for the character to attack the target, False otherwise.
         */
        virtual bool canAttackTarget(std::shared_ptr<Character> target,
            GridPoint src_coordinates, GridPoint dst_coordinates) const = 0;
        
        /**
         * @return the explode range for the character's attack.
         */
        virtual units_t getExplosiveRange() const;

        /**
         * @return the explode damage for the character's attack.
         */
        virtual units_t getExplosiveDamage() const;
        
        /**
         * Add ammo to the character.
         */
        void reload();

        /**
         * apply damage to character.
         */
        void takeDamage(units_t damage);

        /**
         * @return is character dead.
         */
        bool isDead() const;

        /**
         * @return Team of the character.
         */
        enum Team getTeam() const;

        /**
         * @return the health of the character.
         */
        units_t getHealth() const;

        /**
         * @return the range of the character.
         */
        units_t getRange() const;

        /**
         * @return the power of the character.
         */
        units_t getPower() const;\

        /**
         * @return the moveDistance of the character.
         */
        units_t getMoveDistance() const;

        /**
         * @return the ammo of the character.
         */
        units_t getAmmo() const;
        
        /**
         * @return the ammoNeededForAttack of the character.
         */
        units_t getAmmoNeededForAttack() const;
    };
}

#endif // EX3_CHARACTER_H
