#ifndef EX3_GAME_H
#define EX3_GAME_H
#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Matrix.h"
#include "Cell.h"
#include "Character.h"
#include <memory>

namespace mtm {
    /**
    * Class for game.
    */
    class Game {
    private:
        Matrix<Cell> matrix; // game board matrix.

        /**
         * @param gridPoint 2D point.
         * @return True if the point is in the board, False otherwise.
         */
        bool isGridPointInBounds(GridPoint gridPoint);
    public:
        /**
         * Constructor
         * @throw IllegalArgumant if height or width are not positive.
         * @param height number of rows in the game board.
         * @param width number of cols in the game board.
         * @return new Game instance with empty board the size of height x width.
         */
        Game(int height, int width);

        /**
         * destructor
         */
        ~Game();

        /**
         * Copy constructor
         * @param other Game instance to copy
         * @return new Game instance equal to other.
         */
        Game(const Game& other);

        /**
         * = operator
         * @param other Game instance to make this game equal to.
         * @return refreance to the Game, after making it equal to other.
         */
        Game& operator=(const Game& other) = default;
        
        /**
         * Put a character at a poisiton in the game board.
         * @throw IllegalCell if the 2D point is out of the game's bounds.
         * @throw CellOccupied of there's already a character in this position.
         * @param coordinates 2D point in the board to add a new character to.
         * @param character pointer to a character.
         */
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);

        /**
         * @throw IllegalArgument if health is not positive or other paramter is negative.
         * @param type the type of the character to create.
         * @param team the team of the character to create.
         * @param health health points for the new character.
         * @param ammo ammo for the new character.
         * @param range range of attack for the new character.
         * @param power attack damage of the new character.
         * @return pointer to a new Character instance of the type, team and paramters above.
         */
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
            units_t health, units_t ammo, units_t range, units_t power);

        /**
         * Move a character from one poisiton in the game board to another.
         * @throw IllegalCell if any of the 2D points are out of the game's bounds.
         * @throw CellEmpty if the src_coordinates are of an empty cell.
         * @throw CellOccupied if the dst_coordinates cell are already have character in it.
         * @throw MoveTooFar if the character can not move to destenition location.
         * @param src_coordinates 2D point in the board of the character to move.
         * @param dst_coordinates 2D point location in the board to move the character to.
         */
        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

        /**
         * Do an attack of a character in source location at a destantion location.
         * Remove the dead characters form the board afterwards.
         * @throw IllegalCell if any of the 2D points are out of the game's bounds.
         * @throw CellEmpty if the src_coordinates are of an empty cell.
         * @throw OutOfRange if the target is not in the attackers range.
         * @throw OutOfAmmo if the attacker has no ammo to do the current attack.
         * @throw IllegalTarget if the attacker can not attack the target.
         * @param src_coordinates 2D point in the board of the attacking character.
         * @param dst_coordinates 2D point location in the board to attack.
         */
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

        /**
         * Add ammo for the character in source loacation.
         * @throw IllegalCell if the 2D point is out of the game's bounds.
         * @throw CellEmpty if the coordinates are of an empty cell.
         * @param coordinates 2D point in the board of the character to add ammo to.
         */
        void reload(const GridPoint & coordinates);

        //friend declartion. real declartion outside the class.
        friend std::ostream& operator<<(std::ostream& os, const Game& game);
        
        /**
         * @param winningTeam refreance to the winning team.
         * @return True if only one team remained on the board, changing the winning team, False otherwise.
         */
        bool isOver(Team* winningTeam = NULL) const;
    };

    /**
     * Print the game board.
     * @param os output stream
     * @param game game to print.
     */
    std::ostream& operator<<(std::ostream& os, const Game& game);
}

#endif // EX3_GAME_H