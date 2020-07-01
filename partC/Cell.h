#ifndef EX3_CELL_H
#define EX3_CELL_H
#include "Auxiliaries.h"
#include "Character.h"
#include "Exceptions.h"
#include <memory>
#include <string>

namespace mtm {
    /**
     * Wrapper class for character in board Matrix
     */
    class Cell {
    public:
        GridPoint gridPoint; // gridpoint of cell
        std::shared_ptr<Character> character; // the character that is in the cell

        /**
         * Empty Constructor
         */
        Cell();

        /**
         * copy constructor
         */
        Cell(const Cell& other);

        /**
         * operator =
         */
        Cell& operator=(const Cell& other);
        
        /**
         * destructor
         */
        ~Cell();

        /**
         * @return True if the cell is empty, False otherwise.
         */
        bool isCellEmpty() const;
        
        /**
         * Move the character from her source cell to the given destination 
         */
        static void moveCharacter(Cell& src_cell, Cell& dst_cell);

        /**
         * Remove the character from the cell, making the cell empty.
         */
        void removeCharacter();
        
        /**
         * @return string representation of cell
         */
        std::string toString() const {
            return character == nullptr ? " " : character->toString();
        }
    };
}

#endif // EX3_CELL_H
