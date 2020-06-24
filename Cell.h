#ifndef EX3_CELL_H
#define EX3_CELL_H
#include "Auxiliaries.h"
#include "Character.h"
#include <memory>
#include <string>

namespace mtm {
    class Cell {
    private:
    public:
        GridPoint gridPoint;
        std::shared_ptr<Character> character;
        Cell();
        Cell(const Cell& other);
        ~Cell();
        bool isCellEmpty() const;
        void removeCharacter();
        std::string toString() const;
    };
    void moveChracter(Cell src_cell, Cell dst_cell);
}

#endif // EX3_CELL_H