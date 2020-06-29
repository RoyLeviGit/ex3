#ifndef EX3_CELL_H
#define EX3_CELL_H
#include "Auxiliaries.h"
#include "Character.h"
#include "Exceptions.h"
#include <memory>
#include <string>

namespace mtm {
    class Cell {
    public:
        GridPoint gridPoint;
        std::shared_ptr<Character> character;
        Cell();
        Cell(const Cell& other);
        Cell& operator=(const Cell& other);
        ~Cell();
        bool isCellEmpty() const;
        static void moveCharacter(Cell& src_cell, Cell& dst_cell);
        void removeCharacter();
        std::string toString() const {
            return character == nullptr ? " " : character->toString();
        }
    };
}

#endif // EX3_CELL_H