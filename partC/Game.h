#ifndef EX3_GAME_H
#define EX3_GAME_H
#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Matrix.h"
#include "Cell.h"
#include "Character.h"
#include <memory>

namespace mtm {
    class Game {
    private:
        Matrix<Cell> matrix;
        bool isGridPointInBounds(GridPoint gridPoint);
    public:
        Game(int height, int width);
        ~Game();
        Game(const Game& other);
        Game& operator=(const Game& other) = default;

        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
            units_t health, units_t ammo, units_t range, units_t power);

        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        void reload(const GridPoint & coordinates);

        friend std::ostream& operator<<(std::ostream& os, const Game& game);
        bool isOver(Team* winningTeam = NULL) const;
    };
    std::ostream& operator<<(std::ostream& os, const Game& game);
}

#endif // EX3_GAME_H