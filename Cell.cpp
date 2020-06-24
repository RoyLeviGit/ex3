#include "Cell.h"
#include <memory>
using namespace mtm;

Cell::Cell() : gridPoint(0, 0) {}

Cell::Cell(const Cell& other) : gridPoint(other.gridPoint) {
    if (!other.isCellEmpty()) {
        character = std::shared_ptr<Character>(other.character->clone());
    }
}

Cell::~Cell() {}

bool Cell::isCellEmpty() const {
    return character == nullptr;
}

void Cell::removeCharacter() {
    character = nullptr;
}

std::string Cell::toString() const {
    if (character == nullptr) {
        return " ";
    }
    return character->toString();
}

void mtm::moveChracter(Cell src_cell, Cell dst_cell) {
    if (src_cell.character == nullptr || dst_cell.character != nullptr) {
        throw Exception();
    }
    dst_cell.character = src_cell.character;
    src_cell.character = nullptr;
}
